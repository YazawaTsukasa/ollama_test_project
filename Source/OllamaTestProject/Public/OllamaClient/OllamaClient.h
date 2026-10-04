// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "OllamaClient.generated.h"

/**
 * 
 */
UCLASS()
class OLLAMATESTPROJECT_API UOllamaClient : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "OllamaClient_SendMessage")
	bool SendMessage(const FString& Message);

	//UFUNCTION(BlueprintCallable, Category = "OllamaClient_SendMessage")
	bool SendJsonMessages(TArray<TSharedPtr<FJsonValue>> Messages);

	TFunction<void(const FString&)> ResponseReceivedCallback;
	TFunction<void()> ResponseFailedCallback;
private:
	void OnResponseReceived(
		FHttpRequestPtr Request,
		FHttpResponsePtr Response,
		bool bWasSuccessful
	);

	const TCHAR* URL = TEXT("http://localhost:11434/api/chat");
	const TCHAR* Model = TEXT("nemotron-mini:4b");

	bool bIsSendingMessage = false;

	float TimeoutTime = 300.f;
	float ActivityTimeout = 300.f;

	int MaxTokenSize = 250;
};
