// (C) Flumminard 2015

#pragma once

#include "Components/BoxComponent.h"
#include "GameplayValuesComponent.h"
#include "SwordBoxComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AMBOSIA_API USwordBoxComponent : public UBoxComponent
{
	GENERATED_BODY()
	
public:
	USwordBoxComponent();

	void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "SwordBox")
	void ExtendSword();

	UFUNCTION(BlueprintCallable, Category = "SwordBox")
	void RetractSword();

	bool GetIsSwordExtended();

	UGameplayValuesComponent* GetGameplayValues();
	void SetGameplayValues(UGameplayValuesComponent* newGameplayValues);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SwordBox")
	FVector SwordSizeExtended;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "SwordBox")
	bool IsSwordExtended;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SwordBox")
	UGameplayValuesComponent* OwnGameplayValues;
	
};
