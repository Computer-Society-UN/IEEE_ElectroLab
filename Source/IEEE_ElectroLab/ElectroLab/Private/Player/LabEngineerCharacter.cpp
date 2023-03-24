
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/Player/LabEngineerCharacter.h"
// Unreal Engine Dependencies:
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
// User Defined Dependencies:
#include "ElectroLab/Public/Core/LabGameState.h"
#include "ElectroLab/Public/Interfaces/LabIInteractable.h"

	/* ---------------------------- FUNCTION DEFINITIONS ---------------------------- */

ALabEngineerCharacter::ALabEngineerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Engineer Camera"));
	CameraComponent->SetupAttachment(RootComponent);
}

void ALabEngineerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const TObjectPtr<ALabGameState> GameStateRef = GetWorld()->GetGameState<ALabGameState>())
	{
		GameStateRef->OnSafetyEquipmentNeedToBeCheckedDelegate.AddDynamic(this, &ALabEngineerCharacter::CheckIfIShouldEndTheEquipmentIHaveOn);
		GameStateRef->OnNewSafetyEquipmentHasBeenCollectedDelegate.AddDynamic(this, &ALabEngineerCharacter::PickUpNewSafetyEquipment);
	}
}

void ALabEngineerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FHitResult OutHit;
	const TArray<AActor*> ActorsToIgnore;
	const FVector StartTrace = CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * 50.f;
	const FVector EndTrace = StartTrace + CameraComponent->GetForwardVector() * MaxInteractionDistance;
	
	bool IsHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), StartTrace, EndTrace, static_cast<ETraceTypeQuery>(ECC_Visibility), false, ActorsToIgnore,
		InteractionDebugType, OutHit, true, FLinearColor::Red, FLinearColor::Green, DebugDrawTime);
	 

	if(IsHit)
	{
		if (IsValid(OutHit.GetActor()) && OutHit.GetActor()->GetClass()->ImplementsInterface(ULabIInteractable::StaticClass()))
		{
			if (IsValid(ActorToInteract)) // Check if the actor to interact is valid.
			{
				if (ActorToInteract != OutHit.GetActor())
				{
					Cast<ILabIInteractable>(ActorToInteract)->VfxDisinteraction();

					ActorToInteract == OutHit.GetActor();
					Cast<ILabIInteractable>(ActorToInteract)->VfxInteraction();
				}
			}
			else if (ActorToInteract == nullptr) // If the actor is not valid check if it is nullptr.
			{
				ActorToInteract = OutHit.GetActor();
				Cast<ILabIInteractable>(ActorToInteract)->VfxInteraction();
			}
			else // If the actor is not valid and is not nullptr, set it to nullptr to avoid errors.
			{
				ActorToInteract = nullptr;
			}
		}
	}
	else
	{
		if (IsValid(ActorToInteract))
		{
			if(ActorToInteract->GetClass()->ImplementsInterface(ULabIInteractable::StaticClass()))
			{
				Cast<ILabIInteractable>(ActorToInteract)->VfxDisinteraction();
			}

			ActorToInteract = nullptr;
		}
	}
}

void ALabEngineerCharacter::CharacterMovement(const float HorizontalMovementValue, const float VerticalMovementValue)
{
	AddMovementInput(GetActorForwardVector(), VerticalMovementValue);
	AddMovementInput(GetActorRightVector(), HorizontalMovementValue);
	SFXCharacterFoosteps();
}

void ALabEngineerCharacter::CharacterLook(const float YawRotationValue, const float PitchRotationValue)
{
	AddControllerYawInput(YawRotationValue);
	AddControllerPitchInput(PitchRotationValue);
}

void ALabEngineerCharacter::CharacterStaticInteraction()
{
	if (IsValid(ActorToInteract))
	{
		Cast<ILabIInteractable>(ActorToInteract)->StaticInteraction();
	}
}

void ALabEngineerCharacter::CharacterDynamicInteraction()
{
	if (IsValid(ActorToInteract))
	{
		Cast<ILabIInteractable>(ActorToInteract)->DynamicInteraction();
	}
}

void ALabEngineerCharacter::TakeDamage()
{
	// Debug Damage
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Character Damaged"));
}

void ALabEngineerCharacter::CheckIfIShouldEndTheEquipmentIHaveOn()
{
	if (const TObjectPtr<ALabGameState> GameStateRef = GetWorld()->GetGameState<ALabGameState>())
	{
		GameStateRef->OnSafetyEquipmentSendDelegate.Broadcast(EngineerSafetyEquipment);
	}
}

void ALabEngineerCharacter::PickUpNewSafetyEquipment(const TEnumAsByte<ESafetyEquipmentType> NewEquipmentCollected)
{
	EngineerSafetyEquipment.Add(NewEquipmentCollected);
}