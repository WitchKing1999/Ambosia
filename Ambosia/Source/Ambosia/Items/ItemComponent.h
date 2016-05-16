// (C) Flumminard 2015

#pragma once

#include "Components/SceneComponent.h"
#include "Engine/Texture.h"
#include "ItemComponent.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	VE_Item			UMETA(DisplayName = "Item"),
	VE_Weapon		UMETA(DisplayName = "Weapon"),
	VE_Armor		UMETA(DisplayName = "Armor"),
	VE_ArrowBundle	UMETA(DisplayName = "Arrow Bundle"),
	VE_Potion		UMETA(DisplayName = "Potion"),
	VE_Ring			UMETA(DisplayName = "Ring"),
	VE_Amulet		UMETA(DisplayName = "Amulet")
};

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

	EItemType GetItemType();

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
	float ModifyInfightHealthPointsLimit(float HealthPointsLimit);
	virtual float ModifyInfightHealthPointsLimit_Implementation(float HealthPointsLimit);

	/*
	Takes the health points limit and modifies and returns them.
	By default, this does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyDisplayHealthPointsLimit(float HealthPointsLimit);
	virtual float ModifyDisplayHealthPointsLimit_Implementation(float HealthPointsLimit);

	/*
	Takes the attack points and modifies and returns them.
	By default, this does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyInfightAttackPoints(float AttackPoints);
	virtual float ModifyInfightAttackPoints_Implementation(float AttackPoints);

	/*
	Takes the attack points and modifies and returns them.
	By default, this does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyDisplayAttackPoints(float AttackPoints);
	virtual float ModifyDisplayAttackPoints_Implementation(float AttackPoints);

	/*
	Takes the magical attack points and modifies and returns them.
	By default, this does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyInfightMagicalAttackPoints(float MagicalAttackPoints);
	virtual float ModifyInfightMagicalAttackPoints_Implementation(float MagicalAttackPoints);

	/*
	Takes the magical attack points and modifies and returns them.
	By default, this does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyDisplayMagicalAttackPoints(float MagicalAttackPoints);
	virtual float ModifyDisplayMagicalAttackPoints_Implementation(float MagicalAttackPoints);

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
	float ModifyInfightManaLimit(float ManaLimit);
	virtual float ModifyInfightManaLimit_Implementation(float ManaLimit);

	/*
	Takes the mana limit and modifies and returns them.
	By default, this does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyDisplayManaLimit(float ManaLimit);
	virtual float ModifyDisplayManaLimit_Implementation(float ManaLimit);

	/*
	Takes the mana regeneration and modifies and returns them.
	By default, this does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyInfightManaRegeneration(float ManaRegeneration);
	virtual float ModifyInfightManaRegeneration_Implementation(float ManaRegeneration);

	/*
	Takes the mana regeneration and modifies and returns them.
	By default, this does nothing.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gameplay Values")
	float ModifyDisplayManaRegeneration(float ManaRegeneration);
	virtual float ModifyDisplayManaRegeneration_Implementation(float ManaRegeneration);

	/*
	Our screen name
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Name;

	/*
	Our screen description
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Description;

	/*
	Our icon
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture* Icon;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	EItemType ItemType;

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
