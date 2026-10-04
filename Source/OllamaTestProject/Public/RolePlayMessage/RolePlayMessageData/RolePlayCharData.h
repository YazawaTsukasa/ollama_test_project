#pragma once
#include "CoreMinimal.h"
#include "RolePlayMessage\RolePlayMessageData\RolePlayBaseData.h"
#include "RolePlayCharData.generated.h"

USTRUCT(BlueprintType)
struct OLLAMATESTPROJECT_API FRolePlayCharData :public FRolePlayBaseData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Personality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Background;

	TSharedPtr<FJsonObject> ToJson() const override
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();

		JsonObject->SetStringField(TEXT("name"), Name);
		//JsonObject->SetStringField(TEXT("personality"), Personality);
		//JsonObject->SetStringField(TEXT("background"), Background);
		JsonObject->SetArrayField(TEXT("personality"), StringArrayToJson(Personality));
		JsonObject->SetArrayField(TEXT("background"), StringArrayToJson(Background));

		return JsonObject;
	}
};