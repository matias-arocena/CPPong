// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ball.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerPaddle.h"
#include "PaddlePlayerController.generated.h"
/**
 * 
 */

UCLASS()
class CPPONG_API APaddlePlayerController : public APlayerController
{
	GENERATED_BODY()

	APaddlePlayerController();

	UFUNCTION()
		virtual void SetupInputComponent() override;
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABall> BallObj;

private:
	APlayerPaddle* Paddle;
	ABall* Ball;

protected:
	virtual void BeginPlay() override;

public:
	void Move(float value);
	void Start();
	void SpawnNewBall();
};
