#pragma once
#include "CoreMinimal.h"

#include "RolePlayMessage\RolePlayMessageData\RolePlaySystemData.h"
//#include "RolePlayMessage\RolePlayMessageData\RolePlaySceneData.h"
//#include "RolePlayMessage\RolePlayMessageData\RolePlayCharData.h"
//#include "RolePlayMessage\RolePlayMessageData\RolePlayContextData.h"

#include "RolePlayMessageData.generated.h"

USTRUCT(BlueprintType)
struct OLLAMATESTPROJECT_API FRolePlayMessageData
{
	GENERATED_BODY()

	UPROPERTY()
	FRolePlaySystemData SystemData;

	UPROPERTY()
	TArray<FRolePlayConversationContentData> ConversationContentDatas;

	TArray<TSharedPtr<FJsonValue>> ToJson() const
	{
		TArray<TSharedPtr<FJsonValue>> JsonObjectArray;

		JsonObjectArray.Add(
			MakeShared<FJsonValueObject>(SystemData.ToJson())
		);

		for (const FRolePlayConversationContentData& Data : ConversationContentDatas)
		{
			JsonObjectArray.Add(
				MakeShared<FJsonValueObject>(Data.ToJson())
			);
		}

		return JsonObjectArray;
	}
};