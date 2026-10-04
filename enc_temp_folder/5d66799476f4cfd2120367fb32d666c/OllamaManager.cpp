// Fill out your copyright notice in the Description page of Project Settings.


#include "OllamaClient/OllamaManager.h"

void UOllamaManager::StartInitializeOllama() {
	UE_LOG(LogTemp, Log, TEXT("StartInitializeOllama"));
	CheckOllamaAPI();
}

void UOllamaManager::NextStepInitializeOllama() {
	UE_LOG(LogTemp, Log, TEXT("NextStepInitializeOllama"));
	bool Result=CheckIsOllamaInstalledAndLaunch();
	if (!Result) {
		OnInitializeEnd.Broadcast(false);
	}
	else {
		CheckModel();
	}
}

void UOllamaManager::FinalStepInitializeOllama(bool bResult) {
	UE_LOG(LogTemp, Log, TEXT("FinalStepInitializeOllama"));
	OnInitializeEnd.Broadcast(bResult);
}

void UOllamaManager::CheckOllamaAPI()
{
	FHttpModule& HttpModule =
		FModuleManager::LoadModuleChecked<FHttpModule>(TEXT("HTTP"));

	TSharedRef<IHttpRequest> Request = HttpModule.CreateRequest();
	Request->SetURL(OllamaAPIURL);
	Request->SetVerb(TEXT("GET"));
	Request->OnProcessRequestComplete().BindUObject(
		this,
		&UOllamaManager::OnCheckOllamaAPI
	);
	Request->ProcessRequest();
}

void UOllamaManager::OnCheckOllamaAPI(
	FHttpRequestPtr Request,
	FHttpResponsePtr Response,
	bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Ollama API is unavailable."));
		return;
	}

	UE_LOG(
		LogTemp,
		Log,
		TEXT("Ollama API Response: %s"),
		*Response->GetContentAsString()
	);

	bool bResult;
	if (bWasSuccessful && Response.IsValid())
	{
		// API 可用
		bResult = true;
	}
	else
	{
		// API 不可用
		bResult = false;
	}

	if (OnCheckOllamaAPICallback) {
		OnCheckOllamaAPICallback(bResult);
	}
	OnCheckOllamaAPIEnd.Broadcast(bResult);
	if (bResult)NextStepInitializeOllama();
}

bool UOllamaManager::CheckIsOllamaInstalledAndLaunch()
{
	FString OllamaPath;
	FString StdOut;
	FString StdErr;
	int32 ReturnCode = 0;
	FPlatformProcess::ExecProcess(
		TEXT("where.exe"),
		TEXT("ollama"),
		&ReturnCode,
		&StdOut,
		&StdErr
	);
	if (ReturnCode == 0)
	{
		OllamaPath = StdOut.TrimStartAndEnd();
	}

	UE_LOG(LogTemp, Warning, TEXT("OllamaPath: %s"), *OllamaPath);

	if (FPaths::FileExists(OllamaPath)) {
		return LaunchOllama(OllamaPath);
	}
	else {
		return false;
	}
}

bool UOllamaManager::LaunchOllama(const FString& OllamaPath)
{
	FProcHandle OllamaProcessHandle;
	uint32 ProcessID = 0;
	OllamaProcessHandle = FPlatformProcess::CreateProc(
		*OllamaPath,
		TEXT("serve"),
		false,
		false,
		false,
		&ProcessID,
		0,
		nullptr,
		nullptr
	);
	if (OllamaProcessHandle.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Ollama process started."));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to start Ollama."));
		return false;
	}
}

void UOllamaManager::CheckModel()
{
	TSharedRef<IHttpRequest> Request =
		FHttpModule::Get().CreateRequest();
	Request->SetURL(ModelURL);
	Request->SetVerb(TEXT("GET"));
	Request->OnProcessRequestComplete().BindUObject(
		this,
		&UOllamaManager::OnCheckModel
	);
	Request->ProcessRequest();
}

void UOllamaManager::OnCheckModel(
	FHttpRequestPtr Request,
	FHttpResponsePtr Response,
	bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Model Check is unavailable."));
		return;
	}

	UE_LOG(
		LogTemp,
		Log,
		TEXT("Model Check Response: %s"),
		*Response->GetContentAsString()
	);

	// 解析 JSON
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader =
		TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (!FJsonSerializer::Deserialize(Reader, JsonObject)) {
		return;
	}

	// 取得
	const TArray<TSharedPtr<FJsonValue>>* Models;
	if (!JsonObject->TryGetArrayField(TEXT("models"), Models)) {
		return;
	}

	//读取
	bool bResult = false;
	for (const TSharedPtr<FJsonValue>& ModelValue : *Models)
	{
		const TSharedPtr<FJsonObject>* ModelObject;
		if (!ModelValue->TryGetObject(ModelObject))
		{
			continue;
		}
		FString ModelName;
		if ((*ModelObject)->TryGetStringField(TEXT("name"), ModelName))
		{
			UE_LOG(LogTemp, Log, TEXT("Installed Model: %s"), *ModelName);
			if (ModelName == UsedModel)
			{
				UE_LOG(LogTemp, Log, TEXT("Used Model %s exists."), *UsedModel);
				bResult = true;
			}
		}
	}

	if (OnCheckModelCallback)OnCheckModelCallback(bResult);
	OnCheckModelEnd.Broadcast(bResult);
	FinalStepInitializeOllama(bResult);
}