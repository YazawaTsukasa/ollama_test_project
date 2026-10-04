// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ChatItemData.h"
#include "Components/TextBlock.h"
#include "Components/OverlaySlot.h"

#include "UIChatItem.generated.h"

/**
 * 
 */
UCLASS()
class OLLAMATESTPROJECT_API UUIChatItem : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable, Category = "UIChatItem_Event")
	void OnEntryNewObject(UObject* Object);
private:
	UPROPERTY()
	UChatItemData* ChatItemData;

	UFUNCTION(BlueprintCallable, Category = "UIChatItem_Initialize")
	void InitializeObject(UObject* Object);
	
	UFUNCTION(BlueprintCallable, Category = "UIChatItem_Initialize")
	void InitializeComponents(
		UTextBlock* NameTextBlockComponent,
		UTextBlock* ContentTextBlockComponent);

	UTextBlock* NameTextBlock;
	UOverlaySlot* NameTextBlockOverlaySlot;
	UTextBlock* ContentTextBlock;

	UFUNCTION(BlueprintCallable, Category = "UIChatItem_Initialize")
	void InitializeNameTextBlockSlot();
};
