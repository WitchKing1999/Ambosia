// (C) Flumminard 2015

#pragma once

#include "Components/SceneComponent.h"
#include "ItemComponent.generated.h"

/*
This is the item base class. It has a name, a description,
is stackable and provides an action, which may require us to be cooled
down. Also it can modify all gameplay values.
*/
UCLASS(ClassGroup=(Items), meta=(BlueprintSpawnableComponent), Blueprintable)
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

	UFUNCTION(BlueprintCallable, Category = "Variables|Stacking")
	void SetStackSize(float NewStackSize);

	UFUNCTION(BlueprintCallable, Category = "Variables|Stacking")
	void AffectStackSize(float Delta);

	UFUNCTION(BlueprintCallable, Category = "Variables|Stacking")
	void AddItemToStack(UItemComponent* Item);

	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	void StartCooldown();

	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	void OnCooledDown();

	float GetTimeTillCooled();

	float GetCooldownTime();

	bool IsStackable();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyHealthPoints(float HealthPoints);

	virtual float ModifyHealthPoints_Implementation(float HealthPoints);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyHealthPointsLimit(float HealthPointsLimit);

	virtual float ModifyHealthPointsLimit_Implementation(float HealthPointsLimit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyAttackPoints(float AttackPoints);

	virtual float ModifyAttackPoints_Implementation(float AttackPoints);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyMagicalAttackPoints(float MagicalAttackPoints);

	virtual float ModifyMagicalAttackPoints_Implementation(float MagicalAttackPoints);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyMana(float Mana);

	virtual float ModifyMana_Implementation(float Mana);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyManaLimit(float ManaLimit);

	virtual float ModifyManaLimit_Implementation(float ManaLimit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyManaRegeneration(float ManaRegeneration);

	virtual float ModifyManaRegeneration_Implementation(float ManaRegeneration);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FString Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stacking")
	float StackSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stacking")
	bool bStackable;

	UPROPERTY(BlueprintReadOnly, Category = "Cooldown")
	float TimeTillCooled;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cooldown")
	float CooldownTime;
	
};
