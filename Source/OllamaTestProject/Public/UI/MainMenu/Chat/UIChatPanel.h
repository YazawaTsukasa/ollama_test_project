// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
#include "UI/MainMenu/Chat/UIChatItem.h"

#include "UIChatPanel.generated.h"

/**
 * 
 */
UCLASS()
class OLLAMATESTPROJECT_API UUIChatPanel : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "UIChatPanel_Item")
	bool AddObject(UObject* Object);

	void RemoveItem(int32 Index);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIChatPanel_Params")
	int32 UpdateItemNum = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIChatPanel_Params")
	TSubclassOf<UUIChatItem> ChatItemClass = nullptr;

private:
	UFUNCTION(BlueprintCallable, Category = "UIChatPanel_Initialize")
	void InitializComponents(
		UScrollBox* ScrollBoxComponent, UVerticalBox* VerticalBoxComponent);

	UScrollBox* ScrollBox;
	UVerticalBox* VerticalBox;

	UFUNCTION(BlueprintCallable, Category = "UIChatPanel_Item")
	UUIChatItem* CreateNewItem();

	UPROPERTY()
	TMap<int32, UUIChatItem*> ChatItemMap;

};
