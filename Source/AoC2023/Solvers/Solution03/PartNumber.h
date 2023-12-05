// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PartNumber.generated.h"

/**
 * 
 */
USTRUCT()
struct AOC2023_API FPartNumber
{
	GENERATED_BODY()
public:
	bool IsValidPart();
	bool IsAdjacentTo(const FVector& InVector);

	static TArray<FVector> GetNeighbors(const FVector& InVector);

	UPROPERTY()
	TArray<FVector> NumberVectors;

	UPROPERTY()
	int Number = 0;
};
