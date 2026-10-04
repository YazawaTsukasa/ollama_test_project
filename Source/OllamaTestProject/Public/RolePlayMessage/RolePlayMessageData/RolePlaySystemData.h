#pragma once
#include "CoreMinimal.h"

#include "RolePlayMessage\RolePlayMessageData\RolePlayBaseData.h"
#include "RolePlayMessage\RolePlayMessageData\RolePlaySceneData.h"
#include "RolePlayMessage\RolePlayMessageData\RolePlayCharData.h"
#include "RolePlayMessage\RolePlayMessageData\RolePlayMemoryData.h"
#include "RolePlayMessage\RolePlayMessageData\RolePlayRulesData.h"

#include "RolePlaySystemData.generated.h"

USTRUCT(BlueprintType)
struct OLLAMATESTPROJECT_API FRolePlaySystemData :public FRolePlayBaseData
{
	GENERATED_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//FString RolePlayRules;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//FString AIGuidelines;

	//UPROPERTY()
	//FRolePlayContextData ContextData;

	//------------------------------
	UPROPERTY()
	FRolePlayCharData UserCharData;

	UPROPERTY()
	FRolePlayCharData AICharData;

	UPROPERTY()
	FRolePlaySceneData SceneData;

	UPROPERTY()
	FRolePlayMemoryData MemoryData;

	UPROPERTY()
	FRolePlayRulesData RulesData;

	TSharedPtr<FJsonObject> ToJson(const FString& RoleName = TEXT("system")) const override
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
		JsonObject->SetStringField(TEXT("role"), RoleName);

		TSharedPtr<FJsonObject> ContentJsonObject = MakeShared<FJsonObject>();
		//ContentJsonObject->SetStringField(TEXT("role_play_rules"), RolePlayRules);
		//ContentJsonObject->SetStringField(TEXT("ai_guidelines"), AIGuidelines);
		TSharedPtr<FJsonObject> CharactersJsonObject = MakeShared<FJsonObject>();
		//TSharedPtr<FJsonValue> AICharJsonValue = MakeShared<FJsonValueObject>(AICharData.ToJson());
		CharactersJsonObject->SetObjectField(TEXT("ai"), AICharData.ToJson());
		//TSharedPtr<FJsonValue> UserCharJsonValue = MakeShared<FJsonValueObject>(UserCharData.ToJson());
		CharactersJsonObject->SetObjectField(TEXT("user"), UserCharData.ToJson());
		//TSharedPtr<FJsonValue> ContextJsonValue = MakeShared<FJsonValueObject>(ContextData.ToJson());

		//TSharedPtr<FJsonValue> SceneJsonValue = MakeShared<FJsonValueObject>(SceneData.ToJson());
		//TSharedPtr<FJsonValue> MemoryJsonValue = MakeShared<FJsonValueObject>(MemoryData.ToJson());
		//TSharedPtr<FJsonValue> RulesJsonValue = MakeShared<FJsonValueObject>(RulesData.ToJson());

		//ContentJsonObject->SetField(TEXT("user"), UserCharJsonValue);
		//ContentJsonObject->SetField(TEXT("char"), AICharJsonValue);
		//ContentJsonObject->SetField(TEXT("context"), ContextJsonValue);
		ContentJsonObject->SetField(TEXT("characters"), MakeShared<FJsonValueObject>(CharactersJsonObject));
		ContentJsonObject->SetField(TEXT("scene"), MakeShared<FJsonValueObject>(SceneData.ToJson()));
		ContentJsonObject->SetField(TEXT("memory"), MakeShared<FJsonValueObject>(MemoryData.ToJson()));
		ContentJsonObject->SetField(TEXT("rules"), MakeShared<FJsonValueObject>(RulesData.ToJson()));

		FString ContentJsonString;
		TSharedRef<TJsonWriter<>> Writer =
			TJsonWriterFactory<>::Create(&ContentJsonString);

		FJsonSerializer::Serialize(
			ContentJsonObject.ToSharedRef(),
			Writer
		);

		JsonObject->SetStringField(TEXT("content"), ContentJsonString);

		return JsonObject;
	}
};