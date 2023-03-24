
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "Engine/DataTable.h"
#include "ElectroLab/Public/Laboratory/PPE/ESafetyEquipmentType.h"
#include "FLaboratoryData.generated.h"

USTRUCT(BlueprintType, meta=(Tooltip="Structure containing the laboratory data."))
struct FLaboratoryData : public FTableRowBase
{
	GENERATED_BODY()
	
	/** The suggested Row Names for DataTables created based on this structure are:  Level_x , where (x) is the numerical ID of the level ( It is also suggested to use this name with the Level names ). */
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="Laboratory Name", Tooltip="Name of the laboratory to be displayed in the Security Room."))
	FText LaboratoryName = { FText::FromString("Laboratory Name") };
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="Equipment To Check", Tooltip="Array containing the necessary equipment for this laboratory."))
	TArray<TEnumAsByte<ESafetyEquipmentType>> EquipmentToCheck = {};
	
};