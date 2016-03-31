// (C) Flumminard 2015-2016

#include "Ambosia.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "BaseSavepoint.h"


// Sets default values
ABaseSavepoint::ABaseSavepoint()
{
	OnActorBeginOverlap.AddDynamic(this, &ABaseSavepoint::OnOverlapBegin);
}

void ABaseSavepoint::OnOverlapBegin(class AActor* OtherActor)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (OtherActor == PlayerController->GetPawn())
	{
		AAmbosiaPlayerController* PlayerController = Cast<AAmbosiaPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		if (!PlayerController)
		{
			return;
		}
		UGameplaySystemComponent* GameplaySystem = PlayerController->GetGameplaySystem();

		UAmbosiaSaveGame* SaveGame = Cast<UAmbosiaSaveGame>(UGameplayStatics::CreateSaveGameObject(UAmbosiaSaveGame::StaticClass()));
		if (!SaveGame)
		{
			return;
		}

		bool SavingSuccessfull = true;

		if (!this->SaveGameplayValues(SaveGame, PlayerController, GameplaySystem))
		{
			SavingSuccessfull = false;
		}
		if (!this->SavePosition(SaveGame))
		{
			SavingSuccessfull = false;
		}
		if (!this->SaveItems(SaveGame, GameplaySystem))
		{
			SavingSuccessfull = false;
		}
		if (!UGameplayStatics::SaveGameToSlot(SaveGame, "Ambosia", 0))
		{
			SavingSuccessfull = false;
		}

		if (SavingSuccessfull)
		{
			UKismetSystemLibrary::PrintString(this, "Game Saved!");
		}
		else
		{
			UKismetSystemLibrary::PrintString(this, "Game Saving failed!");
		}
	}
}

bool ABaseSavepoint::SaveGameplayValues(UAmbosiaSaveGame* SaveGame, AAmbosiaPlayerController* PlayerController, UGameplaySystemComponent* GameplaySystem)
{
	SaveGame->HealthPoints = GameplaySystem->GetHealthPoints();
	SaveGame->HealthPointsLimit = GameplaySystem->GetHealthPointsLimit();
	SaveGame->Mana = GameplaySystem->GetMana();
	SaveGame->ManaLimit = GameplaySystem->GetRawManaLimit();
	SaveGame->ManaRegeneration = GameplaySystem->GetRawManaRegenerationPerSec();
	SaveGame->AttackPoints = GameplaySystem->GetRawAttackPoints();
	SaveGame->MagicalAttackPoints = GameplaySystem->GetRawMagicalAttackPoints();
	SaveGame->ExperiencePoints = PlayerController->GetExperiencePoints();
	SaveGame->SkillPoints = PlayerController->GetSkillPoints();
	SaveGame->SkillLevel = PlayerController->GetCurrentLevel();
	return true;
}

bool ABaseSavepoint::SavePosition(UAmbosiaSaveGame* SaveGame)
{
	SaveGame->Spawnpoint = FTransform(this->GetActorRotation(), this->GetActorRotation().RotateVector(FVector(96, 0, 0)) + this->GetActorLocation());
	SaveGame->LevelName = TargetWorldName;
	return true;
}

bool ABaseSavepoint::SaveItems(UAmbosiaSaveGame* SaveGame, UGameplaySystemComponent* GameplaySystem)
{
	TArray<USceneComponent*> Items;
	GameplaySystem->GetChildrenComponents(false, Items);
	for (int x = 0; x < Items.Num(); x++)
	{
		UItemComponent* Item = Cast<UItemComponent>(Items[x]);
		if (Item)
		{
			SaveGame->Items.Add(Item->GetClass());
			SaveGame->ItemStacks.Add(Item->GetStackSize());
			if (Item == GameplaySystem->GetWeapon())
				SaveGame->WeaponIndex = x;
			if (Item == GameplaySystem->GetArmor())
				SaveGame->ArmorIndex = x;
			if (Item == GameplaySystem->GetPotion())
				SaveGame->PotionIndex = x;
			if (Item == GameplaySystem->GetArrowBundle())
				SaveGame->ArrowBundleIndex = x;
			if (Item == GameplaySystem->GetFirstRing())
				SaveGame->FirstRingIndex = x;
			if (Item == GameplaySystem->GetSecondRing())
				SaveGame->SecondRingIndex = x;
			if (Item == GameplaySystem->GetAmulet())
				SaveGame->AmuletIndex = x;
		}
	}
	return true;
}