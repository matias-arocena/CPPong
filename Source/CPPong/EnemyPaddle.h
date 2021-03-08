// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "Ball.h"
#include "GameFramework/Actor.h"
#include "EnemyPaddle.generated.h"

UCLASS()
class CPPONG_API AEnemyPaddle : public AActor
{
	GENERATED_BODY()
private:
	ABall* Ball;
	float X;
	float Z;
	bool bIsCollidingAbove;
	bool bIsCollidingBelow;

public:	
	// Sets default values for this actor's properties
	AEnemyPaddle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_EnemyPaddle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere)
		float Speed;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetBall(ABall* TheBall);

};
