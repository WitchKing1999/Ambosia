// (C) Flumminard 2015-2016

#pragma once

#include "GameFramework/PlayerController.h"

#include "AmbosiaSaveGame.h"
#include "GameplaySystemComponent.h"

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

	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void LookRight(float AxisValue);

	void AttackPressed();

	void PotionPressed();

	void MainMenuPressed();

	void InventoryPressed();

	UFUNCTION(BlueprintCallable, Category = "Experience")
	void ReceiveLoot(TArray<UClass*> ItemClasses, TArray<int32> ItemStacks, float Experience);

	UFUNCTION(BlueprintCallable, Category = "Experience")
	void SpendSkillPoints(float Amount, ESkillableValue Value);

	UFUNCTION(BlueprintCallable, Category = "SavefileLoading")
	void LoadGameplayValues(UAmbosiaSaveGame* Savegame);

	UFUNCTION(BlueprintCallable, Category = "SavefileLoading")
	void LoadItems(UAmbosiaSaveGame* Savegame);

	UFUNCTION(BlueprintCallable, Category = "SavefileLoading")
	void LoadPosition(UAmbosiaSaveGame* Savegame);

	float GetLookRate();

	UGameplaySystemComponent* GetGameplaySystem();

	float GetExperiencePoints();

	float GetSkillPoints();

	int32 GetCurrentLevel();
	
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

};
