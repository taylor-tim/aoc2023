// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetStringLibrary.h"
#include "Logging/StructuredLog.h"
#include "FileReader.generated.h"

/**
 * 
 */
UCLASS()
class AOC2023_API UFileReader final : public UObject
{
	GENERATED_BODY()

public:
	static FString ReadFromFile(FString FilePath) {
		FString Result = TEXT("");
		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
		{
			UE_LOGFMT(LogTemp, Error, "Couldn't find path to read file: {File}", FilePath);
			return Result;
		}
		FFileHelper::LoadFileToString(Result, *FilePath);

		return Result;
	}

	static TArray<FString> SplitStringOnNewLines(FString Stringer)
	{
		TArray<FString> Result;
		Stringer.ParseIntoArray(Result, TEXT("\r\n"), true);
		return Result;
	}

	static bool FileIsEmpty(FString FilePath)
	{
		return false;
	}

	UFUNCTION(BlueprintCallable)
	static FString GetPuzzleDataFilePath(int Day)
	{
		FString DayString = UKismetStringLibrary::Conv_IntToString(Day);
		if (DayString.Len() == 1)
		{
			DayString = FString::Printf(TEXT("0%s"), *DayString);
		}
		FString SolutionFolder = FString::Printf(TEXT("Solution%s"), *DayString);
		FString ProjectSource = TEXT("D:/unreals/recheck/aoc2023/Source/AoC2023/Solvers");
		const FString FilePathOne = FString::Printf(TEXT("%s/%s/PuzzleOneData.txt"), *ProjectSource, *SolutionFolder);
		return FilePathOne;
	}
	
	UFUNCTION(BlueprintCallable)
	static void SaveStringToFile(FString Content, FString FilePath)
	{
		UE_LOGFMT(LogTemp, Warning, "Got content to save: {Cont}", Content);
		FFileHelper::SaveStringToFile(Content, *FilePath);
	}
};
