// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SolveTypes.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "SolverBase.generated.h"

UCLASS()
class AOC2023_API ASolverBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASolverBase();

	UFUNCTION()
	void SetPuzzleData(FString InData) {PuzzleData = InData; }
	
	UFUNCTION()
	void SetTestPuzzleData(FString InData) {PuzzleData = InData; }

	UFUNCTION()
	virtual bool IsTestDataRight();

	UFUNCTION(BlueprintCallable)
	void HandleSolve(ESolveTypes SolveTypes);
	
	UFUNCTION(BlueprintCallable)
	virtual FString SolvePartOne();

	UFUNCTION(BlueprintCallable)
	virtual FString SolvePartTwo();

	UFUNCTION(BlueprintCallable)
	virtual FString SolveTestOne();
	
	UFUNCTION(BlueprintCallable)
	virtual FString SolveTestTwo();
	
	UFUNCTION(BlueprintCallable)
	void ReadTestOneData();
	
	UFUNCTION(BlueprintCallable)
	void ReadTestTwoData();
	
	UFUNCTION(BlueprintCallable)
	void ReadPuzzleOneData();
	
	UFUNCTION(BlueprintCallable)
	void ReadPuzzleTwoData();
	
	UFUNCTION()
	void ReadDataFiles();
	
	UFUNCTION(BlueprintCallable)
	void DownloadPuzzleInfo();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ParsePuzzleData();

	UPROPERTY()
	FString SolutionFolder = TEXT("");
	
	UPROPERTY()
	int SolutionNumber = 0;
	
	UPROPERTY()
	FString ProjectSource = TEXT("D:/unreals/recheck/aoc2023/Source/AoC2023/Solvers");
	
	UPROPERTY()
	FString PuzzleData = "";

	UPROPERTY()
	FString TestPuzzleData = "";

	UPROPERTY(EditAnywhere)
	UBoxComponent* OverlapArea;

	UPROPERTY()
	TArray<FString> TestOneData;

	UPROPERTY()
	TArray<FString> TestTwoData;

	UPROPERTY()
	TArray<FString> PuzzleOneData;

	UPROPERTY()
	TArray<FString> PuzzleTwoData;

	UPROPERTY()
	FString AocCookie = TEXT("");
	
	UPROPERTY()
    FString AoCBaseUrl = TEXT("https://adventofcode.com/2023/day");

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
