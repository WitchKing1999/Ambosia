// (C) Flumminard 2015

#pragma once

#include "Items/ItemComponent.h"
#include "DamageTypes/AmbosiaDamageType.h"
#include "WeaponComponent.generated.h"

/*
Base class for weapons.
*/
UCLASS(ClassGroup = (Items), meta = (BlueprintSpawnableComponent))
class AMBOSIA_API UWeaponComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:
	UWeaponComponent();

	/*
	Plots a trace line in front of the instigator's pawn with the length of LineLength.
	If it hits something, it will apply damage of the given damage type and returns the hit actor
	or nullptr if it hits nothing. Requires the GameplaySystem which we are attached to.
	Can be used both for swords and guns.
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon Actions")
	AActor* PlotHitLine(float LineLength, AController* Instigator, TSubclassOf<UDamageType> DamageType, UGameplaySystemComponent* GameplaySystem);

	/*
	Spawns an actor of ActorClass at the RelativeSpawnLocation.
	Requires the actor which launches the projectile (not the controller!)
	and the GameplaySystem which we are attached to.
	Returns the spawned projectile or nullptr if it failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon Actions")
	AActor* SpawnProjectile(UClass* ActorClass, FVector RelativeSpawnLocation, AActor* LaunchingActor, UGameplaySystemComponent* GameplaySystem);

	/*
	Returns whether the given GameplaySystem has enough mana to satisfy our mana costs.
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon Costs")
	bool AreManaCostsSatisfied(UGameplaySystemComponent* GameplaySystem);

	/*
	Reduces the mana of the given GameplaySystem by our mana costs.
	Returns true, if it was successfull and false if not.
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon Costs")
	bool ApplyManaCosts(UGameplaySystemComponent* GameplaySytem);

	/*
	Returns whether the given GameplaySystem has the right and enough arrows
	to satisfy or arrowbundle cost.
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon Costs")
	bool AreArrowBundleCostsSatisfied(UGameplaySystemComponent* GameplaySytem);

	/*
	Reduces the arrow bundle stack of the given GameplaySystem by our arrow bundle costs.
	Returns true if it was successfull and false if not.
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon Costs")
	bool ApplyArrowBundleCosts(UGameplaySystemComponent* GameplaySystem);

	/*
	Multiplies the attack points by our attack factor and returns them.
	If we have a critical hit, it also multiplies the attack points by 2.
	*/
	virtual float ModifyAttackPoints_Implementation(float AttackPoints) override;

	/*
	Multiplies the magical attack points by our magical attack factor.
	*/
	virtual float ModifyMagicalAttackPoints_Implementation(float MagicalAttackPoints) override;

	/*
	Returns our mana costs
	*/
	float GetManaCost();

	/*
	Returns or attack factor.
	*/
	float GetAttackFactor();

	/*
	Returns our magical attack factor
	*/
	float GetMagicalAttackFactor();

	/*
	Returns our chance for a critical hit.
	*/
	float GetCriticalDamageChance();

	int32 GetArrowBundleCosts();

	/*
	Returns an array of all accepted arrow bundle classes
	*/
	TArray<UClass*> GetAcceptedArrowBundles();
	
protected:

	/*
	Our attack factor
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float AttackFactor;

	/*
	Our mana costs
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float ManaCost;

	/*
	Our magical attack factor
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float MagicalAttackFactor;

	/*
	Our chance for a critical hit.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float CriticalDamageChance;

	/*
	Our arrow bundle costs
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	int32 ArrowBundleCosts;

	/*
	All accepted arrow bundle classes
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TArray<UClass*> AcceptedArrowBundles;
};
