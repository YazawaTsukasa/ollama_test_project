#pragma once
#include "CoreMinimal.h"
#include "RolePlayConversationContentData.generated.h"

USTRUCT(BlueprintType)
struct OLLAMATESTPROJECT_API FRolePlayConversationContentData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFromAIChar = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Content;

	TSharedPtr<FJsonObject> ToJson() const
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
		FString RoleName = IsFromAIChar ? TEXT("assistant") : TEXT("user");
		JsonObject->SetStringField(TEXT("role"), RoleName);
		JsonObject->SetStringField(TEXT("content"), Content);

		return JsonObject;
	}
};