// Fill out your copyright notice in the Description page of Project Settings.


#include "SolverBase.h"

#include "AoC2023/GameMode/SolverGameMode.h"
#include "AoC2023/Statics/FileReader.h"
#include "AoC2023/Statics/HttpHelper.h"
#include "Kismet/KismetStringLibrary.h"


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
	case ESolveTypes::TestDataOne:
		Answer = SolveTestOne();
		break;
	case ESolveTypes::TestDataTwo:
		Answer = SolveTestTwo();
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

FString ASolverBase::SolveTestOne()
{
	return TEXT("Test Data Solved One Base");
}

FString ASolverBase::SolveTestTwo()
{
	return TEXT("Test Data Solved Two Base");
}

void ASolverBase::ReadTestOneData()
{
	FString FilePath = FString::Printf(TEXT("%s/%s/TestOneData.txt"), *ProjectSource, *SolutionFolder);
	FString Result = UFileReader::ReadFromFile(FilePath);
	TestOneData = UFileReader::SplitStringOnNewLines(Result);
}

void ASolverBase::ReadTestTwoData()
{
	FString FilePath = FString::Printf(TEXT("%s/%s/TestTwoData.txt"), *ProjectSource, *SolutionFolder);
	FString Result = UFileReader::ReadFromFile(FilePath);
	TestTwoData = UFileReader::SplitStringOnNewLines(Result);
}

void ASolverBase::ReadPuzzleOneData()
{
	FString FilePath = FString::Printf(TEXT("%s/%s/PuzzleOneData.txt"), *ProjectSource, *SolutionFolder);
	FString Result = UFileReader::ReadFromFile(FilePath);
	PuzzleOneData = UFileReader::SplitStringOnNewLines(Result);
}

void ASolverBase::ReadPuzzleTwoData()
{
	FString FilePath = FString::Printf(TEXT("%s/%s/PuzzleTwoData.txt"), *ProjectSource, *SolutionFolder);
	FString Result = UFileReader::ReadFromFile(FilePath);
	PuzzleTwoData = UFileReader::SplitStringOnNewLines(Result);
}

void ASolverBase::ReadDataFiles()
{
	TArray<FString> TheseStrings;
	FString FilePath = FString::Printf(TEXT("%s/%s/PuzzleOneData.txt"), *ProjectSource, *SolutionFolder);
	FFileHelper::LoadFileToStringArray(TheseStrings, *FilePath);
	if (TheseStrings.Num() == 0)
	{
		//DownloadPuzzleInfo();
	}
	ReadTestOneData();
	ReadTestTwoData();
	ReadPuzzleOneData();
	ReadPuzzleTwoData();
}

void ASolverBase::DownloadPuzzleInfo()
{
	SolutionNumber = UKismetStringLibrary::Conv_StringToInt(SolutionFolder.Replace(TEXT("Solution0"), TEXT("")).Replace(TEXT("Solution"), TEXT("")));
	const FString DayUrl = FString::Printf(TEXT("%s/%i/input"), *AoCBaseUrl, SolutionNumber);
	FString Content = UHttpHelper::HttpRetriever(DayUrl, AocCookie);
	if (Content.Len() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("got zero content length"));
		return;
	}
	const FString FilePathOne = FString::Printf(TEXT("%s/%s/PuzzleOneData.txt"), *ProjectSource, *SolutionFolder);
	FFileHelper::SaveStringToFile(Content, *FilePathOne);
	const FString FilePathTwo = FString::Printf(TEXT("%s/%s/PuzzleTwoData.txt"), *ProjectSource, *SolutionFolder);
	FFileHelper::SaveStringToFile(Content, *FilePathTwo);
}

// Called when the game starts or when spawned
void ASolverBase::BeginPlay()
{
	Super::BeginPlay();

	ASolverGameMode* SolverGameMode = Cast<ASolverGameMode>(GetWorld()->GetAuthGameMode());
	if (SolverGameMode != nullptr)
	{
		AocCookie = SolverGameMode->GetAocCookie();
		int DayInt = SolverGameMode->DayToSolve;
		FString DayString = UKismetStringLibrary::Conv_IntToString(DayInt);
		if (DayString.Len() == 1)
		{
			DayString = FString::Printf(TEXT("0%s"), *DayString);
		}
		SolutionFolder = FString::Printf(TEXT("Solution%s"), *DayString);
	}
}

void ASolverBase::ParsePuzzleData()
{
}

// Called every frame
void ASolverBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

