// (C) Flumminard 2015-2016

#pragma once

#include "GameFramework/SaveGame.h"
#include "MetaSaveGame.generated.h"

/*
A save game container that contains
the information about the current user name
and user index. When the player controller loads
the game, it first loads the meta save game, takes
it information and loads the proper save game.
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
