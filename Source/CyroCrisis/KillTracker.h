#pragma once

#include "CoreMinimal.h"
#include "KillTracker.generated.h"

USTRUCT(BlueprintType)
struct FPlayerScore
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite)
	int32 KillCount;

	FPlayerScore() : PlayerName(TEXT("Unknown")), KillCount(0) {}
};
