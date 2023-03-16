
#pragma once

#include "CoreMinimal.h"
#include "EmissionParams.generated.h"

USTRUCT(BlueprintType)
struct FEmissionParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = LightningEmission)
	bool bUseLightRenderer = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = LightningEmission)
	float LightMultiplier = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = LightningEmission)
	float LightExponent = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = LightningEmission)
	float LightRadius = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = LightningEmission)
	float LightVolumetricScattering = 0.f;
};