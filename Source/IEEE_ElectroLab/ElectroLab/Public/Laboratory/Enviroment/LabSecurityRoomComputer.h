﻿
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "FLaboratoryData.h"
#include "ElectroLab/Public/Interfaces/LabIInteractable.h"
#include "GameFramework/Actor.h"
#include "LabSecurityRoomComputer.generated.h"

// Forward Declarations
class UArrowComponent;
class ALabInteractionWidgetContainer;
class ALabCheckStatusWidgetContainer;
class ALabCheckStatusProgressWidgetContainer;
enum EInputDataActions;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ALabSecurityRoomComputer : public AActor, public ILabIInteractable
{
	GENERATED_BODY()

	/* ------------------------------ CLASS COMPONENTS ------------------------------ */

private:
	
	UPROPERTY(VisibleDefaultsOnly, Transient, meta=(DisplayName="Root"))
	TObjectPtr<USceneComponent> CustomRootComponent = { nullptr };
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, meta=(DisplayName="Mesh", AllowPrivateAccess=true), Category="Computer|Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = { nullptr };
	
	UPROPERTY(EditDefaultsOnly, Transient)
	TObjectPtr<UArrowComponent> ArrowComponentInteraction = { nullptr };
	
	UPROPERTY(EditDefaultsOnly, Transient)
	TObjectPtr<UArrowComponent> ArrowComponentStatus = { nullptr };
	
	/* ------------------------------ CLASS PROPERTIES ------------------------------ */

private:

	UPROPERTY(Transient)
	FTimerHandle TimerHandleResetInteraction = {};

	UPROPERTY()
	bool bCanInteract = true;

	UPROPERTY()
	bool bInteractionCheck = true;
	
	UPROPERTY(EditDefaultsOnly, Transient, meta=(DisplayName="Component Name"), Category = "Computer|Properties")
	FText ComponentName = { FText::FromString("Component Name") };

	UPROPERTY(EditAnywhere, meta=(DisplayName="DataTable RowName"), Category = "Computer|Properties")
	FName RowName = { FName("Lab_01") };

	UPROPERTY(EditDefaultsOnly, meta=(DisplayName="Computer Interaction Type"), Category="PPE|Properties")
	TEnumAsByte<EInputDataActions> InteractionType = {};
	
	UPROPERTY(EditAnywhere, meta=(DisplayName="Laboratories Data Table"), Category = "Computer|Properties")
	TObjectPtr<UDataTable> LaboratoriesDataTable = { nullptr };

	UPROPERTY(Transient)
	TArray<TEnumAsByte<ESafetyEquipmentType>> EngineerEquipment = {};
	
	UPROPERTY(Transient)
	TObjectPtr<ALabInteractionWidgetContainer> WidgetInteraction = { nullptr };
	
	UPROPERTY(Transient)
	TObjectPtr<ALabCheckStatusWidgetContainer> WidgetCheckStatus = { nullptr };
	
	UPROPERTY(Transient)
	TObjectPtr<ALabCheckStatusProgressWidgetContainer> WidgetCheckProgress = { nullptr };

	UPROPERTY(EditDefaultsOnly, Transient, meta=(DisplayName="Interactable Widget"), Category="Computer|Widget Actor")
	TSubclassOf<ALabInteractionWidgetContainer> WidgetInteractionReference = { nullptr };
	
	UPROPERTY(EditDefaultsOnly, Transient, meta=(DisplayName="Status Widget"), Category="Computer|Widget Actor")
	TSubclassOf<ALabCheckStatusWidgetContainer> WidgetCheckStatusReference = { nullptr };

	UPROPERTY(EditDefaultsOnly, Transient, meta=(DisplayName="Progress Widget"), Category="Computer|Widget Actor")
	TSubclassOf<ALabCheckStatusProgressWidgetContainer> WidgetCheckProgressReference = { nullptr };

	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */

public:

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="VFX Overlay Interaction"), Category="Computer|Events")
	void VfxOverlay(const bool bInteractionState);
	
private:
	
	// Class Constructor
	ALabSecurityRoomComputer();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Interactable Interface Implementation
	virtual void StaticInteraction() override;

	// Interactable Interface Implementation
	virtual void OnGoingDynamicInteraction(const float HoldTime) override;

	// Interactable Interface Implementation
	virtual void CancelDynamicInteraction() override;
	
	// Interactable Interface Implementation
	virtual void TriggerDynamicInteraction() override;

	// Interactable Interface Implementation
	virtual void VfxInteraction() override;

	// Interactable Interface Implementation
	virtual void VfxDisinteraction() override;

	/**
	 * @brief You receive the equipment that the character has, to check if it corresponds to the equipment needed for the laboratory.
	 * @param EngineerEquipmentToCheck Array with equipment that the character has.
	 */
	UFUNCTION()
	void ReceiveEquipmentToCheck(TArray<TEnumAsByte<ESafetyEquipmentType>> EngineerEquipmentToCheck);

	UFUNCTION()
	void ResetInteraction();
	
};