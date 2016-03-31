// (C) Flumminard 2015-2016

#pragma once

#include "GameFramework/Actor.h"
#include "AmbosiaPlayerController.h"
#include "AmbosiaSaveGame.h"
#include "BaseSavepoint.generated.h"

UCLASS()
class AMBOSIA_API ABaseSavepoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSavepoint();

	UFUNCTION()
	virtual void OnOverlapBegin(class AActor* OtherActor);

	UFUNCTION()
	virtual bool SaveGameplayValues(UAmbosiaSaveGame* SaveGame, AAmbosiaPlayerController* PlayerController, UGameplaySystemComponent* GameplaySystem);

	UFUNCTION()
	virtual bool SavePosition(UAmbosiaSaveGame* SaveGame);

	UFUNCTION()
	virtual bool SaveItems(UAmbosiaSaveGame* SaveGame, UGameplaySystemComponent* GameplaySystem);

protected:

	UPROPERTY(EditAnywhere, Category = "SavefileSaving")
	FName TargetWorldName;
};
