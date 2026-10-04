#pragma once
#include "CoreMinimal.h"
#include "RolePlayMessage\RolePlayMessageData\RolePlayBaseData.h"
#include "RolePlayConversationContentData.h"
#include "RolePlayMemoryData.generated.h"

USTRUCT(BlueprintType)
struct OLLAMATESTPROJECT_API FRolePlayMemoryData :public FRolePlayBaseData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Summary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ImportantEvents;

	TSharedPtr<FJsonObject> ToJson() const override
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();

		JsonObject->SetStringField(TEXT("summary"), Summary);

		JsonObject->SetArrayField(TEXT("important_events"), StringArrayToJson(ImportantEvents));

		return JsonObject;
	}
};