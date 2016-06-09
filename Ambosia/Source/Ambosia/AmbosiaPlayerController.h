// (C) Flumminard 2015-2016

#pragma once

#include "GameFramework/PlayerController.h"

#include "Saving/AmbosiaSaveGame.h"
#include "GameplaySystemComponent.h"
#include "BaseAmbosiaHUD.h"
#include "Structs/Quest.h"

#include "AmbosiaPlayerController.generated.h"

UENUM(BlueprintType)
enum class ESkillableValue : uint8
{
	VE_HealthPointsLimit UMETA(DisplayName="HealthPointsLimit"),
	VE_ManaLimit UMETA(DisplayName="ManaLimt"),
	VE_ManaRegeneration UMETA(DisplayName="ManaRegenerationPerSecond"),
	VE_AttackPoints UMETA(DisplayName="AttackPoints"),
	VE_MagicalAttackPoints UMETA(DisplayName="MagicalAttackPoints")
};

UINTERFACE(Blueprintable)
class UInteractableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IInteractableInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Custom")
		void Interact() const;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameLoadedDelegate, bool, Successfull);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameSavedDelegate, bool, Successfull);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestAddedDelegate, FQuest, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestRemovedDelegate, FQuest, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FQuestStatusChangedDelegate, FQuest, OldQuest, FQuest, NewQuest);

/**
 * 
 */
UCLASS()
class AMBOSIA_API AAmbosiaPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAmbosiaPlayerController();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = "Events")
	void MoveForward(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Events")
	void MoveRight(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Events")
	void LookRight(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Events")
	void AttackPressed();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void PotionPressed();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void MainMenuPressed();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void InventoryPressed();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void InteractionPressed();

	UFUNCTION(BlueprintCallable, Category = "Experience")
	void ReceiveLoot(TArray<UClass*> ItemClasses, TArray<int32> ItemStacks, float Experience);

	UFUNCTION(BlueprintCallable, Category = "Experience")
	void SpendSkillPoints(float Amount, ESkillableValue Value);

	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool SaveSaveGame();

	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool SaveGameplayValues(UAmbosiaSaveGame* Savegame);

	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool SaveItems(UAmbosiaSaveGame* Savegame);

	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool SavePosition(UAmbosiaSaveGame* Savegame);

	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FGameSavedDelegate OnGameSaved;

	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool LoadSaveGame();

	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool LoadGameplayValues(UAmbosiaSaveGame* Savegame);

	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool LoadItems(UAmbosiaSaveGame* Savegame);

	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool LoadPosition(UAmbosiaSaveGame* Savegame);

	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FGameLoadedDelegate OnGameLoaded;

	float GetLookRate();

	UGameplaySystemComponent* GetGameplaySystem();

	float GetExperiencePoints();

	float GetSkillPoints();

	int32 GetCurrentLevel();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CurrentWorldPath;

	bool GetSaveGameLoaded();

	/*
	Returns our quests. See variable description for more information.
	*/
	TArray<FQuest> GetQuests();

	/*
	Gets the quest with this name. Returns true if this Quest was found, false if not.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Variables|Experience")
	bool GetQuest(FName QuestName, FQuest& Quest);

	/*
	Adds a new quest.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Experience")
	void AddQuest(FQuest NewQuest);

	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FQuestAddedDelegate OnQuestAdded;

	/*
	Removes the quest at the given index. Should be used barely.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Experience")
	void RemoveQuest(FName QuestName);

	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FQuestRemovedDelegate OnQuestRemoved;

	/*
	Sets the status of a quest to the new status.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Experience")
	void SetQuestStatus(FName QuestName, EQuestStatus NewStatus);

	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FQuestStatusChangedDelegate OnQuestStatusChanged;

public:

	UPROPERTY(BlueprintReadWrite)
	TArray<AController*> InteractableControllers;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LookRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UGameplaySystemComponent* GameplaySystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Experience")
	float ExperiencePoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Experience")
	TArray<float> XPLevels;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Experience")
	TArray<float> SkillPointsList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Experience")
	float SkillPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Experience")
	int32 CurrentLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool SaveGameLoaded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool ControlsEnabled;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Experience")
	TArray<FQuest> Quests;

};
