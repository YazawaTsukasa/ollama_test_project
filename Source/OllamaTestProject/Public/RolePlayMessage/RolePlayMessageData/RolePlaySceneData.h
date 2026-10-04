#pragma once
#include "CoreMinimal.h"
#include "RolePlaySceneData.generated.h"

USTRUCT(BlueprintType)
struct OLLAMATESTPROJECT_API FRolePlaySceneData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Background;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime CurrentTime;

	TSharedPtr<FJsonObject> ToJson() const
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
		JsonObject->SetStringField(TEXT("background"), Background);
		FString CurrentTimeString = CurrentTime.ToString(TEXT("%Y-%m-%d %H:%M:%S"));
		JsonObject->SetStringField(TEXT("current_time"), CurrentTimeString);

		return JsonObject;
	}
};