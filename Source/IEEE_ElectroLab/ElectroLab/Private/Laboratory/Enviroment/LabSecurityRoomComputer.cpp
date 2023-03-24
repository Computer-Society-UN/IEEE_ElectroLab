
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/Laboratory/Enviroment/LabSecurityRoomComputer.h"
// Unreal Engine Dependencies:
#include "Components/ArrowComponent.h"
// User Defined Dependencies:
#include "ElectroLab/Public/Core/LabGameState.h"
#include "ElectroLab/Public/Laboratory/PPE/LabInteractionWidgetContainer.h"

	/* ---------------------------- FUNCTION DEFINITIONS ---------------------------- */

ALabSecurityRoomComputer::ALabSecurityRoomComputer()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(FName("Computer Root"));
	RootComponent = CustomRootComponent;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Computer Mesh"));
	StaticMeshComponent ->SetupAttachment(RootComponent);
	
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(FName("Computer Arrow Direction"));
	ArrowComponent ->SetupAttachment(RootComponent);
}

void ALabSecurityRoomComputer::BeginPlay()
{
	Super::BeginPlay();
	
	if (const TObjectPtr<ALabGameState> GameStateRef = GetWorld()->GetGameState<ALabGameState>())
	{
		GameStateRef->OnSafetyEquipmentSendDelegate.AddDynamic(this, &ALabSecurityRoomComputer::ReceiveEquipmentToCheck);
	}
}

void ALabSecurityRoomComputer::StaticInteraction()
{
	if (bCanInteract)
	{
		if (IsValid(LaboratoriesDataTable))
		{
			if(const FLaboratoryData* LevelDataToBeLoaded = LaboratoriesDataTable->FindRow<FLaboratoryData>(RowName,TEXT("")))
			{
				if (LevelDataToBeLoaded->EquipmentToCheck.Num() == 0)
				{
					if (const TObjectPtr<ALabGameState> GameStateRef = GetWorld()->GetGameState<ALabGameState>())
					{
						GameStateRef->OnSafetyEquipmentCheckedDelegate.Broadcast(false);
						UE_LOG(LogTemp, Error, TEXT("SECURITY ROOM COMPUTER: No Equipment To Check"));

						VfxDisinteraction();
						bCanInteract = false;
						GetWorld()->GetTimerManager().SetTimer(TimerHandleResetInteraction, this, &ALabSecurityRoomComputer::ResetInteraction, 5.0f, false);
					}
				}
				else
				{
					if (const TObjectPtr<ALabGameState> GameStateRef = GetWorld()->GetGameState<ALabGameState>())
					{
						GameStateRef->OnSafetyEquipmentNeedToBeCheckedDelegate.Broadcast();

						if (EngineerEquipment.Num() > 0)
						{
							for (auto& Equipment : LevelDataToBeLoaded->EquipmentToCheck)
							{
								if ( EngineerEquipment.Find(Equipment) == -1)
								{
									GameStateRef->OnSafetyEquipmentCheckedDelegate.Broadcast(false);
									VfxDisinteraction();
									bCanInteract = false;
									GetWorld()->GetTimerManager().SetTimer(TimerHandleResetInteraction, this, &ALabSecurityRoomComputer::ResetInteraction, 5.0f, false);
									return;
								}
							}
							
							GameStateRef->OnSafetyEquipmentCheckedDelegate.Broadcast(true);
							VfxDisinteraction();
							bCanInteract = false;
						}
						else
						{
							GameStateRef->OnSafetyEquipmentCheckedDelegate.Broadcast(false);
							VfxDisinteraction();
							bCanInteract = false;
							GetWorld()->GetTimerManager().SetTimer(TimerHandleResetInteraction, this, &ALabSecurityRoomComputer::ResetInteraction, 5.0f, false);
						}
					}
				}
			}
			else
			{
				if (const TObjectPtr<ALabGameState> GameStateRef = GetWorld()->GetGameState<ALabGameState>())
				{
					GameStateRef->OnSafetyEquipmentCheckedDelegate.Broadcast(false);
					UE_LOG(LogTemp, Error, TEXT("SECURITY ROOM COMPUTER: RowName On DataTable Not Found"));

					VfxDisinteraction();
					bCanInteract = false;
					GetWorld()->GetTimerManager().SetTimer(TimerHandleResetInteraction, this, &ALabSecurityRoomComputer::ResetInteraction, 5.0f, false);
				}
			}
		}
		else
		{
			if (const TObjectPtr<ALabGameState> GameStateRef = GetWorld()->GetGameState<ALabGameState>())
			{
				GameStateRef->OnSafetyEquipmentCheckedDelegate.Broadcast(false);
				UE_LOG(LogTemp, Error, TEXT("SECURITY ROOM COMPUTER: DataTable Not Valid"));

				VfxDisinteraction();
				bCanInteract = false;
				GetWorld()->GetTimerManager().SetTimer(TimerHandleResetInteraction, this, &ALabSecurityRoomComputer::ResetInteraction, 5.0f, false);
			}
		}
	}
}

void ALabSecurityRoomComputer::DynamicInteraction()
{
}

void ALabSecurityRoomComputer::VfxInteraction()
{
	if (bCanInteract)
	{
		VfxOverlay(true);
	
		if (WidgetPPEReference)
		{
			WidgetPPE = GetWorld()->SpawnActor<ALabInteractionWidgetContainer>(WidgetPPEReference,ArrowComponent->GetComponentLocation(),ArrowComponent->GetComponentRotation());
			WidgetPPE->SetComponentNameToDisplay(ComponentName);
		}
	}
}

void ALabSecurityRoomComputer::VfxDisinteraction()
{
	if (bCanInteract)
	{
		VfxOverlay(false);
	
		if (WidgetPPE)
		{
			GetWorld()->DestroyActor(WidgetPPE);
			WidgetPPE = nullptr;
		}
	}
}

void ALabSecurityRoomComputer::ReceiveEquipmentToCheck(TArray<TEnumAsByte<ESafetyEquipmentType>> EngineerEquipmentToCheck)
{
	EngineerEquipment = EngineerEquipmentToCheck;
}

void ALabSecurityRoomComputer::ResetInteraction()
{
	bCanInteract = true;
}