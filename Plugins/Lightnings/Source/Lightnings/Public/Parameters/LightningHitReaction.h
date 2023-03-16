
#pragma once

#include "CoreMinimal.h"
#include "LightningHitReaction.generated.h"

/**
* Describes how lightning should react on a hit event
*/
UENUM(BlueprintType)
enum class EHitReaction : uint8
{
	// No reaction, continue growth
	HR_Ignore		UMETA(DisplayName = "Ignore"),

	// Stop growth, induce discharge (flashing)
	HR_Discharge	UMETA(DisplayName = "Discharge"),

	// Stop growth, start fading out
	HR_FadeOut		UMETA(DisplayName = "FadeOut")
};