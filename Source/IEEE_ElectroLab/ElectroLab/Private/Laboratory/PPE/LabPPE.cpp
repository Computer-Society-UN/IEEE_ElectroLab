
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/Laboratory/PPE/LabPPE.h"
// Unreal Engine Dependencies:
#include "Components/ArrowComponent.h"
// User Defined References:
#include "ElectroLab/Public/Core/LabGameState.h"
#include "ElectroLab/Public/Laboratory/PPE/LabInteractionWidgetContainer.h"
#include "ElectroLab/Public/UMG/Gameplay/LabUWInteractionElement.h"

	/* ---------------------------- FUNCTION DEFINITIONS ---------------------------- */

ALabPPE::ALabPPE()
{
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(FName("PPE Root"));
	RootComponent = CustomRootComponent;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("PPE Mesh"));
	StaticMeshComponent ->SetupAttachment(RootComponent);
	
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(FName("PPE Arrow Direction"));
	ArrowComponent ->SetupAttachment(RootComponent);
}

void ALabPPE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	StaticMeshComponent->AddLocalRotation(FRotator(0.f, 1.f, 0.f));
}

void ALabPPE::StaticInteraction()
{
	SfxInteraction();
	
	if (WidgetPPE)
	{
		GetWorld()->DestroyActor(WidgetPPE);
		WidgetPPE = nullptr;
	}

	if (const TObjectPtr<ALabGameState> GameStateRef = GetWorld()->GetGameState<ALabGameState>())
	{
		GameStateRef->OnNewSafetyEquipmentHasBeenCollectedDelegate.Broadcast(EquipmentType);
	}
	
	Destroy();
}

void ALabPPE::OnGoingDynamicInteraction(const float HoldTime){}

void ALabPPE::CancelDynamicInteraction(){}

void ALabPPE::TriggerDynamicInteraction(){}

void ALabPPE::VfxInteraction()
{
	VfxOverlay(true);

	if (WidgetPPEReference)
	{
		WidgetPPE = GetWorld()->SpawnActor<ALabInteractionWidgetContainer>(WidgetPPEReference,ArrowComponent->GetComponentLocation(),ArrowComponent->GetComponentRotation());
		WidgetPPE->SetComponentNameToDisplay(ComponentName, InteractionType);
	}
}

void ALabPPE::VfxDisinteraction()
{
	VfxOverlay(false);

	if (WidgetPPE)
	{
		GetWorld()->DestroyActor(WidgetPPE);
        WidgetPPE = nullptr;
	}
}