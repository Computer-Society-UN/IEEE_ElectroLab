
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SGSettings.generated.h"

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API USGSettings : public USaveGame
{
	GENERATED_BODY()
	
	/* ------------------------------ CLASS PROPERTIES ------------------------------ */
	
	public:
	
	UPROPERTY()
	int32 GameLanguage = 0;
    
	UPROPERTY()
	float MusicVolume = 1;
	
	UPROPERTY()
	float SfxVolume = 1;
	
};