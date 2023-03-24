
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/UMG/Menus/LabUWMainMenu.h"
// Unreal Engine Dependencies:
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
// User Defined Dependencies:
#include "AsyncLoadingScreenLibrary.h"
#include "ElectroLab/Public/UMG/Menus/LabUWSubMenu.h"

	/* ---------------------------- FUNCTION DEFINITIONS ---------------------------- */

void ULabUWMainMenu::LoadLevel(const FName &LevelNameToLoad) const
{
	UAsyncLoadingScreenLibrary::SetEnableLoadingScreen(false);
	UGameplayStatics::OpenLevel(GetWorld(),LevelNameToLoad);
}

void ULabUWMainMenu::StartNewGame()
{
	FTimerDelegate StartGameDelegate;
	StartGameDelegate.BindUFunction(this, "LoadLevel", FName("Map_LaboratorySelector"));
	GetWorld()->GetTimerManager().SetTimer(TimerHandleMainMenu, StartGameDelegate, 0.25, false);
}

void ULabUWMainMenu::OpenHowToPlayMenu()
{
	OpenSubMenu(WidgetControlsRef);
}

void ULabUWMainMenu::OpenSettingsMenu()
{
	OpenSubMenu(WidgetSettingsRef);
}

void ULabUWMainMenu::OpenCreditsMenu()
{
	OpenSubMenu(WidgetCreditsRef);
}

void ULabUWMainMenu::OpenSubMenu(const TSubclassOf<ULabUWSubMenu> WidgetReference)
{
	if(IsValid(WidgetReference))
	{
		this->DeactivateWidget();
		this->RemoveFromParent();
	
		WidgetSubMenu = CreateWidget<ULabUWSubMenu>(UGameplayStatics::GetPlayerController(GetWorld(),0), WidgetReference);
		WidgetSubMenu->AddToViewport();
		WidgetSubMenu->ActivateWidget();
	}
}

void ULabUWMainMenu::ExitGame() const
{
	UKismetSystemLibrary::QuitGame(GetWorld(),UGameplayStatics::GetPlayerController(GetWorld(), 0)
		,EQuitPreference::Quit,true);
}