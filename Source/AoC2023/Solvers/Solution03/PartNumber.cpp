// Fill out your copyright notice in the Description page of Project Settings.


#include "PartNumber.h"

bool FPartNumber::IsAdjacentTo(const FVector& InVector)
{
	for (FVector ThisVector : NumberVectors)
	{
		TArray<FVector> Neighbors = GetNeighbors(ThisVector);
		if (Neighbors.Contains(InVector))
		{
			return true;
		}
	}
	return false;
}

TArray<FVector> FPartNumber::GetNeighbors(const FVector& InVector)
{
	TArray<FVector> Neighbors;
	const bool bHasLeft = InVector.X > 0;
	const bool bHasTop = InVector.Y > 0;
	
	if (bHasTop)
	{
		if (bHasLeft)
		{
			Neighbors.Add(FVector(InVector.X - 1, InVector.Y - 1, 0));
		}
		Neighbors.Add(FVector(InVector.X, InVector.Y - 1, 0));
		Neighbors.Add(FVector(InVector.X + 1, InVector.Y - 1, 0));
	}
	if (bHasLeft)
	{
		Neighbors.Add(FVector(InVector.X - 1, InVector.Y, 0));
		Neighbors.Add(FVector(InVector.X - 1, InVector.Y + 1, 0));
	}
	Neighbors.Add(FVector(InVector.X + 1, InVector.Y, 0));
	Neighbors.Add(FVector(InVector.X, InVector.Y + 1, 0));
	Neighbors.Add(FVector(InVector.X + 1, InVector.Y + 1, 0));
	return Neighbors;
}
