// (C) Flumminard 2015-2016

#pragma once

#include "Components/SceneComponent.h"
#include "Items/WeaponComponent.h"
#include "Items/ArmorComponent.h"
#include "Items/PotionComponent.h"
#include "Items/ArrowBundleComponent.h"
#include "Items/RingComponent.h"
#include "GameplaySystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AMBOSIA_API UGameplaySystemComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameplaySystemComponent();

	/*
	Creates an Item from the given class and attaches it to us.
	Returns the created Item or NULL, if the creation failed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Component|AddComponent")
	UItemComponent* CreateAndAddItem(UClass* ItemClass);

	UFUNCTION(BlueprintCallable, Category = "Game|Damage")
	virtual float TakeDamage(float DamageAmount, UDamageType* DamageType, AController* EventInstigator, AActor* DamageCauser);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnChildDetached(USceneComponent* ChildComponent) override;

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
	Returns our raw health points limit
	*/
	float GetRawHealthPointsLimit();

	/*
	Returns our health points limit, modified by our items
	*/
	UFUNCTION(BlueprintPure, Category = "Variables|Gameplay Values|Health Points")
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
	Returns our raw attack points
	*/
	float GetRawAttackPoints();

	/*
	Returns our attack points, modified by our items
	*/
	UFUNCTION(BlueprintPure, Category = "Variables|Gameplay Values|Attack Points")
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
	Returns our raw magical attack points
	*/
	float GetRawMagicalAttackPoints();

	/*
	Returns our magical attack points, modified by our items
	*/
	UFUNCTION(BlueprintPure, Category = "Variables|Gameplay Values|Attack Points")
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
	Returns our raw mana limt
	*/
	float GetRawManaLimit();

	/*
	Returns our mana limit, modified by our items
	*/
	UFUNCTION(BlueprintPure, Category = "Variables|Gameplay Values|Mana")
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
	Returns our raw mana regeneration
	*/
	float GetRawManaRegenerationPerSec();

	/*
	Returns our mana regeneration, modified by our items
	*/
	UFUNCTION(BlueprintPure, Category = "Variables|Gameplay Values|Mana")
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

	/*
	=================================================================
	Weapon
	=================================================================
	*/

	/*
	Returns our weapon
	*/
	UWeaponComponent* GetWeapon();

	/**
	Sets our weapon to the new weapon.
	Doesn't work if the new weapon ism't attached to us.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	bool SetWeapon(UWeaponComponent* NewWeapon);

	/*
	=================================================================
	Armor
	=================================================================
	*/

	/*
	Returns our armor
	*/
	UArmorComponent* GetArmor();

	/**
	Sets our armor to the new armor.
	Doesn't work if the new armor isn't attached to us.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	bool SetArmor(UArmorComponent* NewArmor);

	/*
	=================================================================
	Potion
	=================================================================
	*/

	/*
	Returns our potion
	*/
	UPotionComponent* GetPotion();

	/**
	Sets our potion to the new potion.
	Doesn't work if the new potion ism't attached to us.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	bool SetPotion(UPotionComponent* NewPotion);

	/*
	=================================================================
	Arrow Bundle
	=================================================================
	*/

	/*
	Returns our arrow bundle
	*/
	UArrowBundleComponent* GetArrowBundle();

	/**
	Sets our arrow bundle to the new arrow bundle.
	Doesn't work if the new arrow bundle isn't attached to us.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	bool SetArrowBundle(UArrowBundleComponent* NewArrowBundle);

	/*
	=================================================================
	Rings
	=================================================================
	*/

	/*
	Returns our first ring
	*/
	URingComponent* GetFirstRing();

	/**
	Sets our first ring to the new ring.
	Doesn't work if the new ring isn't attached to us.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	bool SetFirstRing(URingComponent* NewRing);

	/*
	Returns our second ring
	*/
	URingComponent* GetSecondRing();

	/**
	Sets our second ring to the new ring.
	Doesn't work if the new ring isn't attached to us.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	bool SetSecondRing(URingComponent* NewRing);

protected:

	/*
	=================================================================
	Our properties
	=================================================================
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UWeaponComponent* Weapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UArmorComponent* Armor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UPotionComponent* Potion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UArrowBundleComponent* ArrowBundle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	URingComponent* FirstRing;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	URingComponent* SecondRing;
	
};
