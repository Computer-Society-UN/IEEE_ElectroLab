
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "LaboratoryInfoLibrary.generated.h"

UCLASS()
class IEEE_ELECTROLAB_API ULaboratoryInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */
	
public:
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetAppVersion"), Category = "IEEE Electrolab|Info")
	static FString GetAppVersion();
	
};