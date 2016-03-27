# Concept: Fighting

Basicly, dealing damage is implemented with the
[damage system of Unreal Engine](https://www.unrealengine.com/blog/damage-in-ue4). All characters
pass damage they get up to their controllers, which pass them up to the
[GameplaySystemComponent](Concept_GameplaySystemComponent.md). When you use the `PlotHitLine`
function of a weapon, this is done automaticly for you, but if you would like to create a weapon
that doesn't use this function, you will need some advices:

The GSC expects you to use the [`AmbosiaDamageType`](Cpp_AmbosiaDamageType.md). If the damage is not
passed with an `AmbosiaDamageType`, the `GSC` won't reduce the damage with it's armor. Just mind
that.

Why does the `GSC` want an `AmbosiaDamageType`? It tells it whether the damage is magical or not and
whether it should ask the armor to use magical or the plain defence factor.

## Other concepts

* [GameplaySystemComponent](Concept_GameplaySystemComponent.md)
* [ItemComponent](Concept_ItemComponent.md)
* [Looting and experience](Concept_Looting&Experience.md)
* [Saving and level transitions](Concept_Saving&LevelTransitions.md)