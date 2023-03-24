
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "LabUWPauseGame.generated.h"

// Forward declarations
class ULabCustomButton;
class ULabUWSubMenu;
class USoundCue;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ULabUWPauseGame : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
	/* ------------------------------ CLASS PROPERTIES ------------------------------ */
	
private:
	
	/** Handler for Pause Menu Widget timers. */
	UPROPERTY(Transient)
	FTimerHandle TimerHandlePauseMenu = {};
	
	/** Delegate for Pause Menu Widget timers. */ 
	FTimerDelegate TimerDelegatePauseMenu = {};
	
	/** UCommonButtonBase->OnButtonBaseClicked must be called from Blueprints. <BlueprintReadOnly Needed to reference in GetDesiredFocusTarget() BP Override> */
	UPROPERTY(BlueprintReadOnly, Transient, meta=(BindWidget, DisplayName="Button Resume", AllowPrivateAccess=true), Category="Pause Menu|Buttons")
	TObjectPtr<ULabCustomButton> ButtonResume = { nullptr };

	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonReloadLevel = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonSettings = { nullptr };

	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonBackToLaboratorySelector = { nullptr };

	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonExitToMenu = { nullptr };
	
	UPROPERTY(Transient)
	TObjectPtr<ULabUWSubMenu> WidgetSettings = { nullptr };
	
	/** Settings Widget Class reference, to be used to create a new widget */
	UPROPERTY(EditDefaultsOnly, Transient, Category="Pause Menu|Widgets")
	TSubclassOf<ULabUWSubMenu> WidgetSettingsRef = { nullptr };
	
	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */

public:
	
	/** Event that plays a sound when opening this sub menu. */
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="SFX Open PauseGame"), Category="Pause Menu|Events")
	void SfxOpenSubMenu();
	
private:

	// Class Constructor
	virtual void NativeConstruct() override;
	
	/**
	 * @brief Function that loads a level.
	 * @param LevelNameToLoad Name of the level to be loaded.
	 */
	UFUNCTION()
	void OpenLevel(const FName &LevelNameToLoad) const;
	
	/** Removes the pause and continues the game, it must be called on a GameMap since closing the Widget sets the game mode to InputModeGameOnly. */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Resume Game"), Category="Pause Menu|Functions")
	void ResumeGame();

	/** Opens the Settings Submenu. */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Open Settings Menu"), Category="Pause Menu|Functions")
	void OpenSettingsMenu();
	
	/** Reloads the Current Level. */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Reload Current Level"), Category="Pause Menu|Functions")
	void ReloadLevel();
	
	/** Loads the Level Selector Map. */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Load Laboratory Selector Level"), Category="Pause Menu|Functions")
	void LoadSelectorLevel();
	
	/** Loads the Main Menu Map. */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Load Main Menu Level"), Category="Pause Menu|Functions")
	void LoadMainMenuLevel();
	
};