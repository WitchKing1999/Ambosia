// (C) Flumminard 2015

#pragma once

#include "Components/SceneComponent.h"
#include "ItemComponent.generated.h"

// This is the item base class.
UCLASS( ClassGroup=(Items), meta=(BlueprintSpawnableComponent), Blueprintable)
class AMBOSIA_API UItemComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemComponent();

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
	bool Action();

	virtual bool Action_Implementation();

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

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
	float ModifyHealthPoints(float HealthPoints);

	virtual float ModifyHealthPoints_Implementation(float HealthPoints);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
	float ModifyHealthPointsLimit(float HealthPointsLimit);

	virtual float ModifyHealthPointsLimit_Implementation(float HealthPointsLimit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
	float ModifyAttackPoints(float AttackPoints);

	virtual float ModifyAttackPoints_Implementation(float AttackPoints);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
	float ModifyMagicalAttackPoints(float MagicalAttackPoints);

	virtual float ModifyMagicalAttackPoints_Implementation(float MagicalAttackPoints);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
	float ModifyMana(float Mana);

	virtual float ModifyMana_Implementation(float Mana);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
	float ModifyManaLimit(float ManaLimit);

	virtual float ModifyManaLimit_Implementation(float ManaLimit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
	float ModifyManaRegeneration(float ManaRegeneration);

	virtual float ModifyManaRegeneration_Implementation(float ManaRegeneration);

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
