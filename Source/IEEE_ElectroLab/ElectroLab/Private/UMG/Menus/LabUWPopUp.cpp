
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/UMG/Menus/LabUWPopUp.h"
// Unreal Engine Dependencies:
#include "Kismet/GameplayStatics.h"

	/* ---------------------------- FUNCTION DEFINITIONS ---------------------------- */

void ULabUWPopUp::NativeConstruct()
{
	Super::NativeConstruct();
	SfxOpenSubMenu();
}

void ULabUWPopUp::ClosePopUp()
{
	APlayerController* CurrentPlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	
	this->DeactivateWidget();
	this->RemoveFromParent();
	
	CurrentPlayerController->SetInputMode(FInputModeGameOnly());
	CurrentPlayerController->SetShowMouseCursor(false);
}