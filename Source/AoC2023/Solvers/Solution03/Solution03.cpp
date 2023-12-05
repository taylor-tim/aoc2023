// Fill out your copyright notice in the Description page of Project Settings.


#include "Solution03.h"

#include "Kismet/KismetStringLibrary.h"
#include "Logging/StructuredLog.h"


// Sets default values
ASolution03::ASolution03()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SolutionFolder = TEXT("Solution03");
}

// Called every frame
void ASolution03::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASolution03::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

FString ASolution03::SolveTestOne()
{
	ReadTestOneData();
	ParseLines(TestOneData);
	int TotalValue = 0;
	for (FPartNumber ThisPart : PartNumbers)
	{
		TArray<FVector> ToCheck;
		bool bIsValidPart = false;
		for (const FVector ThisVector : ThisPart.NumberVectors)
		{
			ToCheck.Add(FVector(ThisVector.X, ThisVector.Y - 1, 0));
			ToCheck.Add(FVector(ThisVector.X, ThisVector.Y + 1, 0));
			ToCheck.Add(FVector(ThisVector.X - 1, ThisVector.Y - 1, 0));
			ToCheck.Add(FVector(ThisVector.X - 1, ThisVector.Y, 0));
			ToCheck.Add(FVector(ThisVector.X - 1, ThisVector.Y + 1, 0));
			ToCheck.Add(FVector(ThisVector.X + 1, ThisVector.Y - 1, 0));
			ToCheck.Add(FVector(ThisVector.X + 1, ThisVector.Y, 0));
			ToCheck.Add(FVector(ThisVector.X + 1, ThisVector.Y + 1, 0));
			for (FVector ThisSubVector : ToCheck)
			{
				if (SymbolLocs.Contains(ThisSubVector))
				{
					bIsValidPart = true;
					break;
				}
			}
			if (bIsValidPart)
			{
				TotalValue += ThisPart.Number;
				break;
			}
		}
	}
	return FString::Printf(TEXT("%i"), TotalValue);
}

FString ASolution03::SolveTestTwo()
{
	return Super::SolveTestTwo();
}

FString ASolution03::SolvePartOne()
{
	ReadPuzzleOneData();
	ParseLines(PuzzleOneData);
	int TotalValue = 0;
	for (FPartNumber ThisPart : PartNumbers)
	{
		TArray<FVector> ToCheck;
		bool bIsValidPart = false;
		for (const FVector ThisVector : ThisPart.NumberVectors)
		{
			ToCheck.Add(FVector(ThisVector.X - 1, ThisVector.Y - 1, 0));
			ToCheck.Add(FVector(ThisVector.X, ThisVector.Y - 1, 0));
			ToCheck.Add(FVector(ThisVector.X + 1, ThisVector.Y - 1, 0));
			ToCheck.Add(FVector(ThisVector.X - 1, ThisVector.Y, 0));
			ToCheck.Add(FVector(ThisVector.X + 1, ThisVector.Y, 0));
			ToCheck.Add(FVector(ThisVector.X - 1, ThisVector.Y + 1, 0));
			ToCheck.Add(FVector(ThisVector.X, ThisVector.Y + 1, 0));
			ToCheck.Add(FVector(ThisVector.X + 1, ThisVector.Y + 1, 0));
			for (FVector ThisSubVector : ToCheck)
			{
				if (SymbolLocs.Contains(ThisSubVector))
				{
					bIsValidPart = true;
					break;
				}
			}
			if (bIsValidPart)
			{
				UE_LOGFMT(LogTemp, Warning, "{Num} is valid, Total {Pre} -> {Post}", ThisPart.Number, TotalValue, TotalValue + ThisPart.Number);
				TotalValue += ThisPart.Number;
				break;
			}
		}
	}
	return FString::Printf(TEXT("%i"), TotalValue);
}

// Called when the game starts or when spawned
void ASolution03::BeginPlay()
{
	Super::BeginPlay();
	
}

FString ASolution03::SolvePartTwo()
{
	ReadPuzzleOneData();
	ParseLines(PuzzleOneData);
	
	int TotalValue = 0;
	int YValue = 0;
	
	for (FString Line : PuzzleOneData)
	{
		int XValue = 0;
		for (auto ThisChar : Line)
		{
			FString ThisString(&ThisChar);
			if (ThisString.Compare(TEXT("*")) == 0)
			{
				FVector ThisVector = FVector(XValue, YValue, 0);
				TArray<int> NumNeighbors;
				for (FPartNumber ThisPart : PartNumbers)
				{
					if (ThisPart.IsAdjacentTo(ThisVector))
					{
						NumNeighbors.Add(ThisPart.Number);
					}
				}
				if (NumNeighbors.Num() == 2)
				{
					TotalValue += NumNeighbors[0] * NumNeighbors[1];
				}
			}
			XValue++;
		}
		YValue++;
	}
	
	return FString::Printf(TEXT("%i"), TotalValue);
}
	
void ASolution03::ParseLines(TArray<FString> &Lines)
{
	PartNumbers.Empty();
	SymbolLocs.Empty();
	int YValue = 0;
	const FString NumChar = TEXT("1234567890");
	
	for (FString Line : Lines)
	{
		int XValue = 0;
		TArray<FVector> CurrentNumbers;
		FString NumString = TEXT("");
		bool CurrentlyParsingInt = false;
		const int LastIndex = Line.Len();
		
		for (auto ThisChar : Line)
		{
			FString ThisString(&ThisChar);
			if (NumChar.Contains(ThisString))
			{
				if (!CurrentlyParsingInt)
				{
					CurrentNumbers.Empty();
					NumString = TEXT("");
					CurrentlyParsingInt = true;
				}
				CurrentNumbers.Add(FVector(XValue, YValue, 0));
				NumString += ThisString;
			}
			else
			{
				if (CurrentlyParsingInt)
				{
					FPartNumber ThisPart;
					ThisPart.NumberVectors = CurrentNumbers;
					ThisPart.Number = UKismetStringLibrary::Conv_StringToInt(NumString);
					PartNumbers.Add(ThisPart);
					
					CurrentNumbers.Empty();
					NumString = TEXT("");
					CurrentlyParsingInt = false;
				}
				if (ThisString.Compare(TEXT(".")) != 0)
				{
					SymbolLocs.Add(FVector(XValue, YValue, 0));
					CurrentlyParsingInt = false;
				}
				else
				{
					CurrentlyParsingInt = false;
				}
			}
			XValue++;
			if (XValue == LastIndex && CurrentlyParsingInt)
			{
				FPartNumber ThisPart;
					ThisPart.NumberVectors = CurrentNumbers;
					ThisPart.Number = UKismetStringLibrary::Conv_StringToInt(NumString);
					PartNumbers.Add(ThisPart);
			}
		}
		YValue++;
	}
}

bool ASolution03::IsNum(const FString& InString)
{
	const FString NumChar = TEXT("1234567890");
	return NumChar.Contains(InString);
}


