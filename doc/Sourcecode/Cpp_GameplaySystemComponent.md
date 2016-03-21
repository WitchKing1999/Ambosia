# Gameplay System Component

Path: `Source/Ambosia/GameplaySystemComponent.h`

Inherits: [`SceneComponent`](https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Components/USceneComponent/index.html)

## Syntax

`UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))  
class AMBOSIA_API UGameplaySystemComponent : public USceneComponent`

## Variables

### `float` `HealthPoints`

* property options: `EditAnywhere`, `BlueprintReadOnly`
* category: `GameplayValues/Health Points`

### `float` `HealthPointsLimit`

* property options: `EditAnywhere`, `BlueprintReadOnly`
* category: `GameplayValues/Health Points`

### `float` `AttackPoints`

* property options: `EditAnywhere`, `BlueprintReadOnly`
* category: `GameplayValues/Attack Points`

### `float` `MagicalAttackPoints`

* property options: `EditAnywhere`, `BlueprintReadOnly`
* category: `GameplayValues/Attack Points`

### `float` `Mana`

* property options: `EditAnywhere`, `BlueprintReadOnly`
* category: `GameplayValues/Mana`

### `float` `ManaLimit`

* property options: `EditAnywhere`, `BlueprintReadOnly`
* category: `GameplayValues/Mana`

### `float` `ManaRegenerationPerSec`

* property options: `EditAnywhere`, `BlueprintReadOnly`
* category: `GameplayValues/Mana`

### [`UWeaponComponent*`](Cpp_WeaponComponent.md) `Weapon`

* property options: `EditAnywhere`, `BlueprintReadOnly`
* category: `Inventory`

### [`UArmorComponent*`](Cpp_ArmorComponent.md) `Armor`

* property options: `EditAnywhere`, `BlueprintReadOnly`
* category: `Inventory`

### [`UPotionComponent*`](Cpp_PotionComponent.md) `Potion`

* property options: `EditAnywhere`, `BlueprintReadOnly`
* category: `Inventory`

### [`UArrowBundleComponent*`](Cpp_ArrowBundleComponent.md) `ArrowBundle`

* property options: `EditAnywhere`, `BlueprintReadOnly`
* category: `Inventory`

### [`URingComponent*`](Cpp_RingComponent.md) `FirstRing`

* property options: `EditAnywhere`, `BlueprintReadOnly`
* category: `Inventory`

### [`URingComponent*`](Cpp_RingComponent.md) `SecondRing`

* property options: `EditAnywhere`, `BlueprintReadOnly`
* category: `Inventory`

### [`UAmuletComponent*`](Cpp_AmuletComponent.md) `Amulet`

* property options: `EditAnywhere`, `BlueprintReadOnly`
* category: `Inventory`

## Constructors

### `UGameplaySystemComponent()`

Sets default values for this component's properties

## Functions

### [`UItemComponent*`](Cpp_ItemComponent.md) `CreateAndAddItem(`[`UClass*`](https://docs.unrealengine.com/latest/INT/API/Runtime/CoreUObject/UObject/UClass/index.html) ` ItemClass)`

Creates an Item from the given class and attaches it to us.  
Returns the created Item or NULL, if the creation failed.  

* function options: `BlueprintCallable`
* category: `Component/AddComponent`

### `float` `GetHealthPoints()`

Returns our health points

### `void SetHealthPoints(float NewHealthPoints)`

Sets our health points to the new health points.  
If the new health points are bigger than the health points limit,  
our health points will be set to the limit.

* function options: `BlueprintCallable`
* category: `Variables/Gameplay Values/Health Points`

### `void AffectHealthPoints(float Delta)`

Adds the delta value to our health points.  
Since we use "SetHealthPoints", the new health points can't be bigger  
than the health points limit. Also, if the delta is negative,  
we will ask our armor to reduce our delta.

* function options: `BlueprintCallable`
* category: `Variables|Gameplay Values|Health Points`

### `float GetHealthPointsLimit()`

Returns our raw health points limit

### `float GetEffectiveHealthPointsLimit()`

Returns our health points limit, modified by our items

* function options: `BlueprintPure`
* category: `Variables/Gameplay Values/Health Points`

### `void SetHealthPointsLimit(float NewHealthPointsLimit)`

Sets our health points limit. If our health points are bigger than  
the new limit, the health points will be also set to it.

* function options: `BlueprintCallable`
* category: `Variables/Gameplay Values/Health Points`

### `void AffectHealthPointsLimit(float Delta)`

Adds the delta value to our health points limit.  
Since we use "SetHealthPointsLimit", our health points won't be bigger  
than our new limit.

* function options: `BlueprintCallable`
* category: `Variables/Gameplay Values/Health Points`

### `float GetRawAttackPoints()`

Returns our raw attack points

### `float GetAttackPoints()`

Returns our attack points, modified by our items

* function options: `BlueprintPure`
* category: `Variables/Gameplay Values/Attack Points`

### `void SetAttackPoints(float NewAttackPoints)`

Sets our attack points to the new attack points.

* function options: `BlueprintCallable`
* category: `Variables|Gameplay Values|Attack Points`

### `void AffectAttackPoints(float Delta)`

Adds the delta value to our attack points.

* function options: `BlueprintCallable`
* category: `Variables/Gameplay Values/Attack Points`

### `float GetRawMagicalAttackPoints()`

Returns our raw magical attack points

### `float GetMagicalAttackPoints()`

Returns our magical attack points, modified by our items

* function options: `BlueprintPure`
* category: `Variables/Gameplay Values/Attack Points`

### `void SetMagicalAttackPoints(float NewMagicalAttackPoints)`

Sets our magical attack points to the new magical attack points.

* function options: `BlueprintCallable`
* category: `Variables/Gameplay Values/Attack Points`

### `void AffectMagicalAttackPoints(float Delta)`

Adds the delta value to our magical attack points.

* function options: `BlueprintCallable`
* categroy: `Variables|Gameplay Values|Attack Points`

### `float GetMana()`

Returns our mana points

### `void SetMana(float NewMana)`

Sets our mana to the new mana.  
If the new mana is bigger than the mana limit,  
our mana will be set to the limit.

* function options: `BlueprintCallable`
* category: `Variables|Gameplay Values|Mana`

### `void AffectMana(float Delta)`

Adds the delta value to our mana.  
Since we use "SetMana", the new mana can't be bigger  
than the mana limit. Also, if delta is negative,  
we will ask our armor to reduce our delta.

* function options: `BlueprintCallable`
* category: `Variables/Gameplay Values/Mana`

### `float GetRawManaLimit()`

Returns our raw mana limt

### `float GetManaLimit()`

Returns our mana limit, modified by our items

* function options: `BlueprintPure`
* category: `Variables/Gameplay Values/Mana`

### `void SetManaLimit(float NewManaLimit)`

Sets our mana limit. If our mana is bigger than  
the new limit, the mana will be also set to it.

* function options: `BlueprintCallable`
* category: `Variables/Gameplay Values/Mana`

### `void AffectManaLimit(float Delta)`

Adds the delta value to our mana limit.  
Since we use "SetManaLimit", our mana won't be bigger  
than our new limit.

* function options: `BlueprintCallable`
* category: `Variables/Gameplay Values/Mana`

### `float GetRawManaRegenerationPerSec()`

Returns our raw mana regeneration

### `float GetManaRegenerationPerSec()`

Returns our mana regeneration, modified by our items

* function options: `BlueprintPure`
* category: `Variables|Gameplay Values|Mana`

### `void SetManaRegenerationPerSec(float NewManaReg)`

Sets our mana regeneration

* function options: `BlueprintCallable`
* category: `Variables/Gameplay Values/Mana`

### `void AffectManaRegeneration(float Delta)`

Adds the delta to our mana regeneration

* function options: `BlueprintCallable`
* category: `Variables/Gameplay Values/Mana`

### [`UWeaponComponent*`](Cpp_WeaponComponent.md) `GetWeapon()`

Returns our weapon

### `bool SetWeapon(`[`UWeaponComponent*`](Cpp_WeaponComponent.md) `NewWeapon)`

Sets our weapon to the new weapon.  
Doesn't work if the new weapon isn't attached to us.

* function options: `BlueprintCallable`
* category: `Variables/Inventory`

### [`UArmorComponent*`](Cpp_ArmorComponent.md) `GetArmor()`

Returns our Armor

### `bool SetArmor(`[`UArmorComponent*`](Cpp_ArmorComponent.md) `NewArmor)`

Sets our armor to the new armor.  
Doesn't work if the new armor isn't attached to us.

* function options: `BlueprintCallable`
* category: `Variables/Inventory`

### [`UPotionComponent*`](Cpp_PotionComponent.md) `GetPotion()`

Returns our potion

### `bool SetPotion(`[`UPotionComponent*`](Cpp_PotionComponent.md) `NewPotion)`

Sets our potion to the new potion.  
Doesn't work if the new potion isn't attached to us.

* function options: `BlueprintCallable`
* category: `Variables/Inventory`

### [`UArrowBundleComponent*`](Cpp_ArrowBundleComponent.md) `GetArrowBundle()`

Returns our arrow budle

### `bool SetArrowBundle(`[`UArrowBundleComponent*`](Cpp_ArrowBundleComponent.md) `NewArrowBundle)`

Sets our arrow bundle to the new arrow bundle.  
Doesn't work if the new arrow bundle isn't attached to us.

* function options: `BlueprintCallable`
* category: `Variables/Inventory`

### [`UFirstRingComponent*`](Cpp_FirstRingComponent.md) `GetFirstRing()`

Returns our first ring

### `bool SetFirstRing(`[`UFirstRingComponent*`](Cpp_FirstRingComponent.md) `NewFirstRing)`

Sets our first ring to the new first ring.  
Doesn't work if the new first ring isn't attached to us.

* function options: `BlueprintCallable`
* category: `Variables/Inventory`

### [`USecondRingComponent*`](Cpp_SecondRingComponent.md) `GetSecondRing()`

Returns our second ring

### `bool SetSecondRing(`[`USecondRingComponent*`](Cpp_SecondRingComponent.md) `NewSecondRing)`

Sets our second ring to the new second ring.  
Doesn't work if the new second ring isn't attached to us.

* function options: `BlueprintCallable`
* category: `Variables/Inventory`

### [`UAmuletComponent*`](Cpp_AmuletComponent.md) `GetAmulet()`

Returns our amulet

### `bool SetAmulet(`[`UAmuletComponent*`](Cpp_AmuletComponent.md) `NewAmulet)`

Sets our amulet to the new amulet.  
Doesn't work if the new amulet isn't attached to us.

* function options: `BlueprintCallable`
* category: `Variables/Inventory`