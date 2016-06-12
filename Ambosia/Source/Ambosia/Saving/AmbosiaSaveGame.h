// (C) Flumminard 2015-2016

#pragma once

#include "GameFramework/SaveGame.h"
#include "Structs/Quest.h"
#include "AmbosiaSaveGame.generated.h"

/*
A saving container that contains all relevant
information of the game.
*/
UCLASS()
class AMBOSIA_API UAmbosiaSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UAmbosiaSaveGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Values")
		float HealthPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Values")
		float HealthPointsLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Values")
		float Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Values")
		float ManaLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Values")
		float ManaRegeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Values")
		float AttackPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Values")
		float MagicalAttackPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
		float ExperiencePoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
		float SkillPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
		int32 SkillLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
		TArray<FQuest> Quests;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
		FTransform Spawnpoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
		FName LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<UClass*> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<int32> ItemStacks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 WeaponIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 ArmorIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 PotionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 ArrowBundleIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 FirstRingIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 SecondRingIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 AmuletIndex;

};
