# Concept: Looting and Experience

## Looting

Every AI controller keeps track of the the controller which hit them last and when it dies, it will
send loot to it. This works with the [`LootCollector` Interface](BP_LootCollector.md), which
contains one function: `receiveLoot`. This function has three parameters: The first two are the
lists `ItemClasses` and `ItemStacks`. With these, the loot collector creates the looted items. The
third is a float value which contains the gained experience points, which will be covered later.

Just get back to the items: When a controller dies, it iterates through its items. Every item has a 
drop chance between zero and one. The controller generates a random number between zero and one and
if the random number is lower or equal to the drop chance of this item, it will get dropped: First,
the class of the item instance gets added to the `ItemClasses` list and second, the stack size gets
added to the `ItemStacks` list. The experience gain is a fixed value, which is configured in the
class defaults of a controller class.  
In the end, the generated lists and the experience gain will be send to the killer of the
died controller.

When a killer receives it's loot, it first adds the experience gain to it's experience points.
Second it creates items from the classes and stack sizes. That's not a very big deal.

## Experience system

Currently, the only class which implements the `LootCollector` interface is the
[`AmbosiaPlayerController`](Cpp_AmbosiaPlayerController.md). As mentioned before, it collects
experience points every time the player kills an NPC. It also collects skill points, which can be
used to train the core player stats like health points limit or attack points. Applying one skill
point to a stat increses the stat by one. To get those skill points, the player must collect
experience points until he reaches the next level. The level heights are stored in a list called
`XPLevels`. Every element in this list represents a level and when the experience points are equal
or higher then the next level height, the skill points get incresed by the level value stored in the
list `SkillPointsList`. Also, every element represents a level.

## Other concepts

* [Fighting](Concept_Fighting.md)
* [GameplaySystemComponent](Concept_GameplaySystemComponent.md)
* [ItemComponent](Concept_ItemComponent.md)
* [Saving and level transitions](Concept_Saving&LevelTransitions.md)