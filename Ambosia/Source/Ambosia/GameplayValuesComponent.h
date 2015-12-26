// (C) Flumminard 2015

#pragma once

#include "Components/ActorComponent.h"
#include "GameplayValuesComponent.generated.h"

/*
This component holds all gameplay values of a NPC or the Player.
You just need to add this to your controller and it will be used!
Every gameplay value has three realted functions: GetX, SetX and AffectX.
GetX returns the value, SetX sets it and AffectX in- or decreases it.
HealthPoints and Mana can't be bigger than their Limit, which is controlled
in SetX; AffectX uses SetX, so it sticks to that rule too.
For more information see the gameplay document.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AMBOSIA_API UGameplayValuesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameplayValuesComponent();

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	float TimeToNextRegen;

public:

	/*
	Health Points
	*/

	float GetHealthPoints();

	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Health Points")
	void SetHealthPoints(float NewHealthPoints);

	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Health Points")
	void AffectHealthPoints(float Delta);

	float GetHealthPointsLimit();

	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Health Points")
	void SetHealthPointsLimit(float NewHealthPointsLimit);

	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Health Points")
	void AffectHealthPointsLimit(float Delta);

	/*
	Attack Points
	*/

	float GetAttackPoints();

	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Attack Points")
	void SetAttackPoints(float NewAttackPoints);

	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Attack Points")
	void AffectAttackPoints(float Delta);

	float GetMagicalAttackPoints();

	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Attack Points")
	void SetMagicalAttackPoints(float NewMagicalAttackPoints);

	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Attack Points")
	void AffectMagicalAttackPoints(float Delta);

	/*
	Mana
	*/

	float GetMana();

	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Mana")
	void SetMana(float NewMana);

	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Mana")
	void AffectMana(float Delta);

	float GetManaLimit();

	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Mana")
	void SetManaLimit(float NewManaLimit);

	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Mana")
	void AffectManaLimit(float Delta);

	float GetManaRegenerationPerSec();

	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Mana")
	void SetManaRegenerationPerSec(float NewManaReg);

	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Mana")
	void AffectManaRegeneration(float Delta);

protected:

	/*
	Variables
	See gameplay document for more information.
	*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Values|Health Points")
	float HealthPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Values|Health Points")
	float HealthPointsLimit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Values|Attack Points")
	float AttackPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Values|Attack Points")
	float MagicalAttackPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Values|Mana")
	float Mana;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Values|Mana")
	float ManaLimit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Values|Mana")
	float ManaRegenerationPerSec;
	
};
