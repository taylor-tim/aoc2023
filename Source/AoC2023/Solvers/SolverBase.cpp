// Fill out your copyright notice in the Description page of Project Settings.


#include "SolverBase.h"

#include "AoC2023/GameMode/SolverGameMode.h"
#include "AoC2023/Interfaces/SolveStationInterface.h"


// Sets default values
ASolverBase::ASolverBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OverlapArea = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapArea!"));
	FVector BoxExtent = FVector3d::Zero();
	BoxExtent.X = 128;
	BoxExtent.Y = 64;
	BoxExtent.Z = 64;
	OverlapArea->SetBoxExtent(BoxExtent);
}

bool ASolverBase::IsTestDataRight()
{
	return false;
}

void ASolverBase::HandleSolve(ESolveTypes SolveTypes)
{
	const ASolverGameMode* SolverGameMode = Cast<ASolverGameMode>(GetWorld()->GetAuthGameMode());
	if (SolverGameMode != nullptr)
	{
		SolverGameMode->OnBeginSolve.Broadcast();
	}
	FString Answer = TEXT("Nothing Solved");
	switch (SolveTypes)
	{
	case ESolveTypes::TestData:
		Answer = SolveTest();
		break;
	case ESolveTypes::PartOne:
		Answer = SolvePartOne();
		break;
	case ESolveTypes::PartTwo:
		Answer = SolvePartTwo();
		break;
	default:
		break;
	}
	if (SolverGameMode != nullptr)
	{
		SolverGameMode->OnFinishSolve.Broadcast(Answer);
	}
}

FString ASolverBase::SolvePartOne()
{
	return TEXT("Part One Solved Base");
}

FString ASolverBase::SolvePartTwo()
{
	return TEXT("Part Two Solved Base");
}

FString ASolverBase::SolveTest()
{
	return TEXT("Test Data Solved Base");
}

// Called when the game starts or when spawned
void ASolverBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASolverBase::ParsePuzzleData()
{
}

// Called every frame
void ASolverBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

