#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "PauseScreenWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnrestartGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnquitTitleGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnpausedGame);

UCLASS()
class CYROCRISIS_API UPauseScreenWidget : public UWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnrestartGame OnRestartGame;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnquitTitleGame OnQuitGame;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnpausedGame OnPauseGame;
	
	UFUNCTION(BlueprintCallable, Category = "Title Screen")
	void StartNewGame();

	UFUNCTION(BlueprintCallable, Category = "Title Screen")
	void QuitGame();

	UFUNCTION(BlueprintCallable, Category = "Title Screen")
	void PauseGame();

protected:
	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PauseText;

	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
	
};
