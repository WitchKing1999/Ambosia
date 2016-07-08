// (C) Flumminard 2015-2016

#pragma once

#include "GameFramework/Actor.h"
#include "BaseSavepoint.generated.h"

/*
Base class for savepoints.
When the player overlaps it, it sends a message
to the player controller to save the game.
*/
UCLASS()
class AMBOSIA_API ABaseSavepoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSavepoint();

	UFUNCTION()
	virtual void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
};
