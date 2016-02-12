// (C) Flumminard 2015

#pragma once

#include "Components/SceneComponent.h"
#include "ItemComponent.generated.h"

/*
This is the item base class.
*/
UCLASS(ClassGroup=(Items), meta=(BlueprintSpawnableComponent), Blueprintable)
class AMBOSIA_API UItemComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemComponent();

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	Runs an action and returns true, if the action was successfull and false it not.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
	bool Action();
	virtual bool Action_Implementation();

	/*
	Returns the name of this item.
	*/
	FString GetName();

	/*
	Returns the description of this item.
	*/
	FString GetDescription();

	/*
	Returns whether we are stackable or not.
	*/
	bool IsStackable();

	/*
	Returns the stack size of this item.
	*/
	int32 GetStackSize();

	/*
	Sets our stack size to the new stack size
	If the new stack size is equal or lower zero, we will be destroyed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Stacking")
	void SetStackSize(int32 NewStackSize);

	/*
	Adds the delta value to our stack size
	Since it uses "SetStackSize", we will be destroyed when the stack size
	reaches zero.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Stacking")
	void AffectStackSize(int32 Delta);

	/*
	Adds the stack size of the given Item to our stack size.
	Only works if the given item and we are objects of the same class.
	Destroyes the given item.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Stacking")
	void AddItemToStack(UItemComponent* Item);

	/*
	Sets the time till we are cooled down to our cooldown time.
	*/
	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	bool StartCooldown();

	/*
	Will be called when we are cooled down.
	By default, it does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cooldown")
	void OnCooledDown();
	virtual void OnCooledDown_Implementation();

	/*
	Returns the time till we are cooled down in seconds.
	*/
	float GetTimeTillCooled();

	/*
	Returns the time it takes us to cool down in seconds.
	*/
	float GetCooldownTime();

	/*
	Returns our drop chance.
	*/
	float GetDropChance();

	/*
	Takes the health points and modifies and returns them.
	By default, this does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyHealthPoints(float HealthPoints);
	virtual float ModifyHealthPoints_Implementation(float HealthPoints);

	/*
	Takes the health points limit and modifies and returns them.
	By default, this does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyHealthPointsLimit(float HealthPointsLimit);
	virtual float ModifyHealthPointsLimit_Implementation(float HealthPointsLimit);

	/*
	Takes the attack points and modifies and returns them.
	By default, this does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyAttackPoints(float AttackPoints);
	virtual float ModifyAttackPoints_Implementation(float AttackPoints);

	/*
	Takes the magical attack points and modifies and returns them.
	By default, this does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyMagicalAttackPoints(float MagicalAttackPoints);
	virtual float ModifyMagicalAttackPoints_Implementation(float MagicalAttackPoints);

	/*
	Takes the mana and modifies and returns them.
	By default, this does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyMana(float Mana);
	virtual float ModifyMana_Implementation(float Mana);

	/*
	Takes the mana limit and modifies and returns them.
	By default, this does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyManaLimit(float ManaLimit);
	virtual float ModifyManaLimit_Implementation(float ManaLimit);

	/*
	Takes the mana regeneration and modifies and returns them.
	By default, this does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyManaRegeneration(float ManaRegeneration);
	virtual float ModifyManaRegeneration_Implementation(float ManaRegeneration);

protected:

	/*
	Our screen name
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FString Name;

	/*
	Our screen description
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FString Description;

	/*
	Our stack size
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stacking")
	int32 StackSize;

	/*
	Holds the information whether we are stackable or not.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stacking")
	bool bStackable;

	/*
	The time till we are cooled down
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooldown")
	float TimeTillCooled;

	/*
	The time it takes us to cool down
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooldown")
	float CooldownTime;

	/*
	The chance that we will be droped after the death of our owner
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	float DropChance;
	
};
