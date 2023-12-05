// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PartNumber.h"
#include "AoC2023/Solvers/SolverBase.h"
#include "Solution03.generated.h"

UCLASS()
class AOC2023_API ASolution03 : public ASolverBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASolution03();
	virtual FString SolveTestOne() override;
	virtual FString SolveTestTwo() override;
	virtual FString SolvePartOne() override;
	virtual FString SolvePartTwo() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	static bool IsNum(const FString& InString);
	UPROPERTY()
	TArray<FPartNumber> PartNumbers;
	
	UPROPERTY()
	TArray<FVector> SymbolLocs;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ParseLines(TArray<FString>& InData);
};
