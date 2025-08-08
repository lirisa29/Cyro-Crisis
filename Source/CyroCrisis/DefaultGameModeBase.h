#pragma once

#include "CoreMinimal.h"
#include "AICharacter.h"
#include "CharacterBase.h"
#include "GameManager.h"
#include "RespawnPoint.h"
#include "GameFramework/GameMode.h"
#include "DefaultGameModeBase.generated.h"

UCLASS()
class CYROCRISIS_API ADefaultGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
	TArray<ARespawnPoint*> RespawnLocations;

	UPROPERTY(EditDefaultsOnly, Category = "Respawn")
	TSubclassOf<ARespawnPoint> RespawnPointClass;

	void RespawnPlayer(ACharacterBase* PlayerCharacter);

	void RespawnBot(AAICharacter* BotCharacter);

	// Pointer to the GameManager to handle state transitions
	UPROPERTY()
	AGameManager* GameManager;

	// Starts the match timer
	void StartMatchTimer();

	// Updates the timer each second
	void UpdateMatchTimer();

	void EndGame();

protected:
	virtual void BeginPlay() override;

	FTimerHandle MatchTimerHandle;
	int32 MatchTimeRemaining; // Time in seconds

	// Called when the match timer ends
	void OnMatchEnd();
};
