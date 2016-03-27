# Concept: Saving and Level Transitions

Saving the game is implemented with the
[`SaveGame` class](https://docs.unrealengine.com/latest/INT/Gameplay/SaveGame/Blueprints/index.html)
of Unreal Engine. The save game class of Ambosia is called `AmobsiaSavegame` and it contains
information about the state of all gameplay elements:

The gameplay stats are stored as float values, just like the experience values too. The current
level is indicated by a `Name` variable, which can be passed into the `openLevel` node. The player
transform is stored too. The Items are stored in two lists: the first one lists the classes of each
item and the second one the stack sizes. The indices of the active items are stored as integer
values.

Saving itself is done by Actors which derive from `BaseSavepoint`: When the player pawn overlaps
with the savepoint, it will gather all required values and store them.

## Other concepts

* [Fighting](Concept_Fighting.md)
* [GameplaySystemComponent](Concept_GameplaySystemComponent.md)
* [ItemComponent](Concept_ItemComponent.md)
* [Looting and experience](Concept_Looting&Experience.md)