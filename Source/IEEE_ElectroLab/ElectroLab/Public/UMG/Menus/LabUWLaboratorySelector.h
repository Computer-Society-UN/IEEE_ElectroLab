
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "LabUWLaboratorySelector.generated.h"

// Forward Declarations
class UDataTable;
class ULabCustomButton;
class UCommonButtonStyle;
class UImage;
class ULabGameInstance;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ULabUWLaboratorySelector : public UCommonActivatableWidget
{
	GENERATED_BODY()

	/* ------------------------------ CLASS PROPERTIES ------------------------------ */

private:

	/** Handler for Level Selector timers. */
	UPROPERTY(Transient)
	FTimerHandle TimerHandleLevelSelector = {};
	
	/** Delegate for Level Selector timers. */
	FTimerDelegate TimerDelegateLevelSelector = {};
	
	/** UCommonButtonBase->OnButtonBaseClicked must be called from Blueprints. <BlueprintReadOnly Needed to reference in GetDesiredFocusTarget() BP Override> */
	UPROPERTY(BlueprintReadOnly, Transient, meta=(BindWidget, DisplayName="Button Back To Menu", AllowPrivateAccess=true), Category="Laboratory Selector|Buttons")
	TObjectPtr<ULabCustomButton> ButtonBackToMenu = { nullptr };

	/** It will store the reference to the game instance in order to be able to update it. */
	UPROPERTY(Transient)
	TObjectPtr<ULabGameInstance> GameInstanceReference = { nullptr };

	/** Reference to a DataTable [ Game Levels Structure ] that contains the information to configure the levels. */
	UPROPERTY(EditAnywhere, Transient, Category="Laboratory Selector|Map Data Table")
	TObjectPtr<UDataTable> ListLaboratoryMaps = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonLaboratory_1 = { nullptr };
	
	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */
	
private:

	/** Widget Constructor */
	virtual void NativeConstruct() override;
	
	/**
	 * @brief Function that loads a level.
	 * @param LevelNameToLoad Name of the level to be loaded.
	 */
	UFUNCTION()
	void LoadLevel(const FName &LevelNameToLoad) const;

	/* Load the main menu map. */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Back To Menu"), Category="Laboratory Selector|Functions")
	void BackToMainMenu();

	/* Load the map of laboratory 1. */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Open Laboratory 1"), Category="Laboratory Selector|Functions")
	void OpenLaboratory_1();
	
};