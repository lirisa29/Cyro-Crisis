#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "MatchOverWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRestartGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuitTitleGame);

UCLASS()
class CYROCRISIS_API UMatchOverWidget : public UWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnRestartGame OnRestartGame;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnQuitTitleGame OnQuitGame;
	
	UFUNCTION(BlueprintCallable, Category = "Title Screen")
	void StartNewGame();

	UFUNCTION(BlueprintCallable, Category = "Title Screen")
	void QuitGame();

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MatchOverText;

	UPROPERTY(meta = (BindWidget))
	class UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
};
