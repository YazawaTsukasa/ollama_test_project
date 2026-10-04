// Fill out your copyright notice in the Description page of Project Settings.
#include "RolePlayMessage/RolePlayMessageOperator.h"

URolePlayMessageOperator::URolePlayMessageOperator()
{
	//UE_LOG(LogTemp, Log, TEXT("RolePlayMessageOperator Construct."));
	//RolePlayMessageData = FRolePlayMessageData();

	//SetSystemData(
	//	TEXT("进行角色扮演。你必须始终扮演AI角色，不得扮演用户角色。"),
	//	TEXT("你扮演char字段中的角色。user字段中的角色由用户控制。你只能以char角色的身份回应，不得代替user角色发言、行动、思考或决定其行为。")
	//);
	//SetSceneData(
	//	TEXT("这里是一座位于海边的旧港口城市。夜晚，港口附近十分安静，只有少量商船停泊。"),
	//	FDateTime(2026, 9, 27, 21, 30, 00)
	//);
	//SetUserCharData(
	//	TEXT("林"),
	//	TEXT("谨慎、理性，不喜欢轻易相信陌生人。"),
	//	TEXT("一名刚来到港口城市的旅行者，正在寻找一艘能够前往北方大陆的船。")
	//);
	//SetAICharData(
	//	TEXT("艾琳"),
	//	TEXT("冷静、警惕，但愿意帮助有困难的人。"),
	//	TEXT("一名年轻的商船船长，经营自己的小型商船，经常往返于南方港口和北方大陆。")
	//);
	//SetContextData(
	//	TEXT("林刚刚来到港口城市，目前正在寻找前往北方大陆的船只。"));
	//AddNewConversation(
	//	false, TEXT("你好，我正在寻找前往北方大陆的船只，我希望能有一艘有丰富水手的船，你能帮我吗？"));
	//AddNewConversation(
	//	true, TEXT("当然啦，我当然愿意帮你。我们这里正好有一艘船适合你，编号是 K-7392。"));
}

void URolePlayMessageOperator::InitRolePlayMessageData() {
	RolePlayMessageData = FRolePlayMessageData();
}

TArray<TSharedPtr<FJsonValue>> URolePlayMessageOperator::ReadRolePlayMessage()
{
	return RolePlayMessageData.ToJson();
}

void URolePlayMessageOperator::AddNewConversation(bool IsFromAIChar, const FString& Content)
{
	FRolePlayConversationContentData ContentData;
	ContentData.IsFromAIChar = IsFromAIChar;
	ContentData.Content = Content;
	RolePlayMessageData.ConversationContentDatas.Add(ContentData);
}

TArray<FRolePlayConversationContentData> URolePlayMessageOperator::GetConversationContentDatas() const
{
	return RolePlayMessageData.ConversationContentDatas;
}

bool URolePlayMessageOperator::PopConversationContentData(
	FRolePlayConversationContentData& Data, int32 Index)
{
	if (RolePlayMessageData.ConversationContentDatas.IsEmpty())
		return false;
	if (Index == -1) {
		Data = RolePlayMessageData.ConversationContentDatas.Pop();
		return true;
	}
	if (!RolePlayMessageData.ConversationContentDatas.IsValidIndex(Index))
		return false;
	Data = RolePlayMessageData.ConversationContentDatas[Index];
	RolePlayMessageData.ConversationContentDatas.RemoveAt(Index);
	return true;
}

//bool URolePlayMessageOperator::SetSystemData(
//	const FString& RolePlayRules, const FString& AIGuidelines)
//{
//	if (RolePlayRules.IsEmpty() || AIGuidelines.IsEmpty()) return false;
//	RolePlayMessageData.SystemData.RolePlayRules = RolePlayRules;
//	RolePlayMessageData.SystemData.AIGuidelines = AIGuidelines;
//	return true;
//}
bool URolePlayMessageOperator::SetRulesData(
	const TArray<FString>& Must, const TArray<FString>& MustNot)
{
	RolePlayMessageData.SystemData.RulesData.Must = Must;
	RolePlayMessageData.SystemData.RulesData.MustNot= MustNot;
	return true;
}

//bool URolePlayMessageOperator::SetSceneData(
//	const FString& Background, FDateTime CurrentTime)
//{
//	if (Background.IsEmpty())return false;
//	RolePlayMessageData.SystemData.SceneData.Background = Background;
//	RolePlayMessageData.SystemData.SceneData.CurrentTime = CurrentTime;
//	return true;
//}
bool URolePlayMessageOperator::SetSceneData(const FString& Location, const FString& Situation, const FString& Atmosphere)
{
	if (Location.IsEmpty()|| Situation.IsEmpty()||Atmosphere.IsEmpty())return false;
	RolePlayMessageData.SystemData.SceneData.Location = Location;
	RolePlayMessageData.SystemData.SceneData.Situation = Situation;
	RolePlayMessageData.SystemData.SceneData.Atmosphere = Atmosphere;
	return true;
}

bool URolePlayMessageOperator::SetUserCharData(
	const FString& Name, const TArray<FString>& Personality, const TArray<FString>& Background)
{
	if (Name.IsEmpty() || Personality.IsEmpty() || Background.IsEmpty())return false;
	RolePlayMessageData.SystemData.UserCharData.Name = Name;
	RolePlayMessageData.SystemData.UserCharData.Personality = Personality;
	RolePlayMessageData.SystemData.UserCharData.Background = Background;
	return true;
}

bool URolePlayMessageOperator::SetAICharData(
	const FString& Name, const TArray<FString>& Personality, const TArray<FString>& Background)
{
	if (Name.IsEmpty() || Personality.IsEmpty() || Background.IsEmpty())return false;
	RolePlayMessageData.SystemData.AICharData.Name = Name;
	RolePlayMessageData.SystemData.AICharData.Personality = Personality;
	RolePlayMessageData.SystemData.AICharData.Background = Background;
	return true;
}

//bool URolePlayMessageOperator::SetContextData(const FString& PastConversationSummary)
//{
//	if (PastConversationSummary.IsEmpty())return false;
//	RolePlayMessageData.SystemData.ContextData.PastConversationSummary = PastConversationSummary;
//	return true;
//}
bool URolePlayMessageOperator::SetMemoryData(
	const FString& Summary, const TArray<FString>& ImportantEvents)
{
	if (Summary.IsEmpty())return false;
	RolePlayMessageData.SystemData.MemoryData.Summary = Summary;
	RolePlayMessageData.SystemData.MemoryData.ImportantEvents = ImportantEvents;
	return true;
}

FRolePlaySystemData URolePlayMessageOperator::GetSystemData() const
{
	return RolePlayMessageData.SystemData;
}

FRolePlayRulesData URolePlayMessageOperator::GetRulesData() const
{
	return RolePlayMessageData.SystemData.RulesData;
}

FRolePlaySceneData URolePlayMessageOperator::GetSceneData() const
{
	return RolePlayMessageData.SystemData.SceneData;
}

FRolePlayCharData URolePlayMessageOperator::GetUserCharData() const
{
	return RolePlayMessageData.SystemData.UserCharData;
}

FRolePlayCharData URolePlayMessageOperator::GetAICharData() const
{
	return RolePlayMessageData.SystemData.AICharData;
}

//FRolePlayContextData URolePlayMessageOperator::GetContextData() const
//{
//	return RolePlayMessageData.SystemData.ContextData;
//}
FRolePlayMemoryData URolePlayMessageOperator::GetMemoryData() const
{
	return RolePlayMessageData.SystemData.MemoryData;
}


FString URolePlayMessageOperator::JsonToString(TSharedPtr<FJsonObject> JsonObject)
{
	FString JsonString;

	TSharedRef<TJsonWriter<>> Writer =
		TJsonWriterFactory<>::Create(&JsonString);

	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	return JsonString;
}