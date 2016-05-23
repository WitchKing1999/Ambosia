// (C) Flumminard 2015-2016

#pragma once

#include "GameFramework/HUD.h"
#include "BaseAmbosiaHUD.generated.h"

/**
 * 
 */
UCLASS()
class AMBOSIA_API ABaseAmbosiaHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	ABaseAmbosiaHUD();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "HUD")
	void OpenInventory();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "HUD")
	void CloseInventory();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "HUD")
	void ShowHUD();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "HUD")
	void HideHUD();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "HUD")
	void ShowInteractIcon();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "HUD")
	void HideInteractIcon();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "HUD")
	void OpenReturnToMainMenuWidget();

	UPROPERTY(BlueprintReadWrite, Category = "HUD")
	bool bInventoryOpen;

	UPROPERTY(BlueprintReadWrite, Category = "HUD")
	bool bHUDOpen;
};
