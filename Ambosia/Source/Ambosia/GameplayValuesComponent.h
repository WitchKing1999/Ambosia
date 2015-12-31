// (C) Flumminard 2015

#pragma once

#include "Components/ActorComponent.h"
#include "GameplayValuesComponent.generated.h"

/*
This component holds all gameplay values of a NPC or the Player.
Every gameplay value has three related functions: GetX, SetX and AffectX.
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

	/**
	This value gets reduced by every tick and if it is zero,
	the mana regeneration value will be added to our mana
	and the time to the next regeneration will be reset to 1.
	*/
	float TimeToNextRegen;

public:

	/*
	=================================================================
	Health Points
	=================================================================
	*/

	/*
	Returns our health points
	*/
	float GetHealthPoints();

	/*
	Sets our health points to the new health points.
	If the new health points are bigger than the health points limit,
	our health points will be set to the limit.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Health Points")
	void SetHealthPoints(float NewHealthPoints);

	/*
	Adds the delta value to our health points.
	Since we use "SetHealthPoints", the new health points can't be bigger
	than the health points limit. Also, if the delta is negative,
	we will ask our armor to reduce our delta.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Health Points")
	void AffectHealthPoints(float Delta);

	/*
	Returns our health points limit
	*/
	float GetHealthPointsLimit();

	/*
	Sets our health points limit. If our health points are bigger than
	the new limit, the health points will be also set to it.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Health Points")
	void SetHealthPointsLimit(float NewHealthPointsLimit);

	/*
	Adds the delta value to our health points limit.
	Since we use "SetHealthPointsLimit", our health points won't be bigger
	than our new limit.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Health Points")
	void AffectHealthPointsLimit(float Delta);

	/*
	=================================================================
	Attack Points
	=================================================================
	*/

	/*
	Returns our attack points
	*/
	float GetAttackPoints();

	/*
	Sets our attack points to the new attack points.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Attack Points")
	void SetAttackPoints(float NewAttackPoints);

	/*
	Adds the delta value to our attack points.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Attack Points")
	void AffectAttackPoints(float Delta);

	/*
	Returns our magical attack points
	*/
	float GetMagicalAttackPoints();

	/*
	Sets our magical attack points to the new magical attack points.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Attack Points")
	void SetMagicalAttackPoints(float NewMagicalAttackPoints);

	/*
	Adds the delta value to our magical attack points.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Attack Points")
	void AffectMagicalAttackPoints(float Delta);

	/*
	=================================================================
	Mana
	=================================================================
	*/

	/*
	Returns our mana points
	*/
	float GetMana();

	/*
	Sets our mana to the new mana.
	If the new mana is bigger than the mana limit,
	our mana will be set to the limit.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Mana")
	void SetMana(float NewMana);

	/*
	Adds the delta value to our mana.
	Since we use "SetMana", the new mana can't be bigger
	than the mana limit. Also, if delta is negative,
	we will ask our armor to reduce our delta.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Mana")
	void AffectMana(float Delta);

	/*
	Returns our mana limit
	*/
	float GetManaLimit();

	/*
	Sets our mana limit. If our mana is bigger than
	the new limit, the mana will be also set to it.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Mana")
	void SetManaLimit(float NewManaLimit);

	/*
	Adds the delta value to our mana limit.
	Since we use "SetManaLimit", our mana won't be bigger
	than our new limit.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Mana")
	void AffectManaLimit(float Delta);

	/*
	Returs our mana regeneration.
	*/
	float GetManaRegenerationPerSec();

	/*
	Sets our mana regeneration
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Mana")
	void SetManaRegenerationPerSec(float NewManaReg);

	/*
	Adds the delta to our mana regeneration
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Gameplay Values|Mana")
	void AffectManaRegeneration(float Delta);

protected:

	/*
	Our properties
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
