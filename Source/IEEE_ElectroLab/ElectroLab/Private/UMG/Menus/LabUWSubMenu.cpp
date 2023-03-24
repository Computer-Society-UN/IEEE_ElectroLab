
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/UMG/Menus/LabUWSubMenu.h"
// Unreal Engine Dependencies:
#include "Kismet/GameplayStatics.h"
// User Defined Dependencies:
#include "ElectroLab/Public/UMG/Menus/LabUWMainMenu.h"

	/* ---------------------------- FUNCTION DEFINITIONS ---------------------------- */

void ULabUWSubMenu::Back()
{
	if(!IsValid(WidgetMainMenuRef)) return;
	
	this->DeactivateWidget();
	this->RemoveFromParent();
	
	WidgetMainMenu = CreateWidget<ULabUWMainMenu>(UGameplayStatics::GetPlayerController(GetWorld(),0), WidgetMainMenuRef);
	WidgetMainMenu->AddToViewport();
	WidgetMainMenu->ActivateWidget();
}