// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPaddle.h"

// Sets default values
APlayerPaddle::APlayerPaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SM_PlayerPaddle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_PlayerPaddle"));
	RootComponent = SM_PlayerPaddle;

	SM_PlayerPaddle->SetEnableGravity(false);
	SM_PlayerPaddle->SetConstraintMode(EDOFMode::XYPlane);
	SM_PlayerPaddle->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_PlayerPaddle->SetCollisionProfileName(TEXT("PhysicsActor"));

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
}

// Called when the game starts or when spawned
void APlayerPaddle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPaddle::Move(float value)
{
	AddMovementInput(FVector(0.f, value, 0.0f));
}
