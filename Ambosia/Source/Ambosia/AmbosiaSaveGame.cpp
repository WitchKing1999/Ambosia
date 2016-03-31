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
	Spawnpoint = FTransform();
	LevelName = FName();
	Items = TArray<UClass*>();
	ItemStacks = TArray<int32>();
	WeaponIndex = -2;
	ArmorIndex = -2;
	PotionIndex = -2;
	ArrowBundleIndex = -2;
	FirstRingIndex = -2;
	SecondRingIndex = -2;
	AmuletIndex = -2;
}