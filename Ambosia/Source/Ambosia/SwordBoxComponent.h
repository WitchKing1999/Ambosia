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

	//UFUNCTION()
	//virtual void BeginComponentOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void TickComponent(float Delta, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "SwordBox")
	void ExtendSword();

	UFUNCTION(BlueprintCallable, Category = "SwordBox")
	void RetractSword();

	bool GetIsSwordExtended();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SwordBox")
	FVector SwordSizeExtended;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "SwordBox")
	bool IsSwordExtended;
	
};
