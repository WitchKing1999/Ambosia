// (C) Flumminard 2015-2016

#pragma once

#include "Savepoints/BaseSavepoint.h"
#include "BaseSavingPortal.generated.h"

#define LOADINGSCREEN_PATH "/Game/Menues/LoadingScreenWorld"

/**
 * 
 */
UCLASS()
class AMBOSIA_API ABaseSavingPortal : public ABaseSavepoint
{
	GENERATED_BODY()
	
public:
	ABaseSavingPortal();

	UFUNCTION()
	virtual void BeginPlay();

	UFUNCTION()
	virtual void OnOverlapBegin(class AActor* OtherActor) override;

	UFUNCTION()
	virtual bool SavePosition(class UAmbosiaSaveGame* SaveGame) override;

protected:

	UPROPERTY(EditAnywhere, Category = "SavefileSaving")
	FTransform TargetTransform;
	
};
