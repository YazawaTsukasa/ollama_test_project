#pragma once
#include "CoreMinimal.h"
#include "RolePlayBaseData.generated.h"

USTRUCT(BlueprintType)
struct OLLAMATESTPROJECT_API FRolePlayBaseData
{
	GENERATED_BODY()

	virtual TSharedPtr<FJsonObject> ToJson() const { return TSharedPtr<FJsonObject>(); }
	virtual TSharedPtr<FJsonObject> ToJson(const FString& RoleName) const { return TSharedPtr<FJsonObject>(); }

	TArray<TSharedPtr<FJsonValue>> StringArrayToJson(const TArray<FString>& StringArray) const
	{
		TArray<TSharedPtr<FJsonValue>> JsonArray;

		for (const FString& String : StringArray)
		{
			JsonArray.Add(MakeShared<FJsonValueString>(String));
		}

		return JsonArray;
	}
};