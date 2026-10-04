// Fill out your copyright notice in the Description page of Project Settings.


#include "OllamaClient/OllamaClient.h"

bool UOllamaClient::SendMessage(const FString& Message)
{
	if (bIsSendingMessage) return false;

	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField(TEXT("model"), Model);

	TArray<TSharedPtr<FJsonValue>> Messages;

	TSharedPtr<FJsonObject> UserMessage = MakeShared<FJsonObject>();
	UserMessage->SetStringField(TEXT("role"), TEXT("user"));
	UserMessage->SetStringField(TEXT("content"), Message);

	Messages.Add(MakeShared<FJsonValueObject>(UserMessage));
	JsonObject->SetArrayField(TEXT("messages"), Messages);
	JsonObject->SetBoolField(TEXT("stream"), false);

	TSharedPtr<FJsonObject> OptionsJsonObject = MakeShared<FJsonObject>();
	OptionsJsonObject->SetNumberField(TEXT("num_predict"), MaxTokenSize);
	JsonObject->SetObjectField(TEXT("options"), OptionsJsonObject);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);

	FJsonSerializer::Serialize(
		JsonObject.ToSharedRef(),
		Writer
	);

	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	// Ollama 本地 API 地址
	Request->SetURL(URL);
	// HTTP 请求方式
	Request->SetVerb(TEXT("POST"));
	// 告诉 Ollama：请求 Body 中的数据是 JSON
	Request->SetHeader(
		TEXT("Content-Type"),
		TEXT("application/json")
	);
	// 设置 HTTP Body
	// 也就是前面生成的 JSON 字符串
	Request->SetContentAsString(RequestBody);
	// 设置请求超时时间
	Request->SetTimeout(TimeoutTime);
	Request->SetActivityTimeout(ActivityTimeout);
	// 注册 HTTP 请求完成时的回调函数
	// 请求发送完成后：
	// OnResponseReceived() 会被自动调用
	Request->OnProcessRequestComplete().BindUObject(
		this,
		&UOllamaClient::OnResponseReceived
	);
	//UE_LOG(LogTemp, Log, TEXT("Request Ptr: %p"), &Request.Get());
	// 正式发送 HTTP 请求
	UE_LOG(LogTemp, Log, TEXT("Request Body: %s"), *RequestBody);
	bIsSendingMessage = true;
	Request->ProcessRequest();
	return true;
}

bool UOllamaClient::SendJsonMessages(TArray<TSharedPtr<FJsonValue>> Messages)
{
	if (bIsSendingMessage) return false;

	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField(TEXT("model"), Model);

	JsonObject->SetArrayField(TEXT("messages"), Messages);
	JsonObject->SetBoolField(TEXT("stream"), false);

	TSharedPtr<FJsonObject> OptionsJsonObject = MakeShared<FJsonObject>();
	OptionsJsonObject->SetNumberField(TEXT("num_predict"), MaxTokenSize);
	JsonObject->SetObjectField(TEXT("options"), OptionsJsonObject);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);

	FJsonSerializer::Serialize(
		JsonObject.ToSharedRef(),
		Writer
	);

	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	// Ollama 本地 API 地址
	Request->SetURL(URL);
	// HTTP 请求方式
	Request->SetVerb(TEXT("POST"));
	// 告诉 Ollama：请求 Body 中的数据是 JSON
	Request->SetHeader(
		TEXT("Content-Type"),
		TEXT("application/json")
	);
	// 设置 HTTP Body
	// 也就是前面生成的 JSON 字符串
	Request->SetContentAsString(RequestBody);
	// 设置请求超时时间
	Request->SetTimeout(TimeoutTime);
	Request->SetActivityTimeout(ActivityTimeout);
	// 注册 HTTP 请求完成时的回调函数
	// 请求发送完成后：
	// OnResponseReceived() 会被自动调用
	Request->OnProcessRequestComplete().BindUObject(
		this,
		&UOllamaClient::OnResponseReceived
	);
	//UE_LOG(LogTemp, Log, TEXT("Request Ptr: %p"), &Request.Get());
	// 正式发送 HTTP 请求
	UE_LOG(LogTemp, Log, TEXT("Request Body: %s"), *RequestBody);
	bIsSendingMessage = true;
	Request->ProcessRequest();
	return true;
}

void UOllamaClient::OnResponseReceived(
	FHttpRequestPtr Request,
	FHttpResponsePtr Response,
	bool bWasSuccessful)
{
	bIsSendingMessage = false;
	// 检查 HTTP 请求是否成功，以及 Response 是否有效
	UE_LOG(LogTemp, Log, TEXT("Response Request Ptr: %p"), Request.Get());
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Ollama request failed."));
		UE_LOG(LogTemp, Error, TEXT("Ollama request failed. bWasSuccessful=%s, ResponseValid=%s"),
			bWasSuccessful ? TEXT("true") : TEXT("false"),
			Response.IsValid() ? TEXT("true") : TEXT("false"));

		if (Response.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("HTTP Status Code: %d"), Response->GetResponseCode());

			UE_LOG(LogTemp, Error, TEXT("Response: %s"), *Response->GetContentAsString());
		}

		UE_LOG(LogTemp, Error, TEXT("Ollama: Success=%d, ResponseValid=%d, Code=%d"),
			bWasSuccessful,
			Response.IsValid(),
			Response.IsValid() ? Response->GetResponseCode() : -1
		);
		if (Response.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("Ollama Response: %s"), *Response->GetContentAsString());
		}

		if (ResponseFailedCallback) {
			ResponseFailedCallback();
		}

		return;
	}

	// 获取 Ollama 返回的 JSON 字符串
	FString ResponseBody =
		Response->GetContentAsString();
	// 将 Ollama 返回的内容输出到 UE5 Output Log
	UE_LOG(LogTemp, Log, TEXT("Ollama Response: %s"), *ResponseBody);

	// 用于保存解析后的 JSON
	TSharedPtr<FJsonObject> JsonObject;

	// 将 FString 转换成 JSON
	TSharedRef<TJsonReader<>> Reader =
		TJsonReaderFactory<>::Create(ResponseBody);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to parse Ollama response."));
		return;
	}

	// 取得 "message" 对象
	const TSharedPtr<FJsonObject>* MessageObject;
	if (!JsonObject->TryGetObjectField(TEXT("message"), MessageObject))
	{
		UE_LOG(LogTemp, Error, TEXT("Message field not found."));
		return;
	}

	// 取得 message 里面的 "content"
	FString Content;
	if (!(*MessageObject)->TryGetStringField(TEXT("content"), Content))
	{
		UE_LOG(LogTemp, Error, TEXT("Content field not found."));
		return;
	}

	if (ResponseReceivedCallback) {
		ResponseReceivedCallback(Content);
	}
}