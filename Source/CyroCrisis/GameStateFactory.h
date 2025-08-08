#pragma once

#include "CoreMinimal.h"
#include "DefaultGameStateBase.h"
#include "GameStateFactory.generated.h"

enum class EGameState : uint8;

UCLASS()
class CYROCRISIS_API UGameStateFactory : public UObject
{
	GENERATED_BODY()

public:
	// Factory method for creating states based on the requested state type
	UDefaultGameStateBase* CreateState(EGameState StateType);
};
