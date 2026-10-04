// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/Chat/UIChatItem.h"
#include "Components/PanelSlot.h"

void UUIChatItem::InitializeComponents(
	UTextBlock* NameTextBlockComponent,
	UTextBlock* ContentTextBlockComponent)
{
	NameTextBlock = NameTextBlockComponent;
	ContentTextBlock = ContentTextBlockComponent;

	if (NameTextBlock && ChatItemData) {
		NameTextBlock->SetText(FText::FromString(ChatItemData->Name));
		NameTextBlockOverlaySlot = Cast<UOverlaySlot>(NameTextBlock->Slot);
	}
	if (ContentTextBlock && ChatItemData) {
		ContentTextBlock->SetText(FText::FromString(ChatItemData->Content));
	}
}

void UUIChatItem::InitializeObject(UObject* Object)
{
	if (!IsValid(Object)) return;
	ChatItemData = Cast<UChatItemData>(Object);
	if (!ChatItemData)return;

}

void UUIChatItem::InitializeNameTextBlockSlot()
{
	if (!NameTextBlockOverlaySlot)return;

	if (ChatItemData->IsAIChar) {
		NameTextBlockOverlaySlot->SetHorizontalAlignment(
			EHorizontalAlignment::HAlign_Left);
	}
	else{
		NameTextBlockOverlaySlot->SetHorizontalAlignment(
			EHorizontalAlignment::HAlign_Right);
	}
}