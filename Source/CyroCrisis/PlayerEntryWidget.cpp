// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerEntryWidget.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"


void UPlayerEntryWidget::SetupEntry(const FString& PlayerName, int32 KillCount, bool bIsHighlighted)
{
	if (PlayerNameText)
	{
		PlayerNameText->SetText(FText::FromString(PlayerName));
	}

	if (KillCountText)
	{
		KillCountText->SetText(FText::AsNumber(KillCount));
	}

	if (BackgroundBorder)
	{
		FLinearColor HighlightColor = bIsHighlighted ? FLinearColor:: White : FLinearColor:: Red;
		BackgroundBorder->SetBrushColor(HighlightColor);
	}
}
