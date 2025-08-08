#pragma once

#include "CoreMinimal.h"
#include "DefaultGameStateBase.generated.h"

UCLASS(Abstract)
class CYROCRISIS_API UDefaultGameStateBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void EnterState(APlayerController* PlayerController) PURE_VIRTUAL(UDefaultGameStateBase::EnterState, );
	virtual void ExitState(APlayerController* PlayerController) PURE_VIRTUAL(UDefaultGameStateBase::ExitState, );
	virtual void UpdateState(float DeltaTime) PURE_VIRTUAL(UDefaultGameStateBase::UpdateState, );
};
