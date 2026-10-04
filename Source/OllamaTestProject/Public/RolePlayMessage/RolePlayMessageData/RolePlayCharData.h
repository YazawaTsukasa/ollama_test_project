#pragma once
#include "CoreMinimal.h"
#include "RolePlayCharData.generated.h"

USTRUCT(BlueprintType)
struct OLLAMATESTPROJECT_API FRolePlayCharData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Personality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Background;

	TSharedPtr<FJsonObject> ToJson() const
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();

		JsonObject->SetStringField(TEXT("name"), Name);
		JsonObject->SetStringField(TEXT("personality"), Personality);
		JsonObject->SetStringField(TEXT("background"), Background);

		return JsonObject;
	}
};