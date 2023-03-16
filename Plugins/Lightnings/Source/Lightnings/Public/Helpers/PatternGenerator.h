
#pragma once

#include "CoreMinimal.h"

#include "Framework/LightningPattern.h"
#include "Parameters/BranchingParams.h"

#include "Engine/EngineTypes.h"
#include "Curves/RichCurve.h"
#include "Runtime/Core/Public/Async/AsyncWork.h"

DECLARE_DELEGATE_OneParam(FPatternGeneratedEvent, FLightningPattern);

struct FLightningCurve
{
	/** Curve Start point */
	FVector Start;

	/** Curve end point */
	FVector End;

	/** Curve direction at start point (End - Start) */
	FVector DirStart;

	/** Curve direction at end point (End - Start) */
	FVector DirEnd;

	/**
	 * The curve order (root curve has order 0,
	 * root branches have order 1 and so on)
	 */
	uint32 Order = 0;
};

/**
* Pattern generator creates a lightning pattern using passed params.
* Can do work in parallel thread.
* 
* If initialized with the same seed - generates the same pattern.
*/
class FPatternGenerator : public FNonAbandonableTask
{
	friend class FAsyncTask<FPatternGenerator>;

public:
	FPatternGenerator(
		FPatternGeneratedEvent _OnPatternGenerated,
		FBranchingParams _BranchingParams,
		FVector _Start, FVector _End,
		FVector _StartDir, FVector _EndDir,
		float _NoiseMult,
		float _Step,
		uint32 _Segments,
		bool _bInEditor,
		int32 _Seed = -1);

protected:
	void DoWork();

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FPatternGenerator, STATGROUP_ThreadPoolAsyncTasks);
	}

private:
	void MakeLightningPattern(FLightningPattern& OutPattern, FLightningCurve Curve);
	uint32 CreateSegments(FLightningPattern& OutPattern, FLightningCurve Curve, int32 SegmentId, float AlphaStart, float AlphaEnd, bool bFirstSegment = false);
	void InitializePoint(FLightningPattern& Pattern, FLightningCurve Curve, uint32 PtIndx, float CurveAlpha);

	// A pattern to export
	FLightningPattern ResultPattern;

	// A callback function that is called when the pattern is generated
	FPatternGeneratedEvent OnPatternGenerated;

	FBranchingParams BranchingParams;
	int32 NumBranches = 0;

	// Curves array, the first is always the root
	TArray<FLightningCurve> LightningCurves;

	// Noise level multiplier
	float NoiseMult;

	/**
	* A maximum length of a single segment of the lightning
	* (it equals to step size of lightning's spark).
	*/
	float Step;

	// Number of divisions to generate segments
	uint32 Segments;

	bool bInEditor;

	FRandomStream Rnd;
};