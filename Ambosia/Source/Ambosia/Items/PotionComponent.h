// (C) Flumminard 2015

#pragma once

#include "Items/ItemComponent.h"
#include "GameplayValuesComponent.h"
#include "PotionComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Items), meta = (BlueprintSpawnableComponent))
class AMBOSIA_API UPotionComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:
	
	UPotionComponent();

	virtual bool Action_Implementation() override;

	virtual float ModifyHealthPoints_Implementation(float HealthPoints) override;

	virtual float ModifyMana_Implementation(float Mana) override;

	float GetHealthPoints();

	float GetMana();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float HealthPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float Mana;
};
