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

	UFUNCTION(BlueprintCallable, Category = "Item")
	void AffectGameplayValues(UGameplayValuesComponent* GVComponent);

	float GetHealthPoints();

	UFUNCTION(BlueprintCallable, Category = "Variables|Item")
	float GetMana();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float HealthPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float Mana;
};
