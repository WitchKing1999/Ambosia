// (C) Flumminard 2015-2016

#pragma once

#include "GameFramework/Actor.h"
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
};
