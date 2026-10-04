// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/Chat/UIChatPanel.h"
#include "UI/MainMenu/Chat/ChatItemData.h"

void UUIChatPanel::InitializComponents(
	UScrollBox* ScrollBoxComponent, UVerticalBox* VerticalBoxComponent)
{
	ScrollBox = ScrollBoxComponent;
	VerticalBox = VerticalBoxComponent;
}

bool UUIChatPanel::AddObject(UObject* Object)
{
	if (!Object)return false;

	UChatItemData* DataObject = Cast<UChatItemData>(Object);
	if (!DataObject)return false;
	int32 Index = DataObject->Index;

	UUIChatItem* NewItem = CreateNewItem();
	if (!NewItem)return false;

	ChatItemMap.Add(Index, NewItem);
	UE_LOG(LogTemp, Log, TEXT("ChatItemMap Lenth: %d"), ChatItemMap.Num());

	if (VerticalBox) {
		VerticalBox->AddChildToVerticalBox(NewItem);
	}

	NewItem->OnEntryNewObject(Object);
	return true;
}

UUIChatItem* UUIChatPanel::CreateNewItem()
{
	if (!ChatItemClass)return nullptr;

	UUIChatItem* NewItem = CreateWidget<UUIChatItem>(this, ChatItemClass);
	return NewItem;
}

void UUIChatPanel::RemoveItem(int32 Index)
{
	UUIChatItem** ItemPtr = ChatItemMap.Find(Index);
	if (!ItemPtr || !IsValid(*ItemPtr))
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("RemoveItem Index: %d "),Index);
	if (VerticalBox && VerticalBox->RemoveChild(*ItemPtr))
	{
		UE_LOG(LogTemp, Log, TEXT("RemoveItem Success"));
		ChatItemMap.Remove(Index);
	}
}