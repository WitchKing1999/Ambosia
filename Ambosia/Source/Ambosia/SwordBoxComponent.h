// (C) Flumminard 2015

#pragma once

#include "Components/BoxComponent.h"
#include "GameplayValuesComponent.h"
#include "SwordBoxComponent.generated.h"

/**
 * 
 */
UCLASS()
class AMBOSIA_API USwordBoxComponent : public UBoxComponent
{
	GENERATED_BODY()
	
public:
	USwordBoxComponent();

	void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ExtendSword();
	void RetractSword();
	bool GetIsSwordExtended();

	UGameplayValuesComponent* GetGameplayValues();
	void SetGameplayValues(UGameplayValuesComponent* newGameplayValues);
	
	FVector SwordSizeExtended;

protected:
	bool IsSwordExtended;

	UGameplayValuesComponent* OwnGameplayValues;
	
};
