// (C) Flumminard 2015

#pragma once

#include "Items/ItemComponent.h"
#include "GameplayValuesComponent.h"
#include "PotionComponent.generated.h"

/**
 * 
 */
UCLASS()
class AMBOSIA_API UPotionComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:
	
	UPotionComponent();

	bool Action() override;

	float ModifyHealthPoints(float HealthPoint) override;

	float ModifyMana(float Mana) override;

	float GetHealthPoints();

	float GetMana();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float HealthPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float Mana;
};
