#pragma once

#include "CoreMinimal.h"
#include "KillTracker.h"
#include "GameFramework/GameStateBase.h"
#include "DeathmatchGameState.generated.h"

UCLASS()
class CYROCRISIS_API ADeathmatchGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FPlayerScore> PlayerScores;

	UFUNCTION(BlueprintCallable)
	void AddKill(const FString& PlayerName);

	UFUNCTION(BlueprintCallable)
	void ResetScores();

	UFUNCTION(BlueprintCallable)
	void SortLeaderboard();

	UFUNCTION(BlueprintCallable)
	void ShowLeaderboard();

	UPROPERTY(EditAnywhere)
	class ULeaderboardWidget* LeaderboardWidgetInstance;

	APlayerController* PlayerController;
	
};
