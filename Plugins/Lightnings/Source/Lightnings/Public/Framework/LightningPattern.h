
#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Curves/RichCurve.h"
#include "LightningPattern.generated.h"

/**
* This structure describes a lightning spark position and movement
*/
USTRUCT(BlueprintType)
struct FLightningSparkData
{
	GENERATED_USTRUCT_BODY()

	// Spark world-space coordinates
	UPROPERTY(BlueprintReadOnly, Category = LightningSpark)
	FVector SparkPos = FVector(0.f, 0.f, 0.f);

	// Spark direction
	UPROPERTY(BlueprintReadOnly, Category = LightningSpark)
	FVector SparkDir = FVector(0.f, 0.f, 0.f);

	// Spark scalar velocity value
	UPROPERTY(BlueprintReadOnly, Category = LightningSpark)
	float SparkVelocity = 0.f;

	// Spark target point index in Points array
	UPROPERTY(BlueprintReadOnly, Category = LightningSpark)
	int32 SparkTargetPosIdx = 0;

	// Used for spark movement delays timer
	FTimerHandle SparkDelayTimer;
};

/**
* This structure describes a lightning, including its child branches.
* Contains essential geometry params and runtime params of the lightning.
*/
USTRUCT(BlueprintType)
struct FLightningPattern
{
	GENERATED_USTRUCT_BODY()

	bool FindBranch(int32 JointId, FLightningPattern& OutBranch);

	// Lightning points array, that are connected by segments
	UPROPERTY(BlueprintReadOnly, Category = LightningPattern)
	TArray<FVector> Points;

	// Branches map (joint index -- branch pattern ref)
	TArray<struct FBranchData> Branches;

	// Lightning full length
	UPROPERTY(BlueprintReadOnly, Category = LightningPattern)
	float Length = 0.f;

	// Lightning spark data
	UPROPERTY(BlueprintReadOnly, Category = LightningPattern)
	FLightningSparkData SparkData;

	/**
	* Params to export to NiagaraComponent
	*/
	FRichCurve PointsX;
	FRichCurve PointsY;
	FRichCurve PointsZ;

	// A seed value for lightning's RNG
	// Will be randomly generated if equals -1
	int32 Seed = -1;

	// Does this pattern have valid points
	bool bIsValid = false;
};

// Branches map entry
struct FBranchData
{
	int32 JointId;
	FLightningPattern Pattern;
};