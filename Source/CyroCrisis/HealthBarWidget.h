#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "HealthBarWidget.generated.h"

UCLASS()
class CYROCRISIS_API UHealthBarWidget : public UWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	void UpdateHealthBar(float HealthPercentage, const FText& HealthText);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HealthTextBlock;

};
