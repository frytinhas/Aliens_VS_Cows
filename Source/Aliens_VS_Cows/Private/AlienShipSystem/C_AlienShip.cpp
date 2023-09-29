// Fill out your copyright notice in the Description page of Project Settings.

#include "Aliens_VS_Cows/Public/AlienShipSystem/C_AlienShip.h"
#include "Aliens_VS_Cows/Public/CowSystem/C_Cow.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SpotLightComponent.h"

// Sets default values
AC_AlienShip::AC_AlienShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/* Has code in Event Tick! */

	// Create Alien ship collision
	AlienShipCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Alien Ship Box Collision"));

	// Create Alien ship mesh
	AlienShipMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Alien Ship Mesh"));
	AlienShipMesh->SetupAttachment(AlienShipCollision);

	// Declare collision, it's very important component!
	AlienShipCollectionRadiusCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collection Collision"));
	AlienShipCollectionRadiusCollision->SetupAttachment(AlienShipCollision);

	// Niagara effect, to tell the player where the collision is.
	AlienShipCollectionRadiusEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Collection Radius Effect"));
	AlienShipCollectionRadiusEffect->SetupAttachment(AlienShipCollectionRadiusCollision);

	// Light effect, just cosmetic
	AlienShipCollectionRadiusLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Collection Light"));
	AlienShipCollectionRadiusLight->SetupAttachment(AlienShipCollision);
}

// Called when the game starts or when spawned
void AC_AlienShip::BeginPlay()
{
	Super::BeginPlay();
	AlienShipCollectionRadiusCollision->OnComponentBeginOverlap.AddDynamic(this, &AC_AlienShip::OnAlienShipCollectionSphereBeginOverlap);
}

void AC_AlienShip::OnAlienShipCollectionSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//? Verify if hit a cow
	if (AC_Cow* CowRef = Cast<AC_Cow>(OtherActor))
	{
		// Destroy cow and add to cows collected variable
		CowRef->Destroy();
		CowsCollected++;

		// Call OnCollectCow to warning game mode and others things
		OnCollectCow.Execute();
	}
}

// Called every frame
void AC_AlienShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get collision locate by line trace
	FHitResult LineTraceResult;
	const TArray<AActor*> ActorsToIgnore;
	UKismetSystemLibrary::LineTraceSingle(this, GetActorLocation(), GetActorLocation() + GetActorUpVector() * -10000.f, TraceTypeQuery1,
		false, ActorsToIgnore, DebugConfig, LineTraceResult, true);

	// Apply collision location by line trace result
	AlienShipCollectionRadiusCollision->SetWorldLocation(LineTraceResult.ImpactPoint + LineTraceResult.ImpactNormal);

	// Just cosmetic.
	if (RotateToCameraDirection && IsPlayerControlled())
	{
		AlienShipMesh->SetWorldRotation(FRotator(0.f, GetControlRotation().Yaw, 0.f));
	}
}

