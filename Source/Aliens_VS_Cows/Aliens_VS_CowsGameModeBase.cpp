// Copyright Epic Games, Inc. All Rights Reserved.


#include "Aliens_VS_CowsGameModeBase.h"
#include "AlienShipSystem/C_AlienShip.h"
#include "AlienShipSystem/C_AlienShipHUD.h"
#include "CowSystem/C_Cow.h"
#include "Kismet/GameplayStatics.h"

AAliens_VS_CowsGameModeBase::AAliens_VS_CowsGameModeBase()
{
	// Set default values for game mode
	HUDClass = AC_AlienShipHUD::StaticClass();
	DefaultPawnClass = AC_AlienShip::StaticClass();
}

void AAliens_VS_CowsGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Get alien ship ref
	AlienShipReference = Cast<AC_AlienShip>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	// Bind event to on collect a cow
	AlienShipReference->OnCollectCow.BindUFunction(this, "OnCollectCow");
}

void AAliens_VS_CowsGameModeBase::OnCollectCow()
{
	// Get all cows in level
	TArray<AActor*> CowsInLevel;
	UGameplayStatics::GetAllActorsOfClass(this, AC_Cow::StaticClass(), CowsInLevel);

	//? Verify if have 1> cows in level and end game if yes
	if (CowsInLevel.IsEmpty())
	{
		EndGame();
	}
}

void AAliens_VS_CowsGameModeBase::EndGame_Implementation()
{
	UKismetSystemLibrary::PrintString(this, "End game! (Add a implementation using blueprints)");
}
