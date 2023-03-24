
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/UMG/Menus/LabUWLaboratorySelector.h"
// Unreal Engine Dependencies:
#include "Kismet/GameplayStatics.h"
// User Defined Dependencies:
#include "AsyncLoadingScreenLibrary.h"
#include "ElectroLab/Public/UMG/Menus/LabCustomButton.h"

	/* ---------------------------- FUNCTION DEFINITIONS ---------------------------- */

void ULabUWLaboratorySelector::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void ULabUWLaboratorySelector::LoadLevel(const FName &LevelNameToLoad) const
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	UGameplayStatics::OpenLevel(GetWorld(),LevelNameToLoad);
}

void ULabUWLaboratorySelector::BackToMainMenu()
{
	TimerDelegateLevelSelector.BindUFunction(this, "LoadLevel", FName("Map_MainMenu"));
	GetWorld()->GetTimerManager().SetTimer(TimerHandleLevelSelector, TimerDelegateLevelSelector, 0.25, false);
}

void ULabUWLaboratorySelector::OpenLaboratory_1()
{
	TimerDelegateLevelSelector.BindUFunction(this, "LoadLevel", FName("Map_Laboratory_1"));
	UAsyncLoadingScreenLibrary::SetEnableLoadingScreen(true);
	GetWorld()->GetTimerManager().SetTimer(TimerHandleLevelSelector, TimerDelegateLevelSelector, 0.25, false);
}