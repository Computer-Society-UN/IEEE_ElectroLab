
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "ESafetyEquipmentType.generated.h"

UENUM(BlueprintType)
enum ESafetyEquipmentType
{
	EquipmentHardHat			UMETA(DisplayName = "Equipment Hard Hat"),
	EquipmentSafetyGlasses      UMETA(DisplayName = "Equipment Safety Glasses"),
	EquipmentDielectricGloves   UMETA(DisplayName = "Equipment Dielectric Gloves"),
	EquipmentDielectricCoverall UMETA(DisplayName = "Equipment Dielectric Coverall"),
	EquipmentDielectricBoots    UMETA(DisplayName = "Equipment Dielectric Boots")
};