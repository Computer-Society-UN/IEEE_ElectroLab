
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/Core/LabGameMode.h"

	/* ---------------------------- FUNCTION DEFINITIONS ---------------------------- */

ALabGameMode::ALabGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALabGameMode::BeginPlay()
{
	Super::BeginPlay();
}