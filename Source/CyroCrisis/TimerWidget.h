#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "TimerWidget.generated.h"

UCLASS()
class CYROCRISIS_API UTimerWidget : public UWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TimerTextBlock;

public:
	// Updates the timer text via TimerWidget
	void UpdateTimerDisplay(int32 TimeRemaining);
};
