// Fill out your copyright notice in the Description page of Project Settings.

#include "Ball.h"

// Sets default values
ABall::ABall()
{
	PlayerScore = 0;
	EnemyScore = 0;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsGameStarted = false;

	SM_Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	RootComponent = SM_Ball;

	SM_Ball->SetSimulatePhysics(true);
	SM_Ball->SetEnableGravity(false);
	SM_Ball->SetConstraintMode(EDOFMode::XYPlane);
	SM_Ball->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Ball->SetNotifyRigidBodyCollision(true);
	SM_Ball->SetCollisionProfileName(TEXT("PhysicsActor"));
	SM_Ball->OnComponentHit.AddDynamic(this, &ABall::OnCompHit);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1.1f;
	ProjectileMovement->Friction = 0.0f;
	ProjectileMovement->Velocity.Z = 0.0f;
}

void ABall::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
	}
	if (OtherActor->ActorHasTag("EnemyGoal")) {
		EnemyScore++;
		bIsGameStarted = false;
		HitComp->SetPhysicsLinearVelocity(FVector(0, 0, 0));
		SetActorLocation(FVector(0, 0, 0));
	}

	if (OtherActor->ActorHasTag("PlayerGoal")) {
		PlayerScore++;
		bIsGameStarted = false;
		HitComp->SetPhysicsLinearVelocity(FVector(0, 0, 0));
		SetActorLocation(FVector(0, 0, 0));
	}
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SM_Ball->SetPhysicsLinearVelocity(GetVelocity().GetSafeNormal() * Speed * DeltaTime * bIsGameStarted * 500.0f);
	//ProjectileMovement->Velocity = ProjectileMovement->Velocity.GetSafeNormal() * Speed * DeltaTime;
	//ProjectileMovement->UpdateComponentVelocity();
}

void ABall::Start()
{
	if (!bIsGameStarted) {
		SM_Ball->SetPhysicsLinearVelocity(FVector(3.0f, 1.0f, 0.0f));
		bIsGameStarted = true;
	} 
}

UStaticMeshComponent* ABall::GetBall()
{
	return SM_Ball;
}

float ABall::GetY() 
{
	return SM_Ball->GetComponentLocation().Y;
}

