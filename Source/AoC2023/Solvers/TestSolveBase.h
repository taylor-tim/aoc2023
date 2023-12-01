// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SolverBase.h"
#include "TestSolveBase.generated.h"

UCLASS()
class AOC2023_API ATestSolveBase : public ASolverBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestSolveBase();

	virtual FString SolveTest() override;
	virtual FString SolvePartOne() override;
	virtual FString SolvePartTwo() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual bool IsTestDataRight() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
