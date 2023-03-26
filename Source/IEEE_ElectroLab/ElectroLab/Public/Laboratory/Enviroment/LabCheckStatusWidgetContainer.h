
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LabCheckStatusWidgetContainer.generated.h"

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ALabCheckStatusWidgetContainer : public AActor
{
	GENERATED_BODY()
	
	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */
	
	public:
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Check Status Result"), Category="Widget Container|Events")
	void CheckStatusResult(const bool bStatusResult);

};