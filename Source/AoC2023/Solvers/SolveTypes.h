﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SolveTypes.generated.h"

/**
 * 
 */
UCLASS()
class AOC2023_API USolveTypes : public UObject
{
	GENERATED_BODY()
};
UENUM()
enum class ESolveTypes : uint8
{
	PartOne UMETA(DisplayName="Part One"),
	PartTwo UMETA(DisplayName="Part Two"),
	TestDataOne UMETA(DisplayName="Test Data One"),
	TestDataTwo UMETA(DisplayName="Test Data Two"),
	None UMETA(DisplayName="None"),
};
