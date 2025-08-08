#include "GameStateFactory.h"
#include "GameManager.h"
#include "GameplayState.h"
#include "MatchOverState.h"
#include "PausedState.h"
#include "TitleScreenState.h"

UDefaultGameStateBase* UGameStateFactory::CreateState(EGameState StateType)
{
	switch (StateType)
	{
	case EGameState::TitleScreen:
		return NewObject<UTitleScreenState>();
	case EGameState::Gameplay:
		return NewObject<UGameplayState>();
	case EGameState::MatchOver:
		return NewObject<UMatchOverState>();
	case EGameState::Paused:
		return NewObject<UPausedState>();
	default:
		return nullptr;
	}
}
