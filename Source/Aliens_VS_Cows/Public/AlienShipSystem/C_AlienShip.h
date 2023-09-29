// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetSystemLibrary.h"
#include "C_AlienShip.generated.h"

// Forward declarations
class UNiagaraComponent;
class UBoxComponent;
class USpotLightComponent;
class USphereComponent;

// Event dispatchers
DECLARE_DELEGATE(FOnCollectCow);

UCLASS()
class ALIENS_VS_COWS_API AC_AlienShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AC_AlienShip();

// Components
protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UBoxComponent> AlienShipCollision;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> AlienShipMesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<USphereComponent> AlienShipCollectionRadiusCollision;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UNiagaraComponent> AlienShipCollectionRadiusEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<USpotLightComponent> AlienShipCollectionRadiusLight;

// Variables
	UPROPERTY(BlueprintReadWrite, Category = "Config", EditDefaultsOnly)
	bool RotateToCameraDirection = true;
	
	UPROPERTY(BlueprintReadWrite, Category = "Debug", EditAnywhere)
	TEnumAsByte<EDrawDebugTrace::Type> DebugConfig = EDrawDebugTrace::None;

public:
	FOnCollectCow OnCollectCow;
	
	UPROPERTY(BlueprintReadOnly, Category = "Info")
	int CowsCollected;
	
// Functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnAlienShipCollectionSphereBeginOverlap
	(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
