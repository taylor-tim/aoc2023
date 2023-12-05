// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AoC2023/AoC2023GameMode.h"
#include "SolverGameMode.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeginSolve);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFinishSolve, FString, Answer);

UCLASS()
class AOC2023_API ASolverGameMode : public AAoC2023GameMode
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
	FString GetAocCookie() { return AoCCookie; }
	
	UFUNCTION(BlueprintCallable)
	int GetSolveDay() { return DayToSolve; }
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnBeginSolve OnBeginSolve;
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnFinishSolve OnFinishSolve;
	
	UPROPERTY(EditAnywhere, Blueprintable)
	int DayToSolve = 0;
	
	UPROPERTY(EditAnywhere, Blueprintable)
    FString AoCCookie = TEXT("");
};
