# Concept: Gameplay System Component

The [`GameplaySystemComponent`](Cpp_GameplaySystemComponent.md) (or short `GSC`) provides core
elements for the gameplay of Ambosia. It's purposes can be devided in two parts: **gameplay stats**
and **inventory**. The player and every AI controller has a GSC to deal and take damage.

## Gameplay Stats

There are these stats:

* health points
* health points limit
* mana
* mana limit
* mana regeneration per second
* attack points
* magical attack points

The **health points** indicate the health of the character, when it drops to zero, the controller
will destroy itself and it's pawn. They can be set, increased and descreased, but they can't be
higher than the **health points limit**. This limit can also be set, increased and decreased.  
To deal magical damage, you need mana. Everytime you summon a spell or use a magical weapon, it will
take a fixed amount of mana and you need that mana to do this. If your mana is lower than required,
nothing will happen. Thankfully, your mana regenerates over time. Every second, your **mana
regeneration per second** will be added to your mana until it reaches the **mana limit**.  
When you finally managed to fire you weapon, it will decrease the health points of the hit
player/NPC by your **attack points**. If you used a spell or a magical weapon, the health points
will be decreased by your **magical attack points**  
That's it.

## Inventory

There is another core component class in Ambosia: the items! They are also childs of the famous
SceneComponent, so they can be attached to other SceneComponents like the GameplaySystemComponent.
This document doesn't dig too much into the ItemComponent and it child classes, but you can read
more about it [here](Concept_ItemComponent.md). Basicly, the GSC keeps pointers to items, which are
used as it's active items.

* weapon
* armor
* potion
* arrow bundle
* first ring
* second ring
* amulet

There is a pointer for every base item class, but there are two rings, since you can wear two at the
same time. All these items must be attached to the GSC instance, otherwise the setter denies the
setting and if an item detaches itself from it's GSC and it's an active item, the active item
pointer will be set to null. These pointers are public readable, so every other part of the program
can use them. Some of those items modify one or more gameplay stats: The armor reduces the damage
you take by a fixed factor and your rings and your amulet modify the health points and mana limit,
your mana regeneration and your attack points.


## Continue reading

* [Items](Concept_ItemComponent.md)
* [Fighting & dealing damage](Concept_Fighting.md)
* [Looting & experience](Concept_Looting&Experience.md)
