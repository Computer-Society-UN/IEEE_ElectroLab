
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LabGameMode.generated.h"

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ALabGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */
	
private:
	
	// Class Constructor
	ALabGameMode();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};