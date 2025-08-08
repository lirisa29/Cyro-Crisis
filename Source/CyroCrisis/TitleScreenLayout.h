#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "TitleScreenWidget.h"
#include "WidgetBase.h"
#include "TitleScreenLayout.generated.h"

UCLASS(Abstract)
class CYROCRISIS_API UTitleScreenLayout : public UWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleStartGame();

	UFUNCTION()
	void HandleQuit();

	// Context for state transition
	AGameManager* GameManager;

	UPROPERTY(BlueprintReadOnly, Category = "Bound Widgets", meta = (BindWidget))
	TObjectPtr<UTitleScreenWidget> TitleScreenUI = nullptr;
	
};
