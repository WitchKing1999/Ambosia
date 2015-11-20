// (C) Flumminard 2015

#pragma once

#include "Components/SceneComponent.h"
#include "InventoryComponent.h"
#include "GameplayValuesComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AMBOSIA_API UGameplayValuesComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameplayValuesComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void AffectHealthPoints(float Delta);

	float GetHealthPoints();
	void SetHealthPoints(float HealthPoints);
	float GetHealthPointsLimit();
	float GetEffectiveHealthPointsLimit();
	void SetHealthPointsLimit(float HealthPointsLimit);
	float GetAttackPoints();
	float GetEffectiveAttackPoints();
	void SetAttackPoints(float AttackPoints);
	float GetDefenceFactor();
	float GetEffectiveDefenceFactor();
	void SetDefenceFactor(float DefenceFactor);

	UInventoryComponent* GetInventory();
	void SetInventory(UInventoryComponent* Inventory);

protected:

	UInventoryComponent* Inventory;

	float HealthPoints;
	float HealthPointsLimit;
	float AttackPoints;
	float DefenceFactor;
	
};
