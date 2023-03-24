
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LabLBPMainMenu.generated.h"

// Forward Declarations
class UCommonActivatableWidget;
class ULabUWMainMenu;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ALabLBPMainMenu : public ALevelScriptActor
{
	GENERATED_BODY()

	/* ------------------------------ CLASS PROPERTIES ------------------------------ */

private:
	
	UPROPERTY(Transient)
	TObjectPtr<ULabUWMainMenu> WidgetMainMenu = { nullptr };
	
	//** Reference to the Global SoundMix created for the project. */
	UPROPERTY(EditDefaultsOnly, Transient, Category="Main Menu|Sound Types")
	TObjectPtr<USoundMix> SMixMasterSoundRef = { nullptr };

	/** Reference to the SoundClass used for game music. */
	UPROPERTY(EditDefaultsOnly, Transient, Category="Main Menu|Sound Types")
	TObjectPtr<USoundClass> SClassMusicRef = { nullptr };
	
	/** Reference to the SoundClass used for game sfx. */
	UPROPERTY(EditDefaultsOnly, Transient, Category="Main Menu|Sound Types")
	TObjectPtr<USoundClass> SClassSfxRef = { nullptr };
	
	/** MainMnu Widget Class reference, to be used to create a new widget */
	UPROPERTY(EditDefaultsOnly, Transient, Category="Main Menu|Widgets")
	TSubclassOf<ULabUWMainMenu> WidgetMainMenuRef = { nullptr };

	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */

private:
	
	// Class Constructor.
	ALabLBPMainMenu();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};