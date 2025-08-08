#pragma once

#include "CoreMinimal.h"
#include "DefaultGameStateBase.h"
#include "TitleScreenState.generated.h"

UCLASS()
class CYROCRISIS_API UTitleScreenState : public UDefaultGameStateBase
{
	GENERATED_BODY()

public:
	virtual void EnterState(APlayerController* PlayerController) override;
	virtual void ExitState(APlayerController* PlayerController) override;
	virtual void UpdateState(float DeltaTime) override;
};
