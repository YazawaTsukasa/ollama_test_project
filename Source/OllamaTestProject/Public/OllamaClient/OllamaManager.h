// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpManager.h"

#include "OllamaManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInitializeEnd, bool, bIsSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCheckOllamaAPIEnd, bool, bIsSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCheckModelEnd, bool, bIsSuccess);

/**
 *
 */
UCLASS(Blueprintable)
class OLLAMATESTPROJECT_API UOllamaManager : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "OllamaManager_Initialize")
	void StartInitializeOllama();

	TFunction<void(bool)> OnCheckOllamaAPICallback;
	TFunction<void(bool)> OnCheckModelCallback;

	UPROPERTY(BlueprintAssignable, Category = "OllamaManager_Initialize")
	FOnInitializeEnd OnInitializeEnd;
	UPROPERTY(BlueprintAssignable, Category = "OllamaManager_Initialize")
	FOnCheckOllamaAPIEnd OnCheckOllamaAPIEnd;
	UPROPERTY(BlueprintAssignable, Category = "OllamaManager_Initialize")
	FOnCheckModelEnd OnCheckModelEnd;
private:
	void NextStepInitializeOllama();
	void FinalStepInitializeOllama(bool bResult);

	void CheckOllamaAPI();
	void OnCheckOllamaAPI(
		FHttpRequestPtr Request,
		FHttpResponsePtr Response,
		bool bWasSuccessful);

	bool CheckIsOllamaInstalledAndLaunch();

	bool LaunchOllama(const FString& OllamaPath);

	void CheckModel();
	void OnCheckModel(
		FHttpRequestPtr Request,
		FHttpResponsePtr Response,
		bool bWasSuccessful);

	UPROPERTY(EditAnywhere, Category = "OllamaManager_Info")
	FString OllamaAPIURL = TEXT("http://localhost:11434/");
	UPROPERTY(EditAnywhere, Category = "OllamaManager_Info")
	FString ModelURL = TEXT("http://localhost:11434/api/tags");
	UPROPERTY(EditAnywhere, Category = "OllamaManager_Info")
	FString UsedModel = TEXT("nemotron-mini:4b");
		//TEXT("nemotron-mini:4b");
		//TEXT("llama3.1:8b");
};
