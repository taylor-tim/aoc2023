// Fill out your copyright notice in the Description page of Project Settings.


#include "Solution01.h"

#include "Kismet/KismetStringLibrary.h"
#include "Logging/StructuredLog.h"


// Sets default values
ASolution01::ASolution01()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASolution01::BeginPlay()
{
	Super::BeginPlay();
	
}

FString ASolution01::SolveTest()
{
	return TEXT("Solution 1 Part One Answer!");
}

FString ASolution01::SolvePartOne()
{
	const int Total = AddUpLines(PuzzleOneData);
	return FString::Printf(TEXT("%i"), Total);
}

FString ASolution01::SolvePartTwo()
{
	TArray<FString> NewArray;
	
	for (FString Line : PuzzleOneData)
	{
		UE_LOGFMT(LogTemp, Warning, "Old line: '{Line}'", Line);
		Line.ReplaceInline(TEXT("nine"), TEXT("ni9ne"));
		Line.ReplaceInline(TEXT("eight"), TEXT("eig8ht"));
		Line.ReplaceInline(TEXT("seven"), TEXT("sev7en"));
		Line.ReplaceInline(TEXT("six"), TEXT("s6ix"));
		Line.ReplaceInline(TEXT("five"), TEXT("fi5ve"));
		Line.ReplaceInline(TEXT("four"), TEXT("fo4ur"));
		Line.ReplaceInline(TEXT("three"), TEXT("thr3ee"));
		Line.ReplaceInline(TEXT("two"), TEXT("tw2o"));
		Line.ReplaceInline(TEXT("one"), TEXT("o1ne"));
		UE_LOGFMT(LogTemp, Warning, "New line: '{Line}'", Line);
		NewArray.Add(Line);
	}
	const int Total = AddUpLines(NewArray);
	return FString::Printf(TEXT("%i"), Total);
}

int ASolution01::AddUpLines(TArray<FString> &InData)
{
	int Total = 0;
	const FString Nums = "1234567890";
	for (FString Line : InData)
	{
		TArray<int> FoundNums;
		for (auto Char : Line)
		{
			FString ThisChar(&Char);
			if (Nums.Contains(ThisChar))
			{
				FoundNums.Add(UKismetStringLibrary::Conv_StringToInt(ThisChar));
			}
		}
		if (FoundNums.Num() == 1)
		{
			Total += FoundNums[0] * 10 + FoundNums[0];
		}
		else
		{
			const int LastIndex = FoundNums.Num() - 1;
			Total += FoundNums[0] * 10 + FoundNums[LastIndex];
		}
	}
	return Total;
}

// Called every frame
void ASolution01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASolution01::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

