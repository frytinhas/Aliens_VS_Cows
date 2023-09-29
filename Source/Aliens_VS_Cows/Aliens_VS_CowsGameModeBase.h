// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Aliens_VS_CowsGameModeBase.generated.h"

// Forward declarations
class AC_AlienShip;

UCLASS()
class ALIENS_VS_COWS_API AAliens_VS_CowsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

// Variables
public:
	UPROPERTY(BlueprintReadOnly, Category = "References")
	AC_AlienShip* AlienShipReference = nullptr;
	
// Functions
	AAliens_VS_CowsGameModeBase();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCollectCow();

protected:
	UFUNCTION(BlueprintNativeEvent)
	void EndGame();
	
};
