// (C) Flumminard 2015

#pragma once

#include "Items/ItemComponent.h"
#include "WeaponComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Items), meta = (BlueprintSpawnableComponent))
class AMBOSIA_API UWeaponComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:
	UWeaponComponent();

	UFUNCTION(BlueprintCallable, Category = "Item")
	void Attack();

	float GetAttackFactor();

	UFUNCTION(BlueprintCallable, Category="Item")
	float AffectAttackPoints(float RawAttackPoints);

	float GetManaCost();

	float GetMagicalAttackFactor();

	UFUNCTION(BlueprintCallable, Category = "Item")
	float AffectMagicalAttackPoints(float RawMagicalAttackPoints);
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float AttackFactor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float ManaCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float MagicalAttackFactor;
};
