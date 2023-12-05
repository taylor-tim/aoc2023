// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProblemGetter.generated.h"


UCLASS()
class AOC2023_API AProblemGetter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProblemGetter();

	void LoginToAoC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DownloadPuzzleData(int Day);

	UPROPERTY()
	FString BaseUrl = TEXT("https://adventofcode.com/2023/day/");
	
	UPROPERTY()
	FString InputUrl = TEXT("/input");

	UPROPERTY()
	FString ProjectSource = TEXT("D:/unreals/recheck/aoc2023/Source/AoC2023/Solvers");
};
