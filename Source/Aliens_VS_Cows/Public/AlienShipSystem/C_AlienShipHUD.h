// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "C_AlienShipHUD.generated.h"

/**
 * 
 */
UCLASS()
class ALIENS_VS_COWS_API AC_AlienShipHUD : public AHUD
{
	GENERATED_BODY()

// Variables
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Info")
	const TSubclassOf<UUserWidget> AlienShipWidgetClass = UUserWidget::StaticClass();

public:
	UPROPERTY(BlueprintReadOnly, Category = "Info")
	UUserWidget* AlienShipWidget = nullptr;
	
// Functions
protected:
	virtual void BeginPlay() override;
};
