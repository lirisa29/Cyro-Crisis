#include "TimerWidget.h"

#include "Components/TextBlock.h"

void UTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UTimerWidget::UpdateTimerDisplay(int32 TimeRemaining)
{
	if (!TimerTextBlock)
		return;

	int32 Minutes = TimeRemaining / 60;
	int32 Seconds = TimeRemaining % 60;

	// Format the time as MM:SS
	FString TimerString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

	// Update the TimerTextBlock
	TimerTextBlock->SetText(FText::FromString(TimerString));
}
