#pragma once
#include "CoreMinimal.h"
#include "RolePlayMessage\RolePlayMessageData\RolePlayBaseData.h"
#include "RolePlayRulesData.generated.h"

USTRUCT(BlueprintType)
struct OLLAMATESTPROJECT_API FRolePlayRulesData :public FRolePlayBaseData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString YouAre;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString OtherCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Must;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> MustNot;

	TSharedPtr<FJsonObject> ToJson() const override
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
		JsonObject->SetStringField(TEXT("you_are"), YouAre);
		JsonObject->SetStringField(TEXT("other_character"), OtherCharacter);
		JsonObject->SetArrayField(TEXT("must"), StringArrayToJson(Must));
		JsonObject->SetArrayField(TEXT("must_not"), StringArrayToJson(MustNot));

		return JsonObject;
	}

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