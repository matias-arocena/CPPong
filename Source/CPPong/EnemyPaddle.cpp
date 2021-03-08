// Fill out your copyright notice in the Description page of Project Settings.
#include "EnemyPaddle.h"

// Sets default values
AEnemyPaddle::AEnemyPaddle()
{
	bIsCollidingAbove = false;
	bIsCollidingBelow = false;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_EnemyPaddle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyPaddle"));
	
	SM_EnemyPaddle->SetEnableGravity(false);
	SM_EnemyPaddle->SetConstraintMode(EDOFMode::XYPlane);
	SM_EnemyPaddle->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_EnemyPaddle->SetCollisionProfileName(TEXT("PhysicsActor"));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	RootComponent = BoxCollision;
	
	SM_EnemyPaddle->AttachTo(RootComponent);
}

void AEnemyPaddle::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Enemy Hit: %s"), *OtherActor->GetName()));
	}

	if (OtherActor->ActorHasTag("Above")) {
		bIsCollidingAbove = true;
	}
	else if (OtherActor->ActorHasTag("Below")) {
		bIsCollidingBelow = true;
	}
}

void AEnemyPaddle::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Above")) {
		bIsCollidingAbove = false;
	}
	else if (OtherActor->ActorHasTag("Below")) {
		bIsCollidingBelow = false;
	}
}

// Called when the game starts or when spawned
void AEnemyPaddle::BeginPlay()
{
	Super::BeginPlay();
	X = GetActorLocation().X;
	Z = GetActorLocation().Z;

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyPaddle::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AEnemyPaddle::OnOverlapEnd);
}

// Called every frame
void AEnemyPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float ballY = Ball->GetY();
	float thisY = GetActorLocation().Y;

	//Stop moving if it collides with the wall
	float result = (ballY - thisY) * (ballY > thisY) * !bIsCollidingAbove +
		(ballY - thisY) * (ballY <= thisY) * !bIsCollidingBelow;

	SetActorLocation(FVector(X, thisY + (result/std::abs(result)) * Speed * DeltaTime, Z));
}


void AEnemyPaddle::SetBall(ABall* TheBall) {
	this->Ball = TheBall;
}