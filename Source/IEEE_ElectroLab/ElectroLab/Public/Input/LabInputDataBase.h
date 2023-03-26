
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LabInputDataBase.generated.h"

// Forward Declarations
class UInputAction;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ULabInputDataBase : public UDataAsset
{
	GENERATED_BODY()

	/* ------------------------------ CLASS PROPERTIES ------------------------------ */

public:
	
	UPROPERTY(EditDefaultsOnly, Category="Input Data|Actions")
	TObjectPtr<UInputAction> ActionCharacterMovement = { nullptr };

	UPROPERTY(EditDefaultsOnly, Category="Input Data|Actions")
	TObjectPtr<UInputAction> ActionCharacterLook = { nullptr };
	
	UPROPERTY(EditDefaultsOnly, Category="Input Data|Actions")
	TObjectPtr<UInputAction> ActionCharacterStaticInteraction = { nullptr };

	UPROPERTY(EditDefaultsOnly, Category="Input Data|Actions")
	TObjectPtr<UInputAction> ActionCharacterDynamicInteraction = { nullptr };

	UPROPERTY(EditDefaultsOnly, Category="Input Data|Actions")
	TObjectPtr<UInputAction> ActionPause = { nullptr };
	
};