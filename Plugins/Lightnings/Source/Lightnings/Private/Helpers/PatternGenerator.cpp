
#include "Helpers/PatternGenerator.h"
#include "Helpers/GuardedExecution.h"
#include "Async/Async.h"

FPatternGenerator::FPatternGenerator(
	FPatternGeneratedEvent _OnPatternGenerated,
	FBranchingParams _BranchingParams,
	FVector _Start, FVector _End,
	FVector _StartDir, FVector _EndDir,
	float _NoiseMult,
	float _Step,
	uint32 _Segments,
	bool _bInEditor,
	int32 _Seed /*= -1*/) :

	OnPatternGenerated(_OnPatternGenerated),
	BranchingParams(_BranchingParams),
	NoiseMult(_NoiseMult),
	Step(_Step),
	Segments(_Segments),
	bInEditor(_bInEditor)
{
	FLightningCurve RootCurve;

	RootCurve.Start = _Start;
	RootCurve.End = _End;
	RootCurve.DirStart = _StartDir;
	RootCurve.DirEnd = _EndDir;
	RootCurve.Order = 0;

	LightningCurves.Add(RootCurve);

	if (_Seed == -1)
	{
		// Use a random seed
		Rnd.GenerateNewSeed();
	}
	else
	{
		// Use the specified seed
		Rnd.Initialize(_Seed);
	}
}

void FPatternGenerator::DoWork()
{
	MakeLightningPattern(ResultPattern, LightningCurves[0]);

	FLightningPattern Out = ResultPattern;
	FPatternGeneratedEvent Event = OnPatternGenerated;
	bool bEditor = bInEditor;

	AsyncTask(ENamedThreads::GameThread, [Event, Out, bEditor] ()
	{
#if WITH_EDITOR
		if (bEditor)
		{
			FEditorScriptExecutionGuard ScriptGuard;
			Event.ExecuteIfBound(Out);
		}
		else
#endif // WITH_EDITOR
		{
			Event.ExecuteIfBound(Out);
		}
	});
}

void FPatternGenerator::MakeLightningPattern(FLightningPattern& OutPattern, FLightningCurve Curve)
{
	OutPattern.Points.Add(Curve.Start);
	OutPattern.Points.Add(Curve.End);

	CreateSegments(OutPattern, Curve, 0, 0.f, 1.f, true);

	// Initialize last point of the pattern
	InitializePoint(OutPattern, Curve, OutPattern.Points.Num() - 1, 1.f);

	OutPattern.SparkData.SparkPos = OutPattern.Points[0];
	OutPattern.Seed = Rnd.GetCurrentSeed();
	OutPattern.bIsValid = true;
}

uint32 FPatternGenerator::CreateSegments(FLightningPattern& OutPattern, FLightningCurve Curve, int32 SegmentId, float AlphaStart, float AlphaEnd, bool bFirstSegment /*= false*/)
{
	FVector Start = OutPattern.Points[SegmentId];
	FVector End = OutPattern.Points[SegmentId + 1];

	const float SegmentLength = (Start - End).Size();

	if (Step >= SegmentLength)
	{
		/**
		* Passed segment is of length of spark step
		* (segment is indivisible),
		* calculating lightning length
		*/
		OutPattern.Length += SegmentLength;

		// Add point to rich curves and generate a branch if necessary
		InitializePoint(OutPattern, Curve, SegmentId, AlphaStart);

		return 0;
	}

	/**
	* Computing path segments from A to B
	*/
	TArray<FVector> PathAB;

	// Noise is 0.06 per cm of length of path
	const float NoiseLevel = 0.06f * SegmentLength * NoiseMult;

	const float AlphaStep = 1.f / float(Segments);
	for (float Alpha = AlphaStep; Alpha < 1.f; Alpha += AlphaStep)
	{
		FVector Pt;
		if (bFirstSegment)
		{
			/**
			 * Cubic Bezier curve control points:
			 *  P0 = Start
			 *  P1 = P1
			 *  P2 = P2
			 *  P3 = End
			 *
			 *  https://en.wikipedia.org/wiki/Bezier_curve
			 */

			FVector P1 = Start + Curve.DirStart;
			FVector P2 = End - Curve.DirEnd;

			const float InvT = 1.f - Alpha;
			Pt = InvT * InvT * InvT * Start + 3 * Alpha * InvT * InvT * P1 + 3 * Alpha * Alpha * InvT * P2 + Alpha * Alpha * Alpha * End;
		}
		else
		{
			/** Linear interpolation */
			Pt = FMath::Lerp(Start, End, Alpha);
		}

		FVector Noise = FVector(Rnd.FRandRange(-1.f, 1.f), Rnd.FRandRange(-1.f, 1.f), Rnd.FRandRange(-1.f, 1.f)) * NoiseLevel;
		PathAB.Add(Pt + Noise);
	}

	/**
	* Inserting path segments between A and B points
	*/
	OutPattern.Points.Insert(PathAB, SegmentId + 1);

	/**
	* Creating path between created segments
	*/
	uint32 PtIndx = SegmentId;
	uint32 PointsCreated = PathAB.Num();
	float CurAlpha = AlphaStart;
	while (PtIndx <= SegmentId + PointsCreated)
	{
		const float NextAlpha = CurAlpha + AlphaStep * (AlphaEnd - AlphaStart);
		const uint32 NewPointsNum = CreateSegments(OutPattern, Curve, PtIndx, CurAlpha, NextAlpha);
		PtIndx += NewPointsNum + 1;
		PointsCreated += NewPointsNum;
		CurAlpha = NextAlpha;
	}

	return PointsCreated;
}

void FPatternGenerator::InitializePoint(FLightningPattern& Pattern, FLightningCurve Curve, uint32 PtIndx, float CurveAlpha)
{
	const FVector Point = Pattern.Points[PtIndx];

	// Convert pattern segments to Vector3 curve to parse it to the Niagara component later
	Pattern.PointsX.SetKeyInterpMode(Pattern.PointsX.AddKey(PtIndx, Point.X), ERichCurveInterpMode::RCIM_Linear);
	Pattern.PointsY.SetKeyInterpMode(Pattern.PointsY.AddKey(PtIndx, Point.Y), ERichCurveInterpMode::RCIM_Linear);
	Pattern.PointsZ.SetKeyInterpMode(Pattern.PointsZ.AddKey(PtIndx, Point.Z), ERichCurveInterpMode::RCIM_Linear);

	/*
	* Generate a branch
	*/
	if (PtIndx == 0 || PtIndx + 1 == Pattern.Points.Num())
	{
		// Cannot generage a branch on start and end of the lightning
		return;
	}

	if (BranchingParams.BranchChance <= 0.f)
	{
		// No chance to spawn a branch
		return;
	}

	if (BranchingParams.bUseBranchesLimit && NumBranches >= BranchingParams.BranchesLimit)
	{
		// Branches limit reached
		return;
	}

	const float RandVal = Rnd.GetFraction();
	float BranchProb = BranchingParams.BranchChance * FMath::Pow(BranchingParams.BranchChanceFading, Curve.Order);
	BranchProb = FMath::Clamp(BranchProb, 0.f, 1.f);
	if (RandVal <= BranchProb)
	{
		const FVector Prev = Pattern.Points[PtIndx - 1];
		const FVector Cur = Pattern.Points[PtIndx];
		const FVector Next = Pattern.Points[PtIndx + 1];

		/**
		* Calculating and rotating direction unit vector
		*/
		FVector Dir = (Cur - Prev).GetSafeNormal();
		FVector DirNext = (Next - Cur).GetSafeNormal();

		// Check Dir not to be equal to DirNext
		if (Dir.Equals(DirNext))
		{
			const float NoiseLevel = 0.01f;
			const float x = Rnd.FRandRange(-NoiseLevel, NoiseLevel);
			const float y = Rnd.FRandRange(-NoiseLevel, NoiseLevel);
			const float z = Rnd.FRandRange(-NoiseLevel, NoiseLevel);
			DirNext += FVector(x, y, z);
		}

		const FVector RotAxis = FVector::CrossProduct(Dir, DirNext).GetSafeNormal();

		const float Angle = Rnd.FRandRange(BranchingParams.RotationRange.GetLowerBoundValue(), BranchingParams.RotationRange.GetUpperBoundValue());
		Dir = Dir.RotateAngleAxis(Angle, RotAxis);

		/**
		* Calculating branch length depending on length of the root
		*/
		const float Length = Rnd.FRandRange(BranchingParams.LengthRange.GetLowerBoundValue(), BranchingParams.LengthRange.GetUpperBoundValue());
		const float RootLength = (ResultPattern.Points[0] - ResultPattern.Points[ResultPattern.Points.Num() - 1]).Size();
		const FVector BranchEnd = Cur + Dir * Length * RootLength;

		++NumBranches;

		/**
		 * Getting a spline that fit the parent curve well
		 */
		FVector P0 = Curve.Start;
		FVector P1 = Curve.Start + Curve.DirStart;
		FVector P2 = Curve.End - Curve.DirEnd;
		FVector P3 = Curve.End;

		FVector Q0 = FMath::Lerp(P0, P1, CurveAlpha);
		FVector Q1 = FMath::Lerp(P1, P2, CurveAlpha);
		FVector Q2 = FMath::Lerp(P2, P3, CurveAlpha);

		FVector R0 = FMath::Lerp(Q0, Q1, CurveAlpha);
		FVector R1 = FMath::Lerp(Q1, Q2, CurveAlpha);

		FVector B = FMath::Lerp(R0, R1, CurveAlpha);

		FLightningCurve BranchRootCurve;
		BranchRootCurve.Start = Cur;
		BranchRootCurve.End = FMath::Lerp(BranchEnd, Curve.End, BranchingParams.ConvergeFactor);
		BranchRootCurve.DirStart = (R1 - B) * BranchingParams.ConvergeFactor;
		BranchRootCurve.DirEnd = Curve.DirEnd * BranchingParams.ConvergeFactor * (1 - CurveAlpha);
		BranchRootCurve.Order = Curve.Order + 1;
		LightningCurves.Add(BranchRootCurve);

		FLightningPattern BranchPattern;
		MakeLightningPattern(BranchPattern, BranchRootCurve);

		Pattern.Branches.Add({ (int32)PtIndx, BranchPattern });
	}
}
