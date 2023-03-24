
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LabGameState.generated.h"

//Forward Declarations
enum ESafetyEquipmentType;

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSafetyEquipmentNeedToBeChecked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSafetyEquipmentChecked, bool, bIsSafeEquiped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewSafetyEquipmentHasBeenCollected, TEnumAsByte<ESafetyEquipmentType>, NewEquipmentCollected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSafetyEquipmentSend, TArray<TEnumAsByte<ESafetyEquipmentType>>, EquipToCheck);

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ALabGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	/* ------------------------------ CLASS PROPERTIES ------------------------------ */

public:

	UPROPERTY(Transient)
	FOnSafetyEquipmentNeedToBeChecked OnSafetyEquipmentNeedToBeCheckedDelegate;
	
	UPROPERTY(Transient)
	FOnNewSafetyEquipmentHasBeenCollected OnNewSafetyEquipmentHasBeenCollectedDelegate;
	
	UPROPERTY(Transient)
	FOnSafetyEquipmentChecked OnSafetyEquipmentCheckedDelegate;

	UPROPERTY(Transient)
	FOnSafetyEquipmentSend OnSafetyEquipmentSendDelegate;
	
	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */

private:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};