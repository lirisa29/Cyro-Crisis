#pragma once

#include "CoreMinimal.h"
#include "AmmoWidget.h"
#include "MatchOverWidget.h"
#include "PauseScreenWidget.h"
#include "TimerWidget.h"
#include "GameFramework/HUD.h"
#include "HUDBase.generated.h"

class UHealthBarWidget;
class UGameLayoutBase;

UCLASS()
class CYROCRISIS_API AHUDBase : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameLayoutBase>GameLayoutBaseClass = nullptr;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UWorld>World = nullptr;

	UPROPERTY()
	TObjectPtr<UGameLayoutBase>GameLayoutWidget = nullptr;
	
public:
	UPROPERTY()
	UHealthBarWidget* HealthBarWidget = nullptr;

	UPROPERTY()
	UAmmoWidget* AmmoWidget = nullptr;

	UPROPERTY()
	UTimerWidget* TimerWidget = nullptr;

	UPROPERTY()
	UPauseScreenWidget* PauseWidget = nullptr;

	UPROPERTY()
	UMatchOverWidget* MatchOverWidget = nullptr;

	void SetAmmo(int32 Magazine, int32 Total);

	void SetGameUIVisibility(bool bIsVisible);

	void SetPauseUIVisibility(bool bIsVisible);

	void SetMatchOverUIVisibility(bool bIsVisible);

	// Updates the on-screen timer
	void UpdateMatchTimerDisplay(int32 TimeRemaining);
	
};
