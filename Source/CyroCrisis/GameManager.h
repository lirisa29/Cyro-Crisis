#pragma once

#include "CoreMinimal.h"
#include "DefaultGameStateBase.h"
#include "GameStateFactory.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	TitleScreen,
	Gameplay,
	MatchOver,
	Paused
};

UCLASS()
class CYROCRISIS_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameManager();

	void ChangeState(EGameState NewState);
	void UpdateState(float DeltaTime);
	void OnGameplayState();
	void OnMatchOverState();
	void OnPausedState();
	void TogglePause();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	// Store the current state
	UDefaultGameStateBase* CurrentState;

	// The state factory
	UGameStateFactory* StateFactory;
};