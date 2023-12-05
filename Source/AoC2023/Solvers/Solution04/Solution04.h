// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AoC2023/Solvers/SolverBase.h"
#include "Solution04.generated.h"

UCLASS()
class AOC2023_API ASolution04 : public ASolverBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASolution04();
	virtual FString SolveTestOne() override;
	virtual FString SolveTestTwo() override;
	virtual FString SolvePartOne() override;
	virtual FString SolvePartTwo() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void ParseLines(TArray<FString>& InData);
	int ProcessPartOneLines(TArray<FString> &InLines);
	int ProcessPartTwoLines(TArray<FString> &InLines);
	void LineToTwoArrays(FString Line, TArray<int> &LeftNums, TArray<int> &RightNums);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
