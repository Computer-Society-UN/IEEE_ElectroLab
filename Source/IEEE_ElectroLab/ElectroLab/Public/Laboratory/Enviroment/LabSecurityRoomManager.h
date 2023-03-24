
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LabSecurityRoomManager.generated.h"

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ALabSecurityRoomManager : public AActor
{
	GENERATED_BODY()

	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */

public:

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="VFX On System Check"), Category="Security Room Manager|Events")
	void VFXOnSystemCheck(const bool bCheckStatus);
	
private:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * @brief Receives the result of the safety equipment verification.
	 * @param bCheckStatus Returns whether or not the character has the necessary equipment.
	 */
	UFUNCTION()
	void OnSystemCheck(const bool bCheckStatus);
	
};