// (C) Flumminard 2015-2016

#include "Ambosia.h"

#include "Saving/MetaSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "BaseAmbosiaHUD.h"

#include "AmbosiaPlayerController.h"

UInteractableInterface::UInteractableInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

AAmbosiaPlayerController::AAmbosiaPlayerController()
{
	InteractableControllers = TArray<AController*>();

	GameplaySystem = CreateDefaultSubobject<UGameplaySystemComponent>(TEXT("GameplaySystemComponent"));
	GameplaySystem->bLoadGameOverScreenOnDying = true;

	OnGameSaved = FGameSavedDelegate();
	OnGameLoaded = FGameLoadedDelegate();

	LookRate = 2;
	SaveGameLoaded = false;
	ControlsEnabled = true;

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

	Quests = TArray<FQuest>();
	OnQuestAdded = FQuestAddedDelegate();
	OnQuestRemoved = FQuestRemovedDelegate();
	OnQuestStatusChanged = FQuestStatusChangedDelegate();
}

void AAmbosiaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SaveGameLoaded = this->LoadSaveGame();
	
	InputComponent->BindAxis("MoveForward", this, &AAmbosiaPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AAmbosiaPlayerController::MoveRight);
	InputComponent->BindAxis("LookRight", this, &AAmbosiaPlayerController::LookRight);
	
	InputComponent->BindAction("Attack", IE_Pressed, this, &AAmbosiaPlayerController::AttackPressed);
	InputComponent->BindAction("Potion", IE_Pressed, this, &AAmbosiaPlayerController::PotionPressed);
	InputComponent->BindAction("MainMenu", IE_Pressed, this, &AAmbosiaPlayerController::MainMenuPressed);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &AAmbosiaPlayerController::InventoryPressed);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AAmbosiaPlayerController::InteractionPressed);
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
	if (this->ControlsEnabled)
		this->GetPawn()->AddMovementInput(this->GetControlRotation().Vector(), AxisValue);
}

void AAmbosiaPlayerController::MoveRight(float AxisValue)
{
	if (this->ControlsEnabled)
	{
		FVector WorldDirection = this->GetControlRotation().Vector();
		WorldDirection = FRotator(0, 90, 0).RotateVector(WorldDirection);
		this->GetPawn()->AddMovementInput(WorldDirection, AxisValue);
	}
}

void AAmbosiaPlayerController::LookRight(float AxisValue)
{
	if (this->ControlsEnabled)
	{
		this->AddYawInput(AxisValue * LookRate);
	}
}

void AAmbosiaPlayerController::AttackPressed()
{
	if (this->ControlsEnabled && GameplaySystem->GetWeapon())
	{
		GameplaySystem->GetWeapon()->Action();
	}
}

void AAmbosiaPlayerController::PotionPressed()
{
	if (this->ControlsEnabled && GameplaySystem->GetPotion())
	{
		GameplaySystem->GetPotion()->Action();
	}
}

void AAmbosiaPlayerController::MainMenuPressed()
{
	ABaseAmbosiaHUD* HUD = Cast<ABaseAmbosiaHUD>(this->GetHUD());
	if (HUD)
	{
		HUD->OpenReturnToMainMenuWidget();
	}
}

void AAmbosiaPlayerController::InventoryPressed()
{
	ABaseAmbosiaHUD* HUD = Cast<ABaseAmbosiaHUD>(this->GetHUD());
	if (HUD->bInventoryOpen)
	{
		HUD->CloseInventory();
	}
	else
	{
		HUD->OpenInventory();
	}
}

#include "Kismet/KismetSystemLibrary.h"

void AAmbosiaPlayerController::InteractionPressed()
{
	if (this->InteractableControllers.Num() > 0)
	{
		IInteractableInterface::Execute_Interact(this->InteractableControllers.Last());
	}
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
		UItemComponent* Item = Cast<UItemComponent>(this->GetComponentByClass(TSubclassOf<UActorComponent>(ItemClasses[x])));
		if (Item && Item->GetAttachParent() == GameplaySystem && Item->IsStackable())
		{
			Item->SetStackSize(Item->GetStackSize() + ItemStacks[x]);
		}
		else
		{
			GameplaySystem->CreateAndAddItem(ItemClasses[x])->SetStackSize(ItemStacks[x]);
		}
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
		this->OnGameSaved.Broadcast(true);
		return true;
	}
	else
	{
		this->OnGameSaved.Broadcast(false);
		return false;
	}
}

bool AAmbosiaPlayerController::SaveGameplayValues(UAmbosiaSaveGame* Savegame)
{
	Savegame->HealthPoints = GameplaySystem->GetHealthPoints();
	Savegame->HealthPointsLimit = GameplaySystem->GetHealthPointsLimit();
	Savegame->Mana = GameplaySystem->GetMana();
	Savegame->ManaLimit = GameplaySystem->GetManaLimit();
	Savegame->ManaRegeneration = GameplaySystem->GetManaRegenerationPerSec();
	Savegame->AttackPoints = GameplaySystem->GetAttackPoints();
	Savegame->MagicalAttackPoints = GameplaySystem->GetMagicalAttackPoints();
	Savegame->ExperiencePoints = ExperiencePoints;
	Savegame->SkillPoints = SkillPoints;
	Savegame->SkillLevel = CurrentLevel;
	Savegame->Quests = Quests;
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

	this->OnGameLoaded.Broadcast(SaveSuccessfull);
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
	this->Quests = Savegame->Quests;
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
	this->SetControlRotation(FRotator(Savegame->Spawnpoint.GetRotation()));
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

bool AAmbosiaPlayerController::GetSaveGameLoaded()
{
	return this->SaveGameLoaded;
}

TArray<FQuest> AAmbosiaPlayerController::GetQuests()
{
	return this->Quests;
}

bool AAmbosiaPlayerController::GetQuest(FName QuestName, FQuest& Quest)
{
	for (int32 Index = 0; Index < this->GetQuests().Num(); Index++)
	{
		if (this->GetQuests()[Index].QuestName == QuestName)
		{
			Quest = this->GetQuests()[Index];
			return true;
		}
		Index++;
	}
	return false;
}

void AAmbosiaPlayerController::AddQuest(FQuest NewQuest)
{
	this->Quests.Add(NewQuest);
	this->OnQuestAdded.Broadcast(NewQuest);
}

void AAmbosiaPlayerController::RemoveQuest(FName QuestName)
{
	for (int32 Index = 0; Index < this->GetQuests().Num(); Index++)
	{
		if (this->GetQuests()[Index].QuestName == QuestName)
		{
			this->OnQuestRemoved.Broadcast(this->GetQuests()[Index]);
			this->Quests.RemoveAt(Index);
			break;
		}
		Index++;
	}
}

void AAmbosiaPlayerController::SetQuestStatus(FName QuestName, EQuestStatus NewStatus)
{
	for (int32 Index = 0; Index < this->GetQuests().Num(); Index++)
	{
		if (this->GetQuests()[Index].QuestName == QuestName)
		{
			FQuest OldQuest = this->Quests[Index];
			this->Quests[Index].Status = NewStatus;
			this->OnQuestStatusChanged.Broadcast(OldQuest, this->GetQuests()[Index]);
		}
		Index++;
	}
}