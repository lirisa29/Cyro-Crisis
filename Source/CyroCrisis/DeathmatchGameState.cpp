#include "DeathmatchGameState.h"

#include "LeaderboardWidget.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void ADeathmatchGameState::AddKill(const FString& PlayerName)
{
	FPlayerScore* PlayerScore = PlayerScores.FindByPredicate([&](const FPlayerScore& Score)
		{ return Score.PlayerName == PlayerName; });

	if (PlayerScore)
	{
		PlayerScore->KillCount++;
	}else
	{
		FPlayerScore NewScore;
		NewScore.PlayerName = PlayerName;
		NewScore.KillCount = 1;
		PlayerScores.Add(NewScore);
	}
}

void ADeathmatchGameState::ResetScores()
{
	PlayerScores.Empty();
}

void ADeathmatchGameState::SortLeaderboard()
{
	PlayerScores.Sort([](const FPlayerScore& A, const FPlayerScore& B)
	{
		return A.KillCount > B.KillCount;
	});
}

void ADeathmatchGameState::ShowLeaderboard()
{
	if (!PlayerController)
	{
		PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	}

	FString PlayerName;
	if (PlayerController && PlayerController->PlayerState)
	{
		PlayerName = PlayerController->PlayerState->GetPlayerName();
	}else
	{
		PlayerName = TEXT("Unknown Player");
	}
	
	if (LeaderboardWidgetInstance == nullptr)
	{
		SortLeaderboard();

		ULeaderboardWidget* LeaderboardWidget = Cast<ULeaderboardWidget>(LeaderboardWidgetInstance);
		if (LeaderboardWidget)
		{
			LeaderboardWidget->PopulateLeaderboard(PlayerScores, PlayerName);
		}
	}
}
