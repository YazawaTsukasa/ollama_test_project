// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ChatItemData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class OLLAMATESTPROJECT_API UChatItemData : public UObject
{
	GENERATED_BODY()
public:
	UChatItemData();

	UPROPERTY(BlueprintReadWrite)
	int32 Index = -1;

	UPROPERTY(BlueprintReadWrite)
	bool IsAIChar = true;

	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	FString Content;
};
