// (C) Flumminard 2015

#pragma once

#include "Items/ItemComponent.h"
#include "GameplayValuesComponent.h"
#include "PotionComponent.generated.h"

/*
This helpful item gives some health points and/or mana.
*/
UCLASS(ClassGroup = (Items), meta = (BlueprintSpawnableComponent))
class AMBOSIA_API UPotionComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:
	
	UPotionComponent();

	/*
	Adds the health points and mana values to the gameplay values component
	of our owner. To be successfull, it requires that the potion is cooled down.
	Also, it will start the cooldown if it was successful.
	*/
	virtual bool Action_Implementation() override;

	/*
	Adds our health points value to the given health points value and returns it.
	*/
	virtual float ModifyHealthPoints_Implementation(float HealthPoints) override;

	/*
	Adds our man value to the given mana value and returns it.
	*/
	virtual float ModifyMana_Implementation(float Mana) override;

	/*
	Returns our health points
	*/
	float GetHealthPoints();

	/*
	Returns our mana
	*/
	float GetMana();

protected:

	/*
	Our Health Points
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Potion")
	float HealthPoints;

	/*
	Our Mana
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Potion")
	float Mana;
};
