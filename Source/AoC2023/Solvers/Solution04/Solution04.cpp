// Fill out your copyright notice in the Description page of Project Settings.


#include "Solution04.h"

#include "Kismet/KismetStringLibrary.h"
#include "Logging/StructuredLog.h"


// Sets default values
ASolution04::ASolution04()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

FString ASolution04::SolveTestOne()
{
	ReadTestOneData();
	const int TotalValue = ProcessPartOneLines(TestOneData);
	return FString::Printf(TEXT("%i"), TotalValue);
}

FString ASolution04::SolveTestTwo()
{
	ReadTestOneData();
	const int TotalValue = ProcessPartTwoLines(TestOneData);
	return FString::Printf(TEXT("%i"), TotalValue);
}

FString ASolution04::SolvePartOne()
{
	ReadPuzzleOneData();
	const int TotalValue = ProcessPartOneLines(PuzzleOneData);
	return FString::Printf(TEXT("%i"), TotalValue);
}

FString ASolution04::SolvePartTwo()
{
	ReadPuzzleOneData();
	int TotalValue = ProcessPartTwoLines(PuzzleOneData);
	return FString::Printf(TEXT("%i"), TotalValue);
}

// Called when the game starts or when spawned
void ASolution04::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASolution04::ParseLines(TArray<FString>& InData)
{
}

int ASolution04::ProcessPartOneLines(TArray<FString>& InLines)
{
	int TotalValue = 0;
	for (FString Line : InLines)
	{
		TArray<int> LeftNums;
		TArray<int> RightNums;
		LineToTwoArrays(Line, LeftNums, RightNums);
		int LineTotal = 0;
		for (int ThisInt : RightNums)
		{
			if (LeftNums.Contains(ThisInt))
			{
				if (LineTotal == 0)
				{
					LineTotal = 1;
				}
				else
				{
					LineTotal *= 2;
				}
			}
		}
		UE_LOGFMT(LogTemp, Warning, "Line worth {Points}", LineTotal);
		TotalValue += LineTotal;
	}
	return TotalValue;
}

int ASolution04::ProcessPartTwoLines(TArray<FString>& InLines)
{
	int TotalValue = 0;
	TMap<int, int> CardTotals;
	for (int i = 1; i <= InLines.Num(); i++)
	{
		CardTotals.Add(i, 1);
	}

	for (int i = 1; i <= InLines.Num(); i++)
	{
		const FString Line = InLines[i - 1];
		TArray<int> LeftNums;
		TArray<int> RightNums;
		LineToTwoArrays(Line, LeftNums, RightNums);

		int MatchCount = 0;
		for (int ThisInt : RightNums)
		{
			if (LeftNums.Contains(ThisInt))
			{
				MatchCount++;
			}
		}
		if (MatchCount > 0)
		{
			for (int k = 1; k <= CardTotals[i]; k++)
			{
				for (int j = 1; j <= MatchCount; j++)
				{
					int ThisIndex = i + j;
					if (CardTotals.Contains(ThisIndex))
					{
						CardTotals[ThisIndex] = CardTotals[ThisIndex] + 1;
					}
				}
			}
		}
	}
	for (auto Pair : CardTotals)
	{
		TotalValue += Pair.Value;
	}
	return TotalValue;
}

// Called every frame
void ASolution04::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASolution04::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASolution04::LineToTwoArrays(FString Line, TArray<int> &LeftNums, TArray<int> &RightNums)
{
	FString LeftNumString;
	FString RightNumString;
	Line.Split(TEXT(" | "), &LeftNumString, &RightNumString);
	const int ColonIndex = LeftNumString.Find(TEXT(":"));
	LeftNumString.RightChopInline(ColonIndex + 2);

	while (LeftNumString.Len() > 0)
	{
		FString RemainderStr;
		FString ThisNumStr;
		LeftNumString = LeftNumString.TrimStart();
		
		if (LeftNumString.Contains(TEXT(" ")))
		{
			LeftNumString = LeftNumString.TrimStart();
			LeftNumString.Split(TEXT(" "), &ThisNumStr, &RemainderStr);
		}
		else
		{
			ThisNumStr = LeftNumString;
		}
		LeftNums.Add(UKismetStringLibrary::Conv_StringToInt(ThisNumStr));
		LeftNumString = RemainderStr;
	}

	while (RightNumString.Len() > 0)
	{
		FString RemainderStr;
		FString ThisNumStr;
		RightNumString = RightNumString.TrimStart();
		
		if (RightNumString.Contains(TEXT(" ")))
		{
			RightNumString = RightNumString.TrimStart();
			RightNumString.Split(TEXT(" "), &ThisNumStr, &RemainderStr);
		}
		else
		{
			ThisNumStr = RightNumString;
		}
		RightNums.Add(UKismetStringLibrary::Conv_StringToInt(ThisNumStr));
		RightNumString = RemainderStr;
	}
}

