// (C) Flumminard 2015

#pragma once

#include "Components/SceneComponent.h"
#include "ItemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AMBOSIA_API UItemComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	float GetHealthPointsLimit();
	float GetAttackPoints();
	float GetDefenceFactor();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float HealthPointsLimit;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackPoints;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DefenceFactor;
	
};
