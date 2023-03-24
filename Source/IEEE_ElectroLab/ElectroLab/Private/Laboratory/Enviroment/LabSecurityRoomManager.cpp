
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/Laboratory/Enviroment/LabSecurityRoomManager.h"
// User Defined Dependencies:
#include "ElectroLab/Public/Core/LabGameState.h"

	/* ---------------------------- FUNCTION DEFINITIONS ---------------------------- */

void ALabSecurityRoomManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (const TObjectPtr<ALabGameState> GameStateRef = GetWorld()->GetGameState<ALabGameState>())
	{
		GameStateRef->OnSafetyEquipmentCheckedDelegate.AddDynamic(this, &ALabSecurityRoomManager::OnSystemCheck);
	}
}

void ALabSecurityRoomManager::OnSystemCheck(const bool bCheckStatus)
{
	if (bCheckStatus)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("System Check: OK"));
		VFXOnSystemCheck(bCheckStatus);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("System Check: FAIL"));
		VFXOnSystemCheck(bCheckStatus);
	}
}