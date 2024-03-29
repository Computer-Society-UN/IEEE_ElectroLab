﻿
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "ElectroLab/Public/Interfaces/LabIInteractable.h"
#include "GameFramework/Actor.h"
#include "LabPPE.generated.h"

// Forward Declarations
class UArrowComponent;
class UCommonUserWidget;
class ALabInteractionWidgetContainer;
enum ESafetyEquipmentType;
enum EInputDataActions;;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ALabPPE : public AActor, public ILabIInteractable
{
	GENERATED_BODY()

	/* ------------------------------ CLASS COMPONENTS ------------------------------ */

private:

	UPROPERTY(VisibleDefaultsOnly, Transient, meta=(DisplayName="Root"))
	TObjectPtr<USceneComponent> CustomRootComponent = { nullptr };
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, meta=(DisplayName="Mesh", AllowPrivateAccess=true), Category="PPE|Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = { nullptr };
	
	UPROPERTY(EditDefaultsOnly, Transient)
	TObjectPtr<UArrowComponent> ArrowComponent = { nullptr };
	
	/* ------------------------------ CLASS PROPERTIES ------------------------------ */

private:

	UPROPERTY(EditDefaultsOnly, Transient, meta=(DisplayName="Component Name"), Category="PPE|Properties")
	FText ComponentName = { FText::FromString("Component Name") };

	UPROPERTY(EditDefaultsOnly, meta=(DisplayName="Safety Equipment Type"), Category="PPE|Properties")
	TEnumAsByte<ESafetyEquipmentType> EquipmentType = {};

	UPROPERTY(EditDefaultsOnly, meta=(DisplayName="PPE Interaction Type"), Category="PPE|Properties")
	TEnumAsByte<EInputDataActions> InteractionType = {};
	
	UPROPERTY(Transient)
	TObjectPtr<ALabInteractionWidgetContainer> WidgetPPE = { nullptr };
	
	UPROPERTY(EditDefaultsOnly, Transient, meta=(DisplayName="Interactable Widget"), Category="PPE|Widget Actor")
	TSubclassOf<ALabInteractionWidgetContainer> WidgetPPEReference = { nullptr };
	
	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */

public:

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="VFX Overlay Interaction"), Category="PPE|Events")
	void VfxOverlay(const bool bInteractionState);
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="SFX Static Interaction"), Category="PPE|Events")
	void SfxInteraction();
	
private:
	
	// Class Constructor
	ALabPPE();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
	
};