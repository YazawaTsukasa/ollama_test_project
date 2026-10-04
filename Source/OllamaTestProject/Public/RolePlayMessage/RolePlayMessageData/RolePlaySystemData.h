#pragma once
#include "CoreMinimal.h"

#include "RolePlayMessage\RolePlayMessageData\RolePlaySceneData.h"
#include "RolePlayMessage\RolePlayMessageData\RolePlayCharData.h"
#include "RolePlayMessage\RolePlayMessageData\RolePlayContextData.h"

#include "RolePlaySystemData.generated.h"

USTRUCT(BlueprintType)
struct OLLAMATESTPROJECT_API FRolePlaySystemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RolePlayRules;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AIGuidelines;

	UPROPERTY()
	FRolePlaySceneData SceneData;
	UPROPERTY()
	FRolePlayCharData UserCharData;
	UPROPERTY()
	FRolePlayCharData AICharData;
	UPROPERTY()
	FRolePlayContextData ContextData;

	TSharedPtr<FJsonObject> ToJson(const FString& RoleName=TEXT("system")) const
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
		TSharedPtr<FJsonObject> ContentJsonObject = MakeShared<FJsonObject>();
		ContentJsonObject->SetStringField(TEXT("role_play_rules"), RolePlayRules);
		ContentJsonObject->SetStringField(TEXT("ai_guidelines"), AIGuidelines);
		TSharedPtr<FJsonValue> SceneJsonValue = MakeShared<FJsonValueObject>(SceneData.ToJson());
		TSharedPtr<FJsonValue> UserCharJsonValue = MakeShared<FJsonValueObject>(UserCharData.ToJson());
		TSharedPtr<FJsonValue> AICharJsonValue = MakeShared<FJsonValueObject>(AICharData.ToJson());
		TSharedPtr<FJsonValue> ContextJsonValue = MakeShared<FJsonValueObject>(ContextData.ToJson());
		ContentJsonObject->SetField(TEXT("scene"), SceneJsonValue);
		ContentJsonObject->SetField(TEXT("user"), UserCharJsonValue);
		ContentJsonObject->SetField(TEXT("char"), AICharJsonValue);
		ContentJsonObject->SetField(TEXT("context"), ContextJsonValue);

		JsonObject->SetStringField(TEXT("role"), RoleName);

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