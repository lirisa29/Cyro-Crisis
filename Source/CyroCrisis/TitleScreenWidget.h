#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "TitleScreenWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuitGame);

UCLASS()
class CYROCRISIS_API UTitleScreenWidget : public UWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnStartGame OnStartGame;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnQuitGame OnQuitGame;
	
	UFUNCTION(BlueprintCallable, Category = "Title Screen")
	void StartNewGame();

	UFUNCTION(BlueprintCallable, Category = "Title Screen")
	void QuitGame();

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
};
