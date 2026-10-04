// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "RolePlayMessage\RolePlayMessageData\RolePlayMessageData.h"
#include "RolePlayMessage\RolePlayMessageData\RolePlaySystemData.h"
#include "RolePlayMessage\RolePlayMessageData\RolePlayRulesData.h"
#include "RolePlayMessage\RolePlayMessageData\RolePlaySceneData.h"
#include "RolePlayMessage\RolePlayMessageData\RolePlayCharData.h"
#include "RolePlayMessage\RolePlayMessageData\RolePlayMemoryData.h"
//#include "RolePlayMessage\RolePlayMessageData\RolePlayContextData.h"

#include "RolePlayMessageOperator.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class OLLAMATESTPROJECT_API URolePlayMessageOperator : public UObject
{
	GENERATED_BODY()
public:
	URolePlayMessageOperator();

	void InitRolePlayMessageData();

	TArray<TSharedPtr<FJsonValue>> ReadRolePlayMessage();

	UFUNCTION(BlueprintCallable, Category = "RolePlayMessageOperator_ConversationContentData")
	void AddNewConversation(bool IsFromAIChar, const FString& Content);
	UFUNCTION(BlueprintCallable, Category = "RolePlayMessageOperator_ConversationContentData")
	TArray<FRolePlayConversationContentData> GetConversationContentDatas() const;
	UFUNCTION(BlueprintCallable, Category = "RolePlayMessageOperator_ConversationContentData")
	bool PopConversationContentData(
		FRolePlayConversationContentData& Data, int32 Index = -1);

	UFUNCTION(BlueprintCallable, Category = "RolePlayMessageOperator_Data")
	//bool SetSystemData(const FString& RolePlayRules, const FString& AIGuidelines);
	bool SetRulesData(const TArray<FString>& Must, const TArray<FString>& MustNot);
	UFUNCTION(BlueprintCallable, Category = "RolePlayMessageOperator_Data")
	//bool SetSceneData(const FString& Background, FDateTime CurrentTime);
	bool SetSceneData(const FString& Location, const FString& Situation, const FString& Atmosphere);
	UFUNCTION(BlueprintCallable, Category = "RolePlayMessageOperator_Data")
	bool SetUserCharData(const FString& Name, const TArray<FString>& Personality, const TArray<FString>& Background);
	UFUNCTION(BlueprintCallable, Category = "RolePlayMessageOperator_Data")
	bool SetAICharData(const FString& Name, const TArray<FString>& Personality, const TArray<FString>& Background);
	UFUNCTION(BlueprintCallable, Category = "RolePlayMessageOperator_Data")
	//bool SetContextData(const FString& PastConversationSummary);
	bool SetMemoryData(const FString& Summary, const TArray<FString>& ImportantEvents);

	UFUNCTION(BlueprintCallable, Category = "RolePlayMessageOperator_Data")
	FRolePlaySystemData GetSystemData() const;
	UFUNCTION(BlueprintCallable, Category = "RolePlayMessageOperator_Data")
	FRolePlayRulesData GetRulesData() const;
	UFUNCTION(BlueprintCallable, Category = "RolePlayMessageOperator_Data")
	FRolePlaySceneData GetSceneData() const;
	UFUNCTION(BlueprintCallable, Category = "RolePlayMessageOperator_Data")
	FRolePlayCharData GetUserCharData() const;
	UFUNCTION(BlueprintCallable, Category = "RolePlayMessageOperator_Data")
	FRolePlayCharData GetAICharData() const;
	UFUNCTION(BlueprintCallable, Category = "RolePlayMessageOperator_Data")
	//FRolePlayContextData GetContextData() const;
	FRolePlayMemoryData GetMemoryData() const;

private:
	UPROPERTY()
	FRolePlayMessageData RolePlayMessageData;

	//UPROPERTY()
	//FRolePlaySystemData RolePlaySystemData;

	FString JsonToString(TSharedPtr<FJsonObject> JsonObject);
};
