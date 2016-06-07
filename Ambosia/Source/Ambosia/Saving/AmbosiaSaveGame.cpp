// (C) Flumminard 2015-2016

#include "Ambosia.h"
#include "AmbosiaSaveGame.h"

UAmbosiaSaveGame::UAmbosiaSaveGame()
{
	HealthPoints = 0;
	HealthPointsLimit = 0;
	Mana = 0;
	ManaLimit = 0;
	ManaRegeneration = 0;
	AttackPoints = 0;
	MagicalAttackPoints = 0;
	ExperiencePoints = 0;
	SkillPoints = 0;
	SkillLevel = 0;
	//Quests = TArray<FQuest>();
	Spawnpoint = FTransform(FRotator(0, 0, 0), FVector(0, 0, 0));
	LevelName = FName("/Game/Levels/DebugLevel");
	Items = TArray<UClass*>();
	ItemStacks = TArray<int32>();
	WeaponIndex = -1;
	ArmorIndex = -1;
	PotionIndex = -1;
	ArrowBundleIndex = -1;
	FirstRingIndex = -1;
	SecondRingIndex = -1;
	AmuletIndex = -1;
}