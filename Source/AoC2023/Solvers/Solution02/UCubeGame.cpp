// Fill out your copyright notice in the Description page of Project Settings.


#include "UCubeGame.h"

#include "Kismet/KismetStringLibrary.h"
#include "Logging/StructuredLog.h"

UCubeGame::UCubeGame()
{
}

bool UCubeGame::CheckGame()
{
	for (const FCubeReveal ThisReveal : Reveals)
	{
		int ThisMax = 0;
		switch (ThisReveal.CubeGameColor)
		{
		case ECubeGameColor::Red:
			ThisMax = RedMax;
			break;
		case ECubeGameColor::Green:
			ThisMax = GreenMax;
			break;
		case ECubeGameColor::Blue:
			ThisMax = BlueMax;
			break;
		default:
			break;
		}
		if (ThisMax < ThisReveal.ColorCount)
		{
			UE_LOGFMT(LogTemp, Warning, "Game {Id} is NOT Valid, {Count} {Color}", GameId, ThisReveal.ColorCount, UEnum::GetValueAsString(ThisReveal.CubeGameColor));
			bIsValidGame = false;
			return false;
		}
	}
	UE_LOGFMT(LogTemp, Warning, "Game {Id} is Valid", GameId);
	bIsValidGame = true;
	return true;
}

int UCubeGame::CheckGamePartB()
{
	int RedMin = 0;
	int BlueMin = 0;
	int GreenMin = 0;
	
	for (const FCubeReveal ThisReveal : Reveals)
	{
		switch (ThisReveal.CubeGameColor)
		{
		case ECubeGameColor::Red:
			if (ThisReveal.ColorCount > RedMin)
			{
				RedMin = ThisReveal.ColorCount;
			}
			break;
		case ECubeGameColor::Green:
			if (ThisReveal.ColorCount > GreenMin)
			{
				GreenMin = ThisReveal.ColorCount;
			}
			break;
		case ECubeGameColor::Blue:
			if (ThisReveal.ColorCount > BlueMin)
			{
				BlueMin = ThisReveal.ColorCount;
			}
			break;
		default:
			break;
		}
	}
	return RedMin * BlueMin * GreenMin;
}

void UCubeGame::DescribeGame()
{
	FString Descer = FString::Printf(TEXT("Game %i: "), GameId);
	for (auto Reveal : Reveals)
	{
		Descer.Append(FString::Printf(TEXT("%i %s, "), Reveal.ColorCount, *UEnum::GetValueAsString(Reveal.CubeGameColor)));
	}
	UE_LOGFMT(LogTemp, Warning, "{Des}", Descer);
}

void UCubeGame::LoadGameFromString(FString InData)
{
	// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
	FString FirstChop = InData.Replace(TEXT("Game "), TEXT(""));
	const int GameIndex = FirstChop.Find(TEXT(":"));
	GameId = UKismetStringLibrary::Conv_StringToInt(FirstChop.Left(GameIndex));

	const FString RevealGroup = FirstChop.RightChop(GameIndex + 1);
	TArray<FString> RevealArray;
	RevealGroup.ParseIntoArray(RevealArray, TEXT(";"));

	for (FString RevealInstance : RevealArray)
	{
		TArray<FString> CubeGroups;
		FString Trimmed = RevealInstance.TrimStart();
		Trimmed.ParseIntoArray(CubeGroups, TEXT(", "));

		for (FString CubeGroup : CubeGroups)
		{
			const int SpaceIndex = CubeGroup.Find(TEXT(" "));
			const int ColorCount = UKismetStringLibrary::Conv_StringToInt(CubeGroup.Left(SpaceIndex));
			ECubeGameColor ThisColor = ECubeGameColor::Green;
			if (CubeGroup.Contains(TEXT("red")))
			{
				ThisColor = ECubeGameColor::Red;
			}
			if (CubeGroup.Contains(TEXT("blue")))
			{
				ThisColor = ECubeGameColor::Blue;
			}
			FCubeReveal ThisReveal;
			ThisReveal.ColorCount = ColorCount;
			ThisReveal.CubeGameColor = ThisColor;
			Reveals.Add(ThisReveal);
		}

	}
}

void UCubeGame::SetMaxes(const int BlueMaxCount, const int RedMaxCount, const int GreenMaxCount)
{
	BlueMax = BlueMaxCount;
	RedMax = RedMaxCount;
	GreenMax = GreenMaxCount;
}
