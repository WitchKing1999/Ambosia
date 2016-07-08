// (C) Flumminard 2015-2016

#pragma once

#include "Quest.generated.h"

UENUM(BlueprintType)
enum class EQuestStatus : uint8
{
	VE_Active UMETA(DisplayName = "Active"),
	VE_Completed UMETA(DisplayName = "Completed"),
	VE_Canceled UMETA(DisplayName = "Canceled")
};

USTRUCT(BlueprintType)
struct FQuest
{
	GENERATED_BODY()
public:
	/*
	Used to identify the quest by the game, not meant to be displayed.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName QuestName;
	/*
	The name of the quest.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText QuestNameText;
	/*
	The description of the quest.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText DescriptionText;
	/*
	The status of the quest.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EQuestStatus Status;
};