// (C) Flumminard 2015-2016

#pragma once

#include "GameFramework/PlayerController.h"

#include "Saving/AmbosiaSaveGame.h"
#include "GameplaySystemComponent.h"
#include "BaseAmbosiaHUD.h"
#include "Structs/Quest.h"

#include "AmbosiaPlayerController.generated.h"

/*
An enum for every skillable gameplay value.
This is a part of the experience system.
*/
UENUM(BlueprintType)
enum class ESkillableValue : uint8
{
	VE_HealthPointsLimit UMETA(DisplayName="HealthPointsLimit"),
	VE_ManaLimit UMETA(DisplayName="ManaLimt"),
	VE_ManaRegeneration UMETA(DisplayName="ManaRegenerationPerSecond"),
	VE_AttackPoints UMETA(DisplayName="AttackPoints"),
	VE_MagicalAttackPoints UMETA(DisplayName="MagicalAttackPoints")
};

/*
An interface for interactable controllers.
*/
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

/*
Event Dispatchers
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameLoadedDelegate, bool, Successfull);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameSavedDelegate, bool, Successfull);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestAddedDelegate, FQuest, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestRemovedDelegate, FQuest, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FQuestStatusChangedDelegate, FQuest, OldQuest, FQuest, NewQuest);

/*
The player controller for Ambosia.
Adds a gameplay system, controlls, the skill and the quest system to the core
player controller functionalities.
*/
UCLASS()
class AMBOSIA_API AAmbosiaPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAmbosiaPlayerController();

	/*
	Called when we start playing
	*/
	virtual void BeginPlay() override;

	/*
	Called when we stop playing
	*/
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/*
	Applies damage to our gameplay system.
	*/
	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/*
	Input handler for moving forward/backward
	*/
	UFUNCTION(BlueprintCallable, Category = "Events")
	void MoveForward(float AxisValue);

	/*
	Input handler for moving right/left
	*/
	UFUNCTION(BlueprintCallable, Category = "Events")
	void MoveRight(float AxisValue);

	/*
	Input handler for turning right/left
	*/
	UFUNCTION(BlueprintCallable, Category = "Events")
	void LookRight(float AxisValue);

	/*
	Input handler, uses our weapon
	*/
	UFUNCTION(BlueprintCallable, Category = "Events")
	void AttackPressed();

	/*
	Input handler, uses our potion
	*/
	UFUNCTION(BlueprintCallable, Category = "Events")
	void PotionPressed();

	/*
	Input handler, shows the dialogue
	*/
	UFUNCTION(BlueprintCallable, Category = "Events")
	void MainMenuPressed();

	/*
	Input handler, shows our inventory hud
	*/
	UFUNCTION(BlueprintCallable, Category = "Events")
	void InventoryPressed();

	/*
	Input handler, tries to interact with something around us.
	*/
	UFUNCTION(BlueprintCallable, Category = "Events")
	void InteractionPressed();

	/*
	Adds the given items to our gameplay system, sets their stacks to the given stacks
	and adds the given experience points to ours.
	*/
	UFUNCTION(BlueprintCallable, Category = "Experience")
	void ReceiveLoot(TArray<UClass*> ItemClasses, TArray<int32> ItemStacks, float Experience);

	/*
	If possible, it reduces our skill points by the given amount and adds the same amount
	to the given skillable value.
	*/
	UFUNCTION(BlueprintCallable, Category = "Experience")
	void SpendSkillPoints(float Amount, ESkillableValue Value);

	/*
	Saves the current position and state.
	Returns true if saving was successfull.
	*/
	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool SaveSaveGame();

	/*
	Sets the savegame values to our values.
	Used in the saving process, but does not write the savegame.
	Returns true if data copying was successfull.
	*/
	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool SaveGameplayValues(UAmbosiaSaveGame* Savegame);

	/*
	Sets the savegame items to our items.
	Used in the saving process, but does not write the savegame.
	Returns true if data copying was successfull.
	*/
	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool SaveItems(UAmbosiaSaveGame* Savegame);

	/*
	Sets the savegame position and level name to ours.
	Used in the saving process, but does not write the savegame.
	Returns true if data copying was successfull.
	*/
	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool SavePosition(UAmbosiaSaveGame* Savegame);

	/*
	Gets called when the game was saved.
	*/
	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FGameSavedDelegate OnGameSaved;

	/*
	Loads the saved game and returns true if loading was successfull.
	*/
	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool LoadSaveGame();

	/*
	Sets our gameplay values to those in the savegame.
	Return true if loading was successfull.
	*/
	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool LoadGameplayValues(UAmbosiaSaveGame* Savegame);

	/*
	Sets our items to those in the savegame.
	Return true if loading was successfull.
	*/
	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool LoadItems(UAmbosiaSaveGame* Savegame);

	/*
	Sets our position to the one in the savegame.
	Return true if loading was successfull.
	*/
	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool LoadPosition(UAmbosiaSaveGame* Savegame);

	/*
	Gets called when the game was loaded.
	*/
	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FGameLoadedDelegate OnGameLoaded;

	float GetLookRate();

	UGameplaySystemComponent* GetGameplaySystem();

	float GetExperiencePoints();

	float GetSkillPoints();

	int32 GetCurrentLevel();

	/*
	The path to our current level.
	Primarily used in saving and loading.
	*/
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

	/*
	Gets called when a quest was added.
	*/
	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FQuestAddedDelegate OnQuestAdded;

	/*
	Removes the quest at the given index. Should be used barely.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Experience")
	void RemoveQuest(FName QuestName);

	/*
	Gets called when a quest was removed.
	*/
	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FQuestRemovedDelegate OnQuestRemoved;

	/*
	Sets the status of a quest to the new status.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Experience")
	void SetQuestStatus(FName QuestName, EQuestStatus NewStatus);

	/*
	Gets called when a quest status has changed.
	*/
	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FQuestStatusChangedDelegate OnQuestStatusChanged;

public:

	/*
	An array of all controllers we can interact with.
	*/
	UPROPERTY(BlueprintReadWrite)
	TArray<AController*> InteractableControllers;

	/*
	If true, the player controls over the character are enabled.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool ControlsEnabled;
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float LookRate;

	/*
	Our gameplay system.
	It manages our items and our damage.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UGameplaySystemComponent* GameplaySystem;

	/*
	Our current experience points.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Experience")
	float ExperiencePoints;

	/*
	An array that holds the required experience points to reach a level.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Experience")
	TArray<float> XPLevels;

	/*
	An array that holds the skill points we earn when we reach a level.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Experience")
	TArray<float> SkillPointsList;

	/*
	Our available skill points.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Experience")
	float SkillPoints;

	/*
	Our current experience/skill level.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Experience")
	int32 CurrentLevel;

	/*
	If true, we have loaded the last save game.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool SaveGameLoaded;

	/*
	An array with all of our quests.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Experience")
	TArray<FQuest> Quests;

};
