// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/UIMainMenu.h"
#include "UI/MainMenu/Chat/ChatItemData.h"
#include "RolePlayMessage\RolePlayMessageData\RolePlayCharData.h"

void UUIMainMenu::InitializeComponents(
	UTextBlock* RecallTextBlockComponent,
	UMultiLineEditableText* InputEditableTextComponent,
	UUIChatPanel* ChatPanelComponent)
{
	RecallTextBlock = RecallTextBlockComponent;
	InputEditableText = InputEditableTextComponent;
	ChatPanel = ChatPanelComponent;
}

void UUIMainMenu::InitializeOllamaClient()
{
	OllamaClient = NewObject<UOllamaClient>(this);

	OllamaClient->ResponseReceivedCallback = [this](const FString& Message)
		{
			OutputResponseReceived(Message);
		};
	OllamaClient->ResponseFailedCallback = [this]() {OnResponseFailed();};
}

void UUIMainMenu::InitializeRolePlayMessageOperator()
{
	RolePlayMessageOperator = NewObject<URolePlayMessageOperator>(this);
}

void UUIMainMenu::SetRolePlayBaseInfomations(
	//const FString& RolePlayRules, const FString& AIGuidelines,
	const TArray<FString>& Must, const TArray<FString>& MustNot,
	//const FString& Background, FDateTime CurrentTime,
	const FString& Location, const FString& Situation, const FString& Atmosphere,
	const FString& AIName, const TArray<FString>& AIPersonality, const TArray<FString>& AIBackground,
	const FString& UserName, const TArray<FString>& UserPersonality, const TArray<FString>& UserBackground,
	//const FString& PastConversationSummary
	const FString& Summary, const TArray<FString>& ImportantEvents
)
{
	if (!IsValid(RolePlayMessageOperator))return;

	//RolePlayMessageOperator->SetSystemData(RolePlayRules, AIGuidelines);
	RolePlayMessageOperator->SetRulesData(Must, MustNot);
	//RolePlayMessageOperator->SetSceneData(Background, CurrentTime);
	RolePlayMessageOperator->SetSceneData(Location, Situation, Atmosphere);
	RolePlayMessageOperator->SetAICharData(AIName, AIPersonality, AIBackground);
	RolePlayMessageOperator->SetUserCharData(UserName, UserPersonality, UserBackground);
	//RolePlayMessageOperator->SetContextData(PastConversationSummary);
	RolePlayMessageOperator->SetMemoryData(Summary, ImportantEvents);
}

void UUIMainMenu::CommitMessage(const FString& Message)
{
	if (not IsValid(OllamaClient)) {
		UE_LOG(LogTemp, Error, TEXT("Not OllamaClient"));
		return;
	}
	if (Message.IsEmpty()) return;

	UE_LOG(LogTemp, Log, TEXT("Send Message: %s"), *Message);

	bool bIsSuccess = OllamaClient->SendMessage(Message);
	UE_LOG(LogTemp, Log, TEXT("Send Message Is %s"), bIsSuccess ? TEXT("Successful") : TEXT("Failed"));
}

void UUIMainMenu::CommitJsonMessages(const FString& Message)
{
	if (not IsValid(OllamaClient)) {
		UE_LOG(LogTemp, Error, TEXT("Not OllamaClient"));
		return;
	}
	if (Message.IsEmpty()) return;

	UE_LOG(LogTemp, Log, TEXT("Send Message: %s"), *Message);

	bool bIsSuccess = OllamaClient->SendJsonMessages(ReadRolePlayMessage(Message));
	UE_LOG(LogTemp, Log, TEXT("Send Message Is %s"), bIsSuccess ? TEXT("Successful") : TEXT("Failed"));
}

void UUIMainMenu::OutputResponseReceived(const FString& Message)
{
	if (not RecallTextBlock) {
		UE_LOG(LogTemp, Error, TEXT("Not RecallTextBlock"));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("Output Response Received: %s"), *Message);
	//AddRolePlayConversation(true, Message);
	CurrentResponseMessage = Message;
	RecallTextBlock->SetText(FText::FromString(Message));

	FRolePlayCharData CharData =
		RolePlayMessageOperator->GetAICharData();
	int32 Index = RolePlayMessageOperator->GetConversationContentDatas().Num() + 1;
	AddChatPanelItem(true, CharData.Name, Message, Index);
}

TArray<TSharedPtr<FJsonValue>> UUIMainMenu::ReadRolePlayMessage(const FString& Message)
{
	if (!RolePlayMessageOperator)return TArray<TSharedPtr<FJsonValue>>();
	AddRolePlayConversation(true, CurrentResponseMessage);
	CurrentResponseMessage = TEXT("");

	int32 Index = RolePlayMessageOperator->GetConversationContentDatas().Num();
	AddRolePlayConversation(false, Message);
	FRolePlayCharData CharData =
		RolePlayMessageOperator->GetUserCharData();
	//UE_LOG(LogTemp, Log, TEXT("AddRolePlayConversation Index: %d "), Index);
	AddChatPanelItem(false, CharData.Name, Message, Index);
	return RolePlayMessageOperator->ReadRolePlayMessage();
}

void UUIMainMenu::AddRolePlayConversation(bool IsFromAIChar, const FString& Content)
{
	if (!RolePlayMessageOperator || Content.IsEmpty())return;
	RolePlayMessageOperator->AddNewConversation(IsFromAIChar, Content);
}

void UUIMainMenu::AddChatPanelItem(
	bool IsFromAIChar, const FString& Name, const FString& Content, int32 Index)
{
	if (!ChatPanel)return;
	UChatItemData* DataObject = NewObject<UChatItemData>(this);
	DataObject->Index = Index;
	DataObject->IsAIChar = IsFromAIChar;
	DataObject->Name = Name;
	DataObject->Content = Content;
	ChatPanel->AddObject(DataObject);
}

void UUIMainMenu::OnResponseFailed()
{
	//UE_LOG(LogTemp, Log, TEXT("OnResponseFailed"));

	if (!IsValid(RolePlayMessageOperator))return;
	int32 Index = RolePlayMessageOperator->GetConversationContentDatas().Num()-1;
	//UE_LOG(LogTemp, Log, TEXT("OnResponseFailed Index: %d "), Index);
	if (Index < 0) {
		//UE_LOG(LogTemp, Warning, TEXT("Index < 0"));
		return;
	}

	FRolePlayConversationContentData Data =
		RolePlayMessageOperator->GetConversationContentDatas()[Index];
	//UE_LOG(LogTemp, Warning, TEXT("IsFromAIChar: %s"), Data.IsFromAIChar?TEXT("Yes"):TEXT("No"));
	if (Data.IsFromAIChar) {
		return;
	}

	FRolePlayConversationContentData PopedData;
	bool Success=RolePlayMessageOperator->PopConversationContentData(PopedData);
	//UE_LOG(LogTemp, Warning, TEXT("PopConversationContentData Success: %s"),
	//	Success ? TEXT("Yes") : TEXT("No"));

	if (ChatPanel) {
		ChatPanel->RemoveItem(Index);
	}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("No ChatPanel"));
	//}
}