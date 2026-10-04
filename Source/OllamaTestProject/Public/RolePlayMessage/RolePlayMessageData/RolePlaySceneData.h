#pragma once
#include "CoreMinimal.h"
#include "RolePlayMessage\RolePlayMessageData\RolePlayBaseData.h"
#include "RolePlaySceneData.generated.h"

USTRUCT(BlueprintType)
struct OLLAMATESTPROJECT_API FRolePlaySceneData :public FRolePlayBaseData
{
	GENERATED_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//FString Background;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//FDateTime CurrentTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Situation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Atmosphere;

	TSharedPtr<FJsonObject> ToJson() const override
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
		//JsonObject->SetStringField(TEXT("background"), Background);
		//FString CurrentTimeString = CurrentTime.ToString(TEXT("%Y-%m-%d %H:%M:%S"));
		//JsonObject->SetStringField(TEXT("current_time"), CurrentTimeString);
		JsonObject->SetStringField(TEXT("location"), Location);
		JsonObject->SetStringField(TEXT("situation"), Situation);
		JsonObject->SetStringField(TEXT("atmosphere"), Atmosphere);

		return JsonObject;
	}
};