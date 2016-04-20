// (C) Flumminard 2015-2016

#pragma once

#include "GameFramework/SaveGame.h"
#include "MetaSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class AMBOSIA_API UMetaSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UMetaSaveGame();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Variables|SaveGame")
	FString GetCurrentUserName();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
	int32 CurrentUserIndex;
	
};
