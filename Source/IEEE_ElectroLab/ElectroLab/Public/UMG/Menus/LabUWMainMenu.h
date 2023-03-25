
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "LabUWMainMenu.generated.h"


// Forward Declarations
class ULabCustomButton;
class ULabUWSubMenu;
class ULabUWSettingsMenu;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ULabUWMainMenu : public UCommonActivatableWidget
{
	GENERATED_BODY()

	/* ------------------------------ CLASS PROPERTIES ------------------------------ */
	
private:

	/** Handler for Main Menu Widget timers. */
	UPROPERTY(Transient)
	FTimerHandle TimerHandleMainMenu = {};
	
	/** UCommonButtonBase->OnButtonBaseClicked must be called from Blueprints. <BlueprintReadOnly Needed to reference in GetDesiredFocusTarget() BP Override> */
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, DisplayName="Button Online Simulation", AllowPrivateAccess="true"), Category="Main Menu|Buttons")
	TObjectPtr<ULabCustomButton> ButtonOnlineSimulation = { nullptr };
	
	/** UCommonButtonBase->OnButtonBaseClicked must be called from Blueprints. <BlueprintReadOnly Needed to reference in GetDesiredFocusTarget() BP Override> */
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, DisplayName="Button Offline Simulation", AllowPrivateAccess="true"), Category="Main Menu|Buttons")
	TObjectPtr<ULabCustomButton> ButtonOfflineSimulation = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonControls = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonSettings = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonCredits = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonExit = { nullptr };
	
	UPROPERTY(Transient)
	TObjectPtr<ULabUWSubMenu> WidgetSubMenu = { nullptr };

	/**  HowToPlay Widget Class reference, to be used to create a new widget */
	UPROPERTY(EditAnywhere, Transient, Category="Main Menu|Widgets")
	TSubclassOf<ULabUWSubMenu> WidgetControlsRef;
	
	/**  Settings Widget Class reference, to be used to create a new widget */
	UPROPERTY(EditAnywhere, Transient, Category="Main Menu|Widgets")
	TSubclassOf<ULabUWSubMenu> WidgetSettingsRef;
	
	/**  Credits Widget Class reference, to be used to create a new widget */
	UPROPERTY(EditAnywhere, Transient, Category="Main Menu|Widgets")
	TSubclassOf<ULabUWSubMenu> WidgetCreditsRef;

	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */

private:

	/**
	 * @brief Function that loads a level.
	 * @param LevelNameToLoad Name of the level to be loaded.
	 */
	UFUNCTION()
	void LoadLevel(const FName &LevelNameToLoad) const;
	
	/**
	 * @brief Function that opens a submenu.
	 * @param WidgetReference Reference to the Widget type to be created, this must be assigned to the blueprint instance.
	 */
	UFUNCTION()
	void OpenSubMenu(const TSubclassOf<ULabUWSubMenu> WidgetReference);
	
	/** Function that opens the level selector map. */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Start New Game"), Category="Main Menu|Functions")
	void StartNewGame();

	// Function that closes the game. */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Exit Game"), Category="Main Menu|Functions")
	void ExitGame() const;

	/** Function that opens the submenu how to play menu. */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Open How To Play SubMenu"), Category="Main Menu|Functions")
	void OpenHowToPlayMenu();
	
	/** Function that opens the submenu settings menu. */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Open Settings SubMenu"), Category="Main Menu|Functions")
	void OpenSettingsMenu();

	/** Function that opens the submenu credits menu. */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Open Credits SubMenu"), Category="Main Menu|Functions")
	void OpenCreditsMenu();
	
};