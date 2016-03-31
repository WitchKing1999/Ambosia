// (C) Flumminard 2015-2016

#include "Ambosia.h"

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
	XPLevels.Add(10);
	XPLevels.Add(15);

	SkillPointsList = TArray<float>();
	SkillPointsList.Add(0);
	SkillPointsList.Add(5);
	SkillPointsList.Add(10);
	SkillPointsList.Add(20);

}

void AAmbosiaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UAmbosiaSaveGame* SaveGame = Cast<UAmbosiaSaveGame>(UGameplayStatics::LoadGameFromSlot("Ambosia", 0));
	if (SaveGame)
	{
		LoadItems(SaveGame);
		LoadGameplayValues(SaveGame);
		LoadPosition(SaveGame);
	}
	
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
	UKismetSystemLibrary::QuitGame(this, this, EQuitPreference::Quit);
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

void AAmbosiaPlayerController::LoadGameplayValues(UAmbosiaSaveGame* Savegame)
{
	GameplaySystem->SetHealthPointsLimit(Savegame->HealthPointsLimit);
	GameplaySystem->SetHealthPoints(Savegame->HealthPoints);
	GameplaySystem->SetManaLimit(Savegame->ManaLimit);
	GameplaySystem->SetMana(Savegame->Mana);
	GameplaySystem->SetManaRegenerationPerSec(Savegame->ManaRegeneration);
	GameplaySystem->SetAttackPoints(Savegame->AttackPoints);
}

void AAmbosiaPlayerController::LoadItems(UAmbosiaSaveGame* Savegame)
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

	}
}

void AAmbosiaPlayerController::LoadPosition(UAmbosiaSaveGame* Savegame)
{
	if (Savegame)
	{
		this->GetPawn()->SetActorTransform(Savegame->Spawnpoint, true, nullptr, ETeleportType::TeleportPhysics);
	}
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