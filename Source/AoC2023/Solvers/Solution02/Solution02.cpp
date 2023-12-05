// Fill out your copyright notice in the Description page of Project Settings.


#include "Solution02.h"

#include "UCubeGame.h"


// Sets default values
ASolution02::ASolution02()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SolutionFolder = TEXT("Solution02");
}

FString ASolution02::SolveTestOne()
{
	FString Answer = TEXT("");

	int ValidCount = 0;
	for (FString Line : PuzzleOneData)
	{
		UCubeGame* ThisGame = NewObject<UCubeGame>(UCubeGame::StaticClass());
		ThisGame->LoadGameFromString(Line);
		ValidCount += ThisGame->CheckGame() ? 1 : 0;
	}
	return FString::Printf(TEXT("%i"), ValidCount);
}

FString ASolution02::SolveTestTwo()
{
	return Super::SolveTestTwo();
}

FString ASolution02::SolvePartOne()
{
	FString Answer = TEXT("");

	int ValidCount = 0;
	for (FString Line : PuzzleOneData)
	{
		UCubeGame* ThisGame = NewObject<UCubeGame>(UCubeGame::StaticClass());
		ThisGame->LoadGameFromString(Line);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Line);
		ThisGame->DescribeGame();
		if (ThisGame->CheckGame())
		{
			ValidCount += ThisGame->GetGameId();
			UE_LOG(LogTemp, Warning, TEXT("Valid count now %i"), ValidCount);
		}
	}
	return FString::Printf(TEXT("%i"), ValidCount);
}

FString ASolution02::SolvePartTwo()
{
	int TotalSum = 0;
	for (const FString Line : PuzzleOneData)
	{
		UCubeGame* ThisGame = NewObject<UCubeGame>(UCubeGame::StaticClass());
		ThisGame->LoadGameFromString(Line);
		TotalSum += ThisGame->CheckGamePartB();
	}
	return FString::Printf(TEXT("%i"), TotalSum);
}

// Called when the game starts or when spawned
void ASolution02::BeginPlay()
{
	Super::BeginPlay();
	ReadDataFiles();
}

// Called every frame
void ASolution02::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASolution02::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

