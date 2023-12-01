// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSolveBase.h"


// Sets default values
ATestSolveBase::ATestSolveBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

FString ATestSolveBase::SolveTest()
{
	return Super::SolveTest();
}

FString ATestSolveBase::SolvePartOne()
{
	return Super::SolvePartOne();
}

FString ATestSolveBase::SolvePartTwo()
{
	return Super::SolvePartTwo();
}

// Called when the game starts or when spawned
void ATestSolveBase::BeginPlay()
{
	Super::BeginPlay();
}

bool ATestSolveBase::IsTestDataRight()
{
	return true;
}

// Called every frame
void ATestSolveBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATestSolveBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

