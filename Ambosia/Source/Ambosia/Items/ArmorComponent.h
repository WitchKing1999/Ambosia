// (C) Flumminard 2015

#pragma once

#include "Items/ItemComponent.h"
#include "ArmorComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Items), meta = (BlueprintSpawnableComponent))
class AMBOSIA_API UArmorComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:
	UArmorComponent();

	float GetDefenceFactor();
	
	UFUNCTION(BlueprintCallable, Category = "Item")
	float AffectDamage(float RawDamage);

	float GetMagicalDefenceFactor();

	UFUNCTION(BlueprintCallable, Category = "Item")
	float AffectMagicalDamage(float RawMagicalDamage);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float DefenceFactor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float MagicalDefenceFactor;
};
