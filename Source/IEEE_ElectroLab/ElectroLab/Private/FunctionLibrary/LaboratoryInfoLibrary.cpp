
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/FunctionLibrary/LaboratoryInfoLibrary.h"

FString ULaboratoryInfoLibrary::GetAppVersion()
{
	FString AppVersion;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		AppVersion,
		GGameIni
	);

	return AppVersion;
}