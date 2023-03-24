
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "LabUWPopUp.generated.h"

// Forward declarations
class ULabCustomButton;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ULabUWPopUp : public UCommonActivatableWidget
{
	GENERATED_BODY()

	/* ------------------------------ CLASS PROPERTIES ------------------------------ */
	
private:
	
	/** UCommonButtonBase->OnButtonBaseClicked must be called from Blueprints. <BlueprintReadOnly Needed to reference in GetDesiredFocusTarget() BP Override> */
	UPROPERTY(BlueprintReadOnly, Transient, meta=(BindWidget, DisplayName="Button Primary Action", AllowPrivateAccess=true), Category="PopOut|Buttons")
	TObjectPtr<ULabCustomButton> ButtonPrimaryAction = { nullptr };
	
	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */

public:
	
	/** Event that plays a sound when opening this sub menu. */
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="SFX Open PopUp"), Category="Pause Menu|Events")
	void SfxOpenSubMenu();
	
private:

	// Class Constructor
	virtual void NativeConstruct() override;
	
	/** It must be called on a GameMap since closing the Widget sets the game mode to InputModeGameOnly. */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Close PopUp"), Category="PopUp|Functions")
	void ClosePopUp();
	
};