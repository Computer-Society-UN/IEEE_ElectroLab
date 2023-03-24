
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LabLBPLaboratorySelector.generated.h"

// Forward Declarations
class UCommonActivatableWidget;
class ULabUWLaboratorySelector;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ALabLBPLaboratorySelector : public ALevelScriptActor
{
	GENERATED_BODY()

	/* ------------------------------ CLASS PROPERTIES ------------------------------ */

	UPROPERTY(Transient)
	TObjectPtr<ULabUWLaboratorySelector> WidgetLaboratorySelector = { nullptr };
	
	/** LaboratorySelector Widget Class reference, to be used to create a new widget */
	UPROPERTY(EditDefaultsOnly, Transient, Category="Laboratory Selector|Widgets")
	TSubclassOf<UCommonActivatableWidget> WidgetLaboratorySelectorRefRef = { nullptr };
	
	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */

private:
	
	// Class Constructor
	ALabLBPLaboratorySelector();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};