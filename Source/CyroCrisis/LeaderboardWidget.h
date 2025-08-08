#pragma once

#include "CoreMinimal.h"
#include "KillTracker.h"
#include "Blueprint/UserWidget.h"
#include "LeaderboardWidget.generated.h"

UCLASS()
class CYROCRISIS_API ULeaderboardWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* LeaderboardContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UPlayerEntryWidget> PlayerEntryWidgetClass;

	UFUNCTION(BlueprintCallable)
	void PopulateLeaderboard(const TArray<FPlayerScore>& PlayerScores, const FString& PlayerName);
	
};
