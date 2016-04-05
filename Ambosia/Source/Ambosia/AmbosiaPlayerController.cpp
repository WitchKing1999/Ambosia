// (C) Flumminard 2015-2016

#include "Ambosia.h"

#include "Saving/MetaSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "AmbosiaPlayerController.h"

AAmbosiaPlayerController::AAmbosiaPlayerController()
{
	GameplaySystem = CreateDefaultSubobject<UGameplaySystemComponent>(TEXT("GameplaySystemComponent"));

	LookRate = 2;

	XPLevels = TArray<float>();
	XPLevels.Add(0);
	XPLevels.Add(5);
	XPLevels.Add(20);
	XPLevels.Add(40);

	SkillPointsList = TArray<float>();
	SkillPointsList.Add(0);
	SkillPointsList.Add(5);
	SkillPointsList.Add(20);
	SkillPointsList.Add(40);

}

void AAmbosiaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	this->LoadSaveGame();
	
	InputComponent->BindAxis("MoveForward", this, &AAmbosiaPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AAmbosiaPlayerController::MoveRight);
	InputComponent->BindAxis("LookRight", this, &AAmbosiaPlayerController::LookRight);
	
	InputComponent->BindAction("Attack", IE_Pressed, this, &AAmbosiaPlayerController::AttackPressed);
	InputComponent->BindAction("Potion", IE_Pressed, this, &AAmbosiaPlayerController::PotionPressed);
	InputComponent->BindAction("MainMenu", IE_Pressed, this, &AAmbosiaPlayerController::MainMenuPressed);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &AAmbosiaPlayerController::InventoryPressed);
}

void AAmbosiaPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GameplaySystem->DestroyComponent();
}

float AAmbosiaPlayerController::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UDamageType* DamageType = Cast<UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject(true));
	return GameplaySystem->TakeDamage(DamageAmount, DamageType, EventInstigator, DamageCauser);
}

void AAmbosiaPlayerController::MoveForward(float AxisValue)
{
	this->GetPawn()->AddMovementInput(this->GetControlRotation().Vector(), AxisValue);
}

void AAmbosiaPlayerController::MoveRight(float AxisValue)
{
	FVector WorldDirection = this->GetControlRotation().Vector();
	WorldDirection = FRotator(0, 90, 0).RotateVector(WorldDirection);
	this->GetPawn()->AddMovementInput(WorldDirection, AxisValue);
}

void AAmbosiaPlayerController::LookRight(float AxisValue)
{
	this->AddYawInput(AxisValue * LookRate);
}

void AAmbosiaPlayerController::AttackPressed()
{
	if (GameplaySystem->GetWeapon())
	{
		GameplaySystem->GetWeapon()->Action();
	}
}

void AAmbosiaPlayerController::PotionPressed()
{
	if (GameplaySystem->GetPotion())
	{
		GameplaySystem->GetPotion()->Action();
	}
}

void AAmbosiaPlayerController::MainMenuPressed()
{
	UGameplayStatics::OpenLevel(this, "/Game/Menues/MainMenuWorld", true);
}

void AAmbosiaPlayerController::InventoryPressed()
{
	this->SpendSkillPoints(5, ESkillableValue::VE_HealthPointsLimit);
}

void AAmbosiaPlayerController::ReceiveLoot(TArray<UClass*> ItemClasses, TArray<int32> ItemStacks, float Experience)
{
	ExperiencePoints += Experience;

	bool NewLevelReached = false;
	while (!NewLevelReached)
	{
		if (CurrentLevel + 1 < this->XPLevels.Num())
		{
			if (ExperiencePoints >= this->XPLevels[CurrentLevel + 1])
			{
				CurrentLevel++;
				SkillPoints += SkillPointsList[CurrentLevel];
				NewLevelReached = false;
			}
			else
			{
				NewLevelReached = true;
			}
		}
		else
		{
			NewLevelReached = true;
		}
	}
	
	for (int32 x = 0; x < ItemClasses.Num(); x++)
	{
		GameplaySystem->CreateAndAddItem(ItemClasses[x])->SetStackSize(ItemStacks[x]);
	}
}

void AAmbosiaPlayerController::SpendSkillPoints(float Amount, ESkillableValue Value)
{
	if (this->SkillPoints >= Amount)
	{
		switch (Value)
		{
		case ESkillableValue::VE_HealthPointsLimit:
			GameplaySystem->SetHealthPointsLimit(GameplaySystem->GetHealthPointsLimit() + Amount);
			break;
		case ESkillableValue::VE_ManaLimit:
			GameplaySystem->SetManaLimit(GameplaySystem->GetManaLimit() + Amount);
			break;
		case ESkillableValue::VE_ManaRegeneration:
			GameplaySystem->SetManaRegenerationPerSec(GameplaySystem->GetManaRegenerationPerSec() + Amount);
			break;
		case ESkillableValue::VE_AttackPoints:
			GameplaySystem->SetAttackPoints(GameplaySystem->GetAttackPoints() + Amount);
			break;
		case ESkillableValue::VE_MagicalAttackPoints:
			GameplaySystem->SetMagicalAttackPoints(GameplaySystem->GetMagicalAttackPoints() + Amount);
			break;
		default:
			break;
		}
		SkillPoints -= Amount;
	}
}

bool AAmbosiaPlayerController::SaveSaveGame()
{
	UMetaSaveGame* MetaSG = Cast<UMetaSaveGame>(UGameplayStatics::LoadGameFromSlot("Meta", 0));
	if (!MetaSG)
	{
		return false;
	}

	UAmbosiaSaveGame* SaveGame = Cast<UAmbosiaSaveGame>(UGameplayStatics::CreateSaveGameObject(UAmbosiaSaveGame::StaticClass()));
	if (!SaveGame)
	{
		return false;
	}

	bool SavingSuccessfull = true;

	if (!this->SaveGameplayValues(SaveGame))
	{
		SavingSuccessfull = false;
	}
	if (!this->SavePosition(SaveGame))
	{
		SavingSuccessfull = false;
	}
	if (!this->SaveItems(SaveGame))
	{
		SavingSuccessfull = false;
	}
	if (!UGameplayStatics::SaveGameToSlot(SaveGame, MetaSG->GetCurrentUserName(), MetaSG->CurrentUserIndex))
	{
		SavingSuccessfull = false;
	}

	if (SavingSuccessfull)
	{
		UKismetSystemLibrary::PrintString(this, "Game Saved!");
		return true;
	}
	else
	{
		return false;
	}
}

bool AAmbosiaPlayerController::SaveGameplayValues(UAmbosiaSaveGame* Savegame)
{
	Savegame->HealthPoints = GameplaySystem->GetHealthPoints();
	Savegame->HealthPointsLimit = GameplaySystem->GetHealthPointsLimit();
	Savegame->Mana = GameplaySystem->GetMana();
	Savegame->ManaLimit = GameplaySystem->GetRawManaLimit();
	Savegame->ManaRegeneration = GameplaySystem->GetRawManaRegenerationPerSec();
	Savegame->AttackPoints = GameplaySystem->GetRawAttackPoints();
	Savegame->MagicalAttackPoints = GameplaySystem->GetRawMagicalAttackPoints();
	Savegame->ExperiencePoints = ExperiencePoints;
	Savegame->SkillPoints = SkillPoints;
	Savegame->SkillLevel = CurrentLevel;
	return true;
}

bool AAmbosiaPlayerController::SaveItems(UAmbosiaSaveGame* SaveGame)
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
		else
			return false;
	}
	return true;
}

bool AAmbosiaPlayerController::SavePosition(UAmbosiaSaveGame* Savegame)
{
	Savegame->Spawnpoint = this->GetPawn()->GetTransform();
	Savegame->LevelName = CurrentWorldPath;
	return true;
}

bool AAmbosiaPlayerController::LoadSaveGame()
{
	UMetaSaveGame* MetaSG = Cast<UMetaSaveGame>(UGameplayStatics::LoadGameFromSlot("Meta", 0));
	if (!MetaSG)
	{
		return false;
	}

	UAmbosiaSaveGame* SaveGame = Cast<UAmbosiaSaveGame>(UGameplayStatics::LoadGameFromSlot(MetaSG->GetCurrentUserName(), MetaSG->CurrentUserIndex));
	bool SaveSuccessfull = true;
	if (SaveGame)
	{
		if (!LoadItems(SaveGame))
			SaveSuccessfull = false;
		if (!LoadGameplayValues(SaveGame))
			SaveSuccessfull = false;
		if (!LoadPosition(SaveGame))
			SaveSuccessfull = false;
	}
	else
		SaveSuccessfull = false;
	return SaveSuccessfull;
}

bool AAmbosiaPlayerController::LoadGameplayValues(UAmbosiaSaveGame* Savegame)
{
	GameplaySystem->SetHealthPointsLimit(Savegame->HealthPointsLimit);
	GameplaySystem->SetHealthPoints(Savegame->HealthPoints);
	GameplaySystem->SetManaLimit(Savegame->ManaLimit);
	GameplaySystem->SetMana(Savegame->Mana);
	GameplaySystem->SetManaRegenerationPerSec(Savegame->ManaRegeneration);
	GameplaySystem->SetAttackPoints(Savegame->AttackPoints);
	this->ExperiencePoints = Savegame->ExperiencePoints;
	this->CurrentLevel = Savegame->SkillLevel;
	this->SkillPoints = Savegame->SkillPoints;
	return true;
}

bool AAmbosiaPlayerController::LoadItems(UAmbosiaSaveGame* Savegame)
{
	for (int x = 0; x < Savegame->Items.Num(); x++)
	{
		UItemComponent* NewItem = GameplaySystem->CreateAndAddItem(Savegame->Items[x]);
		if (NewItem)
		{
			NewItem->SetStackSize(Savegame->ItemStacks[x]);

			if (x == Savegame->WeaponIndex)
			{
				UWeaponComponent* NewWeapon = Cast<UWeaponComponent>(NewItem);
				if (NewWeapon)
				{
					GameplaySystem->SetWeapon(NewWeapon);
				}
			}

			if (x == Savegame->ArmorIndex)
			{
				UArmorComponent* NewArmor = Cast<UArmorComponent>(NewItem);
				if (NewArmor)
				{
					GameplaySystem->SetArmor(NewArmor);
				}
			}

			if (x == Savegame->PotionIndex)
			{
				UPotionComponent* NewPotion = Cast<UPotionComponent>(NewItem);
				if (NewPotion)
				{
					GameplaySystem->SetPotion(NewPotion);
				}
			}

			if (x == Savegame->ArrowBundleIndex)
			{
				UArrowBundleComponent* NewArrowBundle = Cast<UArrowBundleComponent>(NewItem);
				if (NewArrowBundle)
				{
					GameplaySystem->SetArrowBundle(NewArrowBundle);
				}
			}

			if (x == Savegame->FirstRingIndex)
			{
				URingComponent* NewFirstRing = Cast<URingComponent>(NewItem);
				if (NewFirstRing)
				{
					GameplaySystem->SetFirstRing(NewFirstRing);
				}
			}

			if (x == Savegame->SecondRingIndex)
			{
				URingComponent* NewSecondRing = Cast<URingComponent>(NewItem);
				if (NewSecondRing)
				{
					GameplaySystem->SetSecondRing(NewSecondRing);
				}
			}

			if (x == Savegame->AmuletIndex)
			{
				UAmuletComponent* NewAmulet = Cast<UAmuletComponent>(NewItem);
				if (NewAmulet)
				{
					GameplaySystem->SetAmulet(NewAmulet);
				}
			}
		}
		else
			return false;
	}
	return true;
}

bool AAmbosiaPlayerController::LoadPosition(UAmbosiaSaveGame* Savegame)
{
	this->GetPawn()->SetActorTransform(Savegame->Spawnpoint, false, nullptr, ETeleportType::TeleportPhysics);
	this->CurrentWorldPath = Savegame->LevelName;
	return true;
}

float AAmbosiaPlayerController::GetLookRate()
{
	return this->LookRate;
}

UGameplaySystemComponent* AAmbosiaPlayerController::GetGameplaySystem()
{
	return this->GameplaySystem;
}

float AAmbosiaPlayerController::GetExperiencePoints()
{
	return this->ExperiencePoints;
}

float AAmbosiaPlayerController::GetSkillPoints()
{
	return this->SkillPoints;
}

int32 AAmbosiaPlayerController::GetCurrentLevel()
{
	return this->CurrentLevel;
}