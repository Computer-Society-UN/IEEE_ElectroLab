
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/UMG/Menus/LabCustomButton.h"
// Unreal Engine Dependencies:
#include "CommonTextBlock.h"

	/* ---------------------------- FUNCTION DEFINITIONS ---------------------------- */

void ULabCustomButton::NativeConstruct()
{
	Super::NativeConstruct();
	DisplayButtonText->SetText(ButtonText);
}