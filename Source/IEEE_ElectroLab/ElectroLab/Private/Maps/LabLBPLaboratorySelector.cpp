
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/Maps/LabLBPLaboratorySelector.h"
// Unreal Engine Dependencies:
#include "CommonActivatableWidget.h"
#include "Kismet/GameplayStatics.h"
// User Defined Dependencies:
#include "ElectroLab/Public/UMG/Menus/LabUWLaboratorySelector.h"

	/* ---------------------------- FUNCTION DEFINITIONS ---------------------------- */

ALabLBPLaboratorySelector::ALabLBPLaboratorySelector()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALabLBPLaboratorySelector::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(WidgetLaboratorySelectorRefRef))
	{
		APlayerController* CurrentPlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
		
		WidgetLaboratorySelector = CreateWidget<ULabUWLaboratorySelector>(CurrentPlayerController, WidgetLaboratorySelectorRefRef);
		WidgetLaboratorySelector->AddToViewport();
		WidgetLaboratorySelector->ActivateWidget();
		
		CurrentPlayerController->SetInputMode(FInputModeUIOnly().SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock));
		CurrentPlayerController->SetShowMouseCursor(true);
	}
}