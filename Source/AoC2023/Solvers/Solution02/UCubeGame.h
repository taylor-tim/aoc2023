// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UCubeGame.generated.h"

/**
 * 
 */
UENUM()
enum ECubeGameColor
{
	Blue,
	Red,
	Green
};

USTRUCT()
struct FCubeReveal
{
	GENERATED_BODY()
public:
	ECubeGameColor CubeGameColor = ECubeGameColor::Blue;
	int ColorCount = 0;
};

UCLASS()
class AOC2023_API UCubeGame : public UObject
{
	GENERATED_BODY()

	UCubeGame();

public:
	UFUNCTION()
	int GetGameId() const { return GameId; }

	UFUNCTION()
	bool CheckGame();

	UFUNCTION()
	int CheckGamePartB();

	UFUNCTION()
	void DescribeGame();
	
	UFUNCTION()
	void LoadGameFromString(FString InData);
	
	UFUNCTION()
	void SetMaxes(int BlueMaxCount, int RedMaxCount, int GreenMaxCount);

protected:

	UPROPERTY()
	int GameId = 0;
	
	UPROPERTY()
	TArray<FCubeReveal> Reveals;

	UPROPERTY()
	bool bIsValidGame = false;

	UPROPERTY()
	int RedMax = 12;
	
	UPROPERTY()
	int GreenMax = 13;
	
	UPROPERTY()
	int BlueMax = 14;
};

