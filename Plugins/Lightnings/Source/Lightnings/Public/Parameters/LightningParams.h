
#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "LightningParams.generated.h"

USTRUCT(BlueprintType)
struct FLightningParams
{
	GENERATED_USTRUCT_BODY()

	// Color of particles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = Variables)
	FLinearColor Color = FLinearColor(0.543647f, 0.368351f, 1.f, 1.f);

	// Width form of root lightnings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	UCurveFloat* RootParticlesWidth = NULL;

	// Width form of branches
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	UCurveFloat* BranchParticlesWidth = NULL;

	// Width scale of particles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = Variables)
	float ParticlesWidthScale = 5.f;

	// Whether lightnings are spawned instantly
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = Variables)
	bool bInstant = false;

	// Linear speed of spark in cm/s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, meta = (EditCondition = "bInstant == false"), Category = Variables)
	FFloatRange SparkVelocityRange = FFloatRange(1000000.f, 2500000.f);

	// Fading of spark velocity with order of lightning
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, meta = (EditCondition = "bInstant == false"), Category = Variables)
	FFloatRange SparkVelocityFading = FFloatRange(0.65, 0.8f);

	// Duration of delays in spark movement (in seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, meta = (EditCondition = "bInstant == false"), Category = Variables)
	FFloatRange SparkDelayRange = FFloatRange(0.003f, 0.01f);

	// Noise multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, meta = (UIMin = "0.0", UIMax = "2.0"), Category = Variables)
	float NoiseMult = 1.f;

	// LengthRange of steps in spark movement (in cm)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = Variables)
	float SparkStep = 50.f;

	// Root flashing curve
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	UCurveFloat* FlashingCurve = NULL;

	// Root flashing rate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = Variables)
	FFloatRange FlashingRate = FFloatRange(5.f, 8.5f);

	// Root flashing force
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = Variables)
	FFloatRange FlashingForce = FFloatRange(0.8f, 10.f);

	// Spark light intensity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = Variables)
	float SparkIntensity = 500.f;

	// Spark trail light intensity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = Variables)
	float TrailIntensity = 50.f;

	// Fading of spark trail light intensity with order of lightning
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = Variables)
	FFloatRange TrailIntensityFading = FFloatRange(0.8f, 0.95f);

	// Root light intensity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = Variables)
	float BoltIntensity = 750.f;

	/**
	* Multiplier of speed of lightning spark fade out
	* Value of 1. means it will fade with speed of root flashing
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = Variables)
	float SparkFadeOutSpeedMult = 40.f;

	/**
	* Multiplier of speed of lightning trail fade out
	* Value of 1. means it will fade with speed of root flashing
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = Variables)
	float TrailFadeOutSpeedMult = 1.15f;

	/**
	* Lightning segmentation level
	* Higher values make lightning be more noizy
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, meta = (UIMin = "2"), Category = Variables)
	int32 NumSegments = 5;
};