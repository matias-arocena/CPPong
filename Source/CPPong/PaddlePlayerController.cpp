// Fill out your copyright notice in the Description page of Project Settings.
#include "PaddlePlayerController.h"

#include "Camera/CameraActor.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

APaddlePlayerController::APaddlePlayerController()
{

}

void APaddlePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnableInput(this);

	InputComponent->BindAxis("Move", this, &APaddlePlayerController::Move);
	InputComponent->BindAction("Start", IE_Pressed, this, &APaddlePlayerController::Start);
}

void APaddlePlayerController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);

	SetViewTarget(CameraActors[0]);

	Paddle = Cast<APlayerPaddle>(GetPawn());
	
	SpawnNewBall();

	TArray<AActor*> EnemyActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyPaddle::StaticClass(), EnemyActor);

	Enemy = Cast<AEnemyPaddle>(EnemyActor[0]);
	Enemy->SetBall(Ball);
}

void APaddlePlayerController::Move(float value)
{
	if (Paddle) {
		Paddle->Move(value);
	}
}

void APaddlePlayerController::Start()
{
	Ball->Start();
}

void APaddlePlayerController::SpawnNewBall()
{
	if (BallObj) {
		Ball = GetWorld()->SpawnActor<ABall>(BallObj, FVector(0.0f, 0.0f, 20.0f), FRotator(0.0f, 0.0f, 0.0f));
	}
}
