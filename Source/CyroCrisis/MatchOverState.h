#pragma once

#include "CoreMinimal.h"
#include "DefaultGameStateBase.h"
#include "MatchOverState.generated.h"

UCLASS()
class CYROCRISIS_API UMatchOverState : public UDefaultGameStateBase
{
	GENERATED_BODY()

public:
	virtual void EnterState(APlayerController* PlayerController) override;
	virtual void ExitState(APlayerController* PlayerController) override;
	virtual void UpdateState(float DeltaTime) override;
	
};
