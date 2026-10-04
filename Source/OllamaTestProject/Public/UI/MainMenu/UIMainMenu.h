// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/MultiLineEditableText.h"
#include "UI/MainMenu/Chat/UIChatPanel.h"

#include "OllamaClient/OllamaClient.h"
#include "RolePlayMessage/RolePlayMessageOperator.h"

#include "UIMainMenu.generated.h"

/**
 *
 */
UCLASS()
class OLLAMATESTPROJECT_API UUIMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

private:
	UFUNCTION(BlueprintCallable, Category = "MainMenuWidget_Components")
	void InitializeComponents(
		UTextBlock* RecallTextBlockComponent,
		UMultiLineEditableText* InputEditableTextComponent,
		UUIChatPanel* ChatPanelComponent);

	UTextBlock* RecallTextBlock;
	UMultiLineEditableText* InputEditableText;
	UUIChatPanel* ChatPanel;

	UPROPERTY()
	UOllamaClient* OllamaClient = nullptr;

	UFUNCTION(BlueprintCallable, Category = "MainMenuWidget_OllamaClient")
	void InitializeOllamaClient();

	UFUNCTION(BlueprintCallable, Category = "MainMenuWidget_RolePlayMessageOperator")
	void InitializeRolePlayMessageOperator();

	UPROPERTY()
	URolePlayMessageOperator* RolePlayMessageOperator;

	UFUNCTION(BlueprintCallable, Category = "MainMenuWidget_RolePlayMessageOperator")
	void SetRolePlayBaseInfomations(
		const FString& RolePlayRules, const FString& AIGuidelines,
		const FString& Background, FDateTime CurrentTime,
		const FString& AIName, const FString& AIPersonality, const FString& AIBackground,
		const FString& UserName, const FString& UserPersonality, const FString& UserBackground,
		const FString& PastConversationSummary
	);

	UFUNCTION(BlueprintCallable, Category = "MainMenuWidget_OllamaClient")
	void CommitMessage(const FString& Message);

	UFUNCTION(BlueprintCallable, Category = "MainMenuWidget_OllamaClient")
	void CommitJsonMessages(const FString& Message);

	void OutputResponseReceived(const FString& Message);

	TArray<TSharedPtr<FJsonValue>> ReadRolePlayMessage(const FString& Message = TEXT(""));

	FString CurrentResponseMessage = TEXT("");

	void AddRolePlayConversation(bool IsFromAIChar, const FString& Content);

	void AddChatPanelItem(
		bool IsFromAIChar, const FString& Name, const FString& Content, int32 Index);

	void OnResponseFailed();
};
