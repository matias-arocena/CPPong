// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPaddle.h"

// Sets default values
APlayerPaddle::APlayerPaddle()
{
	bIsCollidingBelow = false;
	bIsCollidingAbove = false;

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SM_PlayerPaddle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_PlayerPaddle"));
	RootComponent = SM_PlayerPaddle;

	SM_PlayerPaddle->SetEnableGravity(false);
	SM_PlayerPaddle->SetConstraintMode(EDOFMode::SixDOF);
	SM_PlayerPaddle->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_PlayerPaddle->SetCollisionProfileName(TEXT("PhysicsActor"));

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));

	SM_PlayerPaddle->OnComponentBeginOverlap.AddDynamic(this, &APlayerPaddle::OnOverlapBegin);
	SM_PlayerPaddle->OnComponentEndOverlap.AddDynamic(this, &APlayerPaddle::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APlayerPaddle::BeginPlay()
{
	Super::BeginPlay();
	this->XPos = GetActorLocation().X;
	this->ZPos = GetActorLocation().Z;
}

// Called every frame
void APlayerPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float YPos = GetActorLocation().Y;
	//Stop moving if it collides with the wall
	float velocity = (YVelocity > 0) * !bIsCollidingAbove + (YVelocity < 0) * !bIsCollidingBelow * -1;
	SetActorLocation(FVector(XPos, YPos + velocity * 100.0f * DeltaTime , ZPos));
}
// Called to bind functionality to input
void APlayerPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPaddle::Move(float value)
{
	YVelocity = value;
}

void APlayerPaddle::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
	}

	if (OtherActor->ActorHasTag("Above")) {
		bIsCollidingAbove = true;
	}
	else if (OtherActor->ActorHasTag("Below")) {
		bIsCollidingBelow = true;
	}
}

void APlayerPaddle::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Above")) {
		bIsCollidingAbove = false;
	}
	else if (OtherActor->ActorHasTag("Below")) {
		bIsCollidingBelow = false;
	}
}