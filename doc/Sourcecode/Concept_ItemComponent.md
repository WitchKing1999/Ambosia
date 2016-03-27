# Concept: Item Components

Items are components which provide an action or a passive effect for the player or an AI. To do so, they must be attached to a [GameplaySystemComponent](Concept_GameplaySystemComponent.md). There is one base class and some derived special classes. The base for every item is the [ItemComponent](Cpp_ItemComponent.md), which defines some abstract and concrete functionalities:  
First, it's **stackable**, which means that it has a stack size, which can be in- and decreased. Also, you can add some items of the same class together. Second, it can cool down: When the `startCooldown`-function gets called, it sets a timer to a preset value, which gets decreased every tick. When the timer reaches zero, an event gets called to handle it.  
Also, it provides a name, a description and an icon, which are used by the UI to present the item.  
But these are just side functionalities; The core functions are the `Action` and the `Modify` functions:
The **`Action`** function can be overriden by every child class to define the actions of the item, for example a potion adds health points or a bow launches an arrow. The **`Modify`** functions can be overriden to and are consulted to modify gameplay stats or damage.

There are also some quite important sub-base classes: The **weapon**, the **armor**, the **potion**, the **arrow bundle**, the **ring** and the **amulet**.

The **weapon** adds some weapon-related functions: First, there is a function that spawns actors of a given class at a given locations relative to the actor who spawns it. Second, there is a function that plots a line that goes forward from the shooting actor and applies damage to the first actor it hits. Third, it can claim mana and arrow bundle costs. It can check, if there is enough mana for an action and reduces it by this amount. I does the same for the arrow bundle costs, but it also checks if the needed type of an arrow bundle is present and if it's stack size is high enough. Next, it modifies the attack values in a quite special way: First, it multiplies the attack points with a fixed factor, but second, it generates a random number and compares it with the preset critical chance. If the random number is lower or equal to the critical chance, it multiplies the attack points with 2!

The **armor** is a passive item. It could be asked for an action, since it still has the `Action` function from the item, but it is never called. It speciality are the `Modify` functions: It multiplies dealt damage by a fixed factor, which is usually lower than one. Thats all about the armor.

The **potion** has an action, which adds a fixed amount of health points or mana to its GameplaySystemComponent and reduces its stack by one.

The **arrow bundle** holds a fixed actor class which may be used by some weapons like a bow.

The **ring** and the **amulet** are absolutly identical and modify the health points and mana limits, the attack points and the mana regeneration.

## Other concepts

* [Fighting](Concept_Fighting.md)
* [GameplaySystemComponent](Concept_GameplaySystemComponent.md)
* [Looting and experience](Concept_Looting&Experience.md)
* [Saving and level transitions](Concept_Saving&LevelTransitions.md)
