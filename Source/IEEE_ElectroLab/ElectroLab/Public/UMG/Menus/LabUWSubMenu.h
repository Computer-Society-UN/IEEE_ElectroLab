
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "LabUWSubMenu.generated.h"

// Forward Declarations
class ULabCustomButton;
class ULabUWMainMenu;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ULabUWSubMenu : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
	/* ------------------------------ CLASS PROPERTIES ------------------------------ */

private:
	
	/** UCommonButtonBase->OnButtonBaseClicked must be called from Blueprints. <BlueprintReadOnly Needed to reference in GetDesiredFocusTarget() BP Override> */
	UPROPERTY(BlueprintReadOnly, Transient, meta=(BindWidget, DisplayName="Button Back", AllowPrivateAccess=true), Category="SubMenu|Buttons")
	TObjectPtr<ULabCustomButton> ButtonBack = { nullptr };

protected:
	
	UPROPERTY(Transient)
	TObjectPtr<ULabUWMainMenu> WidgetMainMenu = { nullptr};
	
	/** MainMenu Widget Class reference, to be used to create a new widget */
	UPROPERTY(EditDefaultsOnly, Transient, Category="SubMenu|Widgets")
	TSubclassOf<ULabUWMainMenu> WidgetMainMenuRef = { nullptr };
	
	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */
	
private:
	
	/** Loads Main Menu Map. */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Back"), Category="SubMenu|Functions")
	virtual void Back();
	
};