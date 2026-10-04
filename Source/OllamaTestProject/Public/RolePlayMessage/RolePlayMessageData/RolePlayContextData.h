#pragma once
#include "CoreMinimal.h"
#include "RolePlayConversationContentData.h"
#include "RolePlayContextData.generated.h"

USTRUCT(BlueprintType)
struct OLLAMATESTPROJECT_API FRolePlayContextData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PastConversationSummary;

	TSharedPtr<FJsonObject> ToJson() const
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();

		JsonObject->SetStringField(TEXT("past_conversation_summary"), PastConversationSummary);

		return JsonObject;
	}
};