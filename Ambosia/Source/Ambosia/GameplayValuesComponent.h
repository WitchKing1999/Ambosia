// (C) Flumminard 2015

#pragma once

#include "Components/ActorComponent.h"
#include "GameplayValuesComponent.generated.h"

// This component holds all gameplay values of a NPC or the Player.
// You just need to add this to your controller and it will be used!
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AMBOSIA_API UGameplayValuesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameplayValuesComponent();

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AffectHealthPoints(float Delta);

private:

	float TimeToNextRegen;

public:

	float GetHealthPoints();

	void SetHealthPoints(float NewHealthPoints);

	float GetHealthPointsLimit();

	void SetHealthPointsLimit(float NewHealthPointsLimit);

	float GetAttackPoints();

	void SetAttackPoints(float NewAttackPoints);

	float GetMana();

	void SetMana(float NewMana);

	float GetManaLimit();

	void SetManaLimit(float NewManaLimit);

	float GetMagicalAttackPoints();

	void SetMagicalAttackPoints(float NewMagicalAttackPoints);

	float GetManaRegenerationPerSec();

	void SetManaRegenerationPerSec(float NewManaReg);

protected:
	float HealthPoints;

	float HealthPointsLimit;

	float AttackPoints;

	float Mana;

	float ManaLimit;

	float MagicalAttackPoints;

	float ManaRegenerationPerSec;
	
};
