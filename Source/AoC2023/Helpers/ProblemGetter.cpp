// Fill out your copyright notice in the Description page of Project Settings.


#include "ProblemGetter.h"

#include <AoC2023/Statics/HttpHelper.h>
#include "AoC2023/GameMode/SolverGameMode.h"
#include "Kismet/KismetStringLibrary.h"


// Sets default values
AProblemGetter::AProblemGetter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AProblemGetter::LoginToAoC()
{
}

// Called when the game starts or when spawned
void AProblemGetter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProblemGetter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProblemGetter::DownloadPuzzleData(int Day)
{
	const FString Url = FString::Printf(TEXT("%s%i%s"), *BaseUrl, Day, *InputUrl);
	FString Cookie = TEXT("");
	ASolverGameMode* SolverGameMode = Cast<ASolverGameMode>(GetWorld()->GetAuthGameMode());
	
	if (SolverGameMode == nullptr)
	{
		return;
	}

	FString DayString = UKismetStringLibrary::Conv_IntToString(Day);
	if (DayString.Len() == 1)
	{
		DayString = FString::Printf(TEXT("0%s"), *DayString);
	}
	const FString SolutionFolder = FString::Printf(TEXT("Solution%s"), *DayString);
	const FString OutPath = FString::Printf(TEXT("%s/%s/PuzzleOneData.txt"), *ProjectSource, *SolutionFolder);
	UE_LOG(LogTemp, Warning, TEXT("Outpath: %s"), *OutPath);
	Cookie = SolverGameMode->GetAocCookie();
	FHttpModule& HTTPModule = FHttpModule::Get();

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> PRequest = HTTPModule.CreateRequest();

	PRequest->SetVerb(TEXT("GET"));
	PRequest->SetHeader(TEXT("Content-Type"), TEXT("text/html; charset=utf-8"));
	PRequest->SetHeader(TEXT("Cookie"), FString::Printf(TEXT("session=%s"), *Cookie));
	PRequest->SetURL(Url);
	PRequest->OnProcessRequestComplete().BindLambda(
		[&, OutPath](
			FHttpRequestPtr Request,
			FHttpResponsePtr Response,
			bool ConnectResult) mutable
		{
			if (ConnectResult && Response != nullptr) {
				FString Content;
				Content = Response->GetContentAsString();
				FFileHelper::SaveStringToFile(Content, *OutPath);
				UE_LOG(LogTemp, Warning, TEXT("Got result: %i chars of content, should be at %s"), Content.Len(), *OutPath);
				// UE_LOG(LogTemp, Warning, TEXT("Got result: %s"), *Result);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Connection failed."));
			}
		}
	);
	PRequest->ProcessRequest();
	
}

