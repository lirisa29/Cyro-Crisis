#pragma once

#include "CoreMinimal.h"
#include "AmmoWidget.h"
#include "GameManager.h"
#include "MatchOverWidget.h"
#include "PauseScreenWidget.h"
#include "TimerWidget.h"
#include "WidgetBase.h"
#include "GameLayoutBase.generated.h"

class UHealthBarWidget;
class ACharacterBase;

UCLASS(Abstract)
class CYROCRISIS_API UGameLayoutBase : public UWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Bound Widgets", meta = (BindWidget))
	TObjectPtr<UHealthBarWidget>HealthBar = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Bound Widgets", meta = (BindWidget))
	TObjectPtr<UAmmoWidget>AmmoUI = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Bound Widgets", meta = (BindWidget))
	TObjectPtr<UTimerWidget>TimerUI = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Bound Widgets", meta = (BindWidget))
	TObjectPtr<UPauseScreenWidget>PauseUI = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Bound Widgets", meta = (BindWidget))
	TObjectPtr<UMatchOverWidget>MatchOverUI = nullptr;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleRestartGame();

	UFUNCTION()
	void HandleQuit();

	UFUNCTION()
	void HandlePause();

	// Context for state transition
	AGameManager* GameManager;
	
};
