
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/UMG/Menus/LabUWPauseGame.h"
// Unreal Engine Dependencies:
#include "Kismet/GameplayStatics.h"
// User Defined Dependencies:
#include "ElectroLab/Public/UMG/Menus/LabUWSubMenu.h"

	/* ---------------------------- FUNCTION DEFINITIONS ---------------------------- */

void ULabUWPauseGame::NativeConstruct()
{
	Super::NativeConstruct();
	SfxOpenSubMenu();
}

void ULabUWPauseGame::ResumeGame()
{
	APlayerController* PlayerRef = UGameplayStatics::GetPlayerController(GetWorld(),0);
	PlayerRef->SetPause(false);
	
	this->DeactivateWidget();
	this->RemoveFromParent();
	
	PlayerRef->SetInputMode(FInputModeGameOnly());
	PlayerRef->SetShowMouseCursor(false);
}

void ULabUWPauseGame::ReloadLevel()
{
	APlayerController* PlayerRef = UGameplayStatics::GetPlayerController(GetWorld(),0);
	PlayerRef->SetPause(false);
	PlayerRef->SetInputMode(FInputModeGameOnly());
	PlayerRef->SetShowMouseCursor(false);
	
	const FName CurrentLevelName = FName(*UGameplayStatics::GetCurrentLevelName(GetWorld(), true));
	TimerDelegatePauseMenu.BindUFunction(this, "OpenLevel",CurrentLevelName);
	GetWorld()->GetTimerManager().SetTimer(TimerHandlePauseMenu, TimerDelegatePauseMenu, 0.25, false);
}

void ULabUWPauseGame::OpenSettingsMenu()
{
	if(IsValid(WidgetSettingsRef))
	{
		this->DeactivateWidget();
		this->RemoveFromParent();
	
		WidgetSettings = CreateWidget<ULabUWSubMenu>(UGameplayStatics::GetPlayerController(GetWorld(),0), WidgetSettingsRef);
		WidgetSettings->AddToViewport();
		WidgetSettings->ActivateWidget();
	}
}

void ULabUWPauseGame::LoadSelectorLevel()
{
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetPause(false);;
	
	TimerDelegatePauseMenu.BindUFunction(this, "OpenLevel", FName("Map_LaboratorySelector"));
	GetWorld()->GetTimerManager().SetTimer(TimerHandlePauseMenu, TimerDelegatePauseMenu, 0.25, false);
}

void ULabUWPauseGame::LoadMainMenuLevel()
{
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetPause(false);;
	
	TimerDelegatePauseMenu.BindUFunction(this, "OpenLevel", FName("Map_MainMenu"));
	GetWorld()->GetTimerManager().SetTimer(TimerHandlePauseMenu, TimerDelegatePauseMenu, 0.25, false);
}

void ULabUWPauseGame::OpenLevel(const FName &LevelNameToLoad) const
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	UGameplayStatics::OpenLevel(GetWorld(),LevelNameToLoad);
}