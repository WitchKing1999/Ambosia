// (C) Flumminard 2015

#pragma once

#include "Components/SceneComponent.h"
#include "ItemComponent.generated.h"

// This is the item base class.
UCLASS( ClassGroup=(Items), meta=(BlueprintSpawnableComponent) )
class AMBOSIA_API UItemComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemComponent();

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual bool Action();

	FString GetName();

	FString GetDescription();

	float GetStackSize();

	UFUNCTION(BlueprintCallable, Category = "Variables|Item")
	void SetStackSize(float NewStackSize);

	UFUNCTION(BlueprintCallable, Category = "Variables|Item")
	void AffectStackSize(float Delta);

	UFUNCTION(BlueprintCallable, Category = "Variables|Item")
	void AddItemToStack(UItemComponent* Item);

	UFUNCTION(BlueprintCallable, Category = "Variables|Item")
	void StartCooldown();

	UFUNCTION(BlueprintCallable, Category = "Item")
	void OnCooledDown();

	float GetTimeTillCooled();

	float GetCooldownTime();

	bool IsStackable();

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual float ModifyHealthPoints(float HealthPoints);

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual float ModifyHealthPointsLimit(float HealthPointsLimit);

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual float ModifyAttackPoints(float AttackPoints);

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual float ModifyMagicalAttackPoints(float MagicalAttackPoints);

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual float ModifyMana(float Mana);

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual float ModifyManaLimit(float ManaLimit);

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual float ModifyManaRegeneration(float ManaRegeneration);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FString Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float StackSize;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	float TimeTillCooled;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float CooldownTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	bool bStackable;
	
};
