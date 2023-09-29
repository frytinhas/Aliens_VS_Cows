// Fill out your copyright notice in the Description page of Project Settings.


#include "AlienShipSystem/C_AlienShipHUD.h"
#include "Blueprint/UserWidget.h"

void AC_AlienShipHUD::BeginPlay()
{
	// Create alien ship HUD
	if (AlienShipWidgetClass)
	{
		AlienShipWidget = CreateWidget(GetOwningPlayerController(), AlienShipWidgetClass);
		AlienShipWidget->AddToViewport();
	}
}
