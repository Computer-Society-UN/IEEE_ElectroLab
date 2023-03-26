
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/Laboratory/Enviroment/LabSecurityRoomComputer.h"
// Unreal Engine Dependencies:
#include "Components/ArrowComponent.h"
// User Defined Dependencies:
#include "ElectroLab/Public/Core/LabGameState.h"
#include "ElectroLab/Public/Laboratory/Enviroment/LabCheckStatusWidgetContainer.h"
#include "ElectroLab/Public/Laboratory/Enviroment/LabCheckStatusProgressWidgetContainer.h"
#include "ElectroLab/Public/Laboratory/PPE/LabInteractionWidgetContainer.h"

	/* ---------------------------- FUNCTION DEFINITIONS ---------------------------- */

ALabSecurityRoomComputer::ALabSecurityRoomComputer()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(FName("Computer Root"));
	RootComponent = CustomRootComponent;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Computer Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	ArrowComponentInteraction = CreateDefaultSubobject<UArrowComponent>(FName("Computer Arrow Interaction"));
	ArrowComponentInteraction->SetupAttachment(RootComponent);
	
	ArrowComponentStatus = CreateDefaultSubobject<UArrowComponent>(FName("Computer Arrow Status"));
	ArrowComponentStatus->SetupAttachment(RootComponent);
}

void ALabSecurityRoomComputer::BeginPlay()
{
	Super::BeginPlay();
	
	if (const TObjectPtr<ALabGameState> GameStateRef = GetWorld()->GetGameState<ALabGameState>())
	{
		GameStateRef->OnSafetyEquipmentSendDelegate.AddDynamic(this, &ALabSecurityRoomComputer::ReceiveEquipmentToCheck);
	}
}

void ALabSecurityRoomComputer::StaticInteraction(){}

void ALabSecurityRoomComputer::OnGoingDynamicInteraction(const float HoldTime)
{
	if (bCanInteract)
	{
		if (!IsValid(WidgetCheckProgress) && IsValid(WidgetCheckProgressReference))
		{
			WidgetCheckProgress = GetWorld()->SpawnActor<ALabCheckStatusProgressWidgetContainer>(WidgetCheckProgressReference,ArrowComponentStatus->GetComponentLocation(),ArrowComponentStatus->GetComponentRotation());
			WidgetCheckProgress->CheckProgressTime(HoldTime);
		}
		else
		{
			WidgetCheckProgress->CheckProgressTime(HoldTime);
		}
	}
}

void ALabSecurityRoomComputer::CancelDynamicInteraction()
{
	if (bCanInteract)
	{
		if (IsValid(WidgetCheckProgress))
		{
			WidgetCheckProgress->Destroy();
			WidgetCheckProgress = nullptr;
		}
	}
}

void ALabSecurityRoomComputer::TriggerDynamicInteraction()
{
	if (bInteractionCheck)
	{
		bInteractionCheck = false;

		if (IsValid(WidgetCheckProgress))
		{
			WidgetCheckProgress->Destroy();
			WidgetCheckProgress = nullptr;
		}
		
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

							if (WidgetCheckStatusReference)
							{
								WidgetCheckStatus = GetWorld()->SpawnActor<ALabCheckStatusWidgetContainer>(WidgetCheckStatusReference,ArrowComponentStatus->GetComponentLocation(),ArrowComponentStatus->GetComponentRotation());
								WidgetCheckStatus->CheckStatusResult(false);
							}
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

										if (WidgetCheckStatusReference)
										{
											WidgetCheckStatus = GetWorld()->SpawnActor<ALabCheckStatusWidgetContainer>(WidgetCheckStatusReference,ArrowComponentStatus->GetComponentLocation(),ArrowComponentStatus->GetComponentRotation());
											WidgetCheckStatus->CheckStatusResult(false);
										}
										
										return;
									}
								}
								
								GameStateRef->OnSafetyEquipmentCheckedDelegate.Broadcast(true);
								VfxDisinteraction();
								bCanInteract = false;
								
								if (WidgetCheckStatusReference)
								{
									WidgetCheckStatus = GetWorld()->SpawnActor<ALabCheckStatusWidgetContainer>(WidgetCheckStatusReference,ArrowComponentStatus->GetComponentLocation(),ArrowComponentStatus->GetComponentRotation());
									WidgetCheckStatus->CheckStatusResult(true);
								}

								/* We remove the reference, because from Blueprints we are destroying it. */
								WidgetCheckStatus = nullptr;
							}
							else
							{
								GameStateRef->OnSafetyEquipmentCheckedDelegate.Broadcast(false);
								VfxDisinteraction();
								bCanInteract = false;
								GetWorld()->GetTimerManager().SetTimer(TimerHandleResetInteraction, this, &ALabSecurityRoomComputer::ResetInteraction, 5.0f, false);

								if (WidgetCheckStatusReference)
								{
									WidgetCheckStatus = GetWorld()->SpawnActor<ALabCheckStatusWidgetContainer>(WidgetCheckStatusReference,ArrowComponentStatus->GetComponentLocation(),ArrowComponentStatus->GetComponentRotation());
									WidgetCheckStatus->CheckStatusResult(false);
								}
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

						if (WidgetCheckStatusReference)
						{
							WidgetCheckStatus = GetWorld()->SpawnActor<ALabCheckStatusWidgetContainer>(WidgetCheckStatusReference,ArrowComponentStatus->GetComponentLocation(),ArrowComponentStatus->GetComponentRotation());
							WidgetCheckStatus->CheckStatusResult(false);
						}
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

					if (WidgetCheckStatusReference)
					{
						WidgetCheckStatus = GetWorld()->SpawnActor<ALabCheckStatusWidgetContainer>(WidgetCheckStatusReference,ArrowComponentStatus->GetComponentLocation(),ArrowComponentStatus->GetComponentRotation());
						WidgetCheckStatus->CheckStatusResult(false);
					}
				}
			}
		}
	}
}

void ALabSecurityRoomComputer::VfxInteraction()
{
	if (bCanInteract)
	{
		VfxOverlay(true);
	
		if (WidgetInteractionReference)
		{
			WidgetInteraction = GetWorld()->SpawnActor<ALabInteractionWidgetContainer>(WidgetInteractionReference,ArrowComponentInteraction->GetComponentLocation(),ArrowComponentInteraction->GetComponentRotation());
			WidgetInteraction->SetComponentNameToDisplay(ComponentName, InteractionType);
		}
	}
}

void ALabSecurityRoomComputer::VfxDisinteraction()
{
	if (bCanInteract)
	{
		VfxOverlay(false);
	
		if (WidgetInteraction)
		{
			GetWorld()->DestroyActor(WidgetInteraction);
			WidgetInteraction = nullptr;
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
	bInteractionCheck = true;

	if (WidgetCheckStatus)
	{
		WidgetCheckStatus->Destroy();
		WidgetCheckStatus = nullptr;
	}
}