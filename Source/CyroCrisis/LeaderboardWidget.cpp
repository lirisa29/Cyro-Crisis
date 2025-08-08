// Fill out your copyright notice in the Description page of Project Settings.


#include "LeaderboardWidget.h"

#include "PlayerEntryWidget.h"
#include "Components/VerticalBox.h"

void ULeaderboardWidget::PopulateLeaderboard(const TArray<FPlayerScore>& PlayerScores, const FString& PlayerName)
{
	if (!LeaderboardContainer || !PlayerEntryWidgetClass)
	{
		return;
	}

	LeaderboardContainer->ClearChildren();

	for (const FPlayerScore& Score : PlayerScores)
	{
		UPlayerEntryWidget* EntryWidget = CreateWidget<UPlayerEntryWidget>(this, PlayerEntryWidgetClass);

		if (EntryWidget)
		{
			bool bIsHighlighted = (Score.PlayerName == PlayerName);

			EntryWidget->SetupEntry(Score.PlayerName, Score.KillCount, bIsHighlighted);

			LeaderboardContainer->AddChildToVerticalBox(EntryWidget);
		}

	}
}
