#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "GameFramework/GameMode.h"
#include "TitleScreenGameMode.generated.h"

UCLASS()
class CYROCRISIS_API ATitleScreenGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	// Pointer to the GameManager to handle state transitions
	UPROPERTY()
	AGameManager* GameManager;

protected:
	virtual void BeginPlay() override;
};
