// (C) Flumminard 2015-2016

#pragma once

#include "GameFramework/PlayerController.h"

#include "Saving/AmbosiaSaveGame.h"
#include "GameplaySystemComponent.h"
#include "BaseAmbosiaHUD.h"

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

	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool LoadSaveGame();

	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool LoadGameplayValues(UAmbosiaSaveGame* Savegame);

	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool LoadItems(UAmbosiaSaveGame* Savegame);

	UFUNCTION(BlueprintCallable, Category = "Saveing")
	bool LoadPosition(UAmbosiaSaveGame* Savegame);

	float GetLookRate();

	UGameplaySystemComponent* GetGameplaySystem();

	float GetExperiencePoints();

	float GetSkillPoints();

	int32 GetCurrentLevel();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CurrentWorldPath;

	bool GetSaveGameLoaded();
	
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

};
