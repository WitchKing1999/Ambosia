// (C) Flumminard 2015-2016

#pragma once

#include "Savepoints/BaseSavepoint.h"
#include "BaseSavingPortal.generated.h"

#define LOADINGSCREEN_PATH "/Game/Menues/LoadingScreenWorld"

/*
Base class for saving portals.
Does the same like a save point, but after the player
controller saved the game, it overrides the world path
and the player location and opens the loading screen,
which opens the next level.
*/
UCLASS()
class AMBOSIA_API ABaseSavingPortal : public ABaseSavepoint
{
	GENERATED_BODY()
	
public:
	ABaseSavingPortal();

	UFUNCTION()
	virtual void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor) override;

protected:

	/*
	The transform the player character will have when it enters
	the next level.
	*/
	UPROPERTY(EditAnywhere, Category = "SavefileSaving")
	FTransform TargetTransform;

	/*
	The path to the next level.
	*/
	UPROPERTY(EditAnywhere, Category = "SavefileSaving")
	FName TargetWorldPath;
	
};
