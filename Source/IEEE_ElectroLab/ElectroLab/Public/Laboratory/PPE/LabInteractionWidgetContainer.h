
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LabInteractionWidgetContainer.generated.h"

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ALabInteractionWidgetContainer : public AActor
{
	GENERATED_BODY()

	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */
	
public:
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Set Component Name To Display"), Category="Widget Container|Events")
	void SetComponentNameToDisplay(const FText& NewInteractionComponentName);
	
};