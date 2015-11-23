// (C) Flumminard 2015

#pragma once

#include "Components/ActorComponent.h"
#include "InventoryComponent.h"
#include "GameplayValuesComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AMBOSIA_API UGameplayValuesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameplayValuesComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintCallable, Category = "GameplayValues")
	void AffectHealthPoints(float Delta);

	float GetHealthPoints();

	UFUNCTION(BlueprintCallable, Category = "Variables|GameplayValues")
	void SetHealthPoints(float HealthPoints);

	float GetHealthPointsLimit();

	UFUNCTION(BlueprintCallable, Category = "Variables|GameplayValues")
	float GetEffectiveHealthPointsLimit();

	UFUNCTION(BlueprintCallable, Category = "Variables|GameplayValues")
	void SetHealthPointsLimit(float HealthPointsLimit);

	float GetAttackPoints();

	UFUNCTION(BlueprintCallable, Category = "Variables|GameplayValues")
	float GetEffectiveAttackPoints();

	UFUNCTION(BlueprintCallable, Category = "Variables|GameplayValues")
	void SetAttackPoints(float AttackPoints);

	float GetDefenceFactor();

	UFUNCTION(BlueprintCallable, Category = "Variables|GameplayValues")
	float GetEffectiveDefenceFactor();

	UFUNCTION(BlueprintCallable, Category = "Variables|GameplayValues")
	void SetDefenceFactor(float DefenceFactor);

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GameplayValues")
	float HealthPoints;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GameplayValues")
	float HealthPointsLimit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameplayValues")
	float AttackPoints;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameplayValues")
	float DefenceFactor;
	
};
