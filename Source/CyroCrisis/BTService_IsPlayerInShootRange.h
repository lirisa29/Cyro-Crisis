#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsPlayerInShootRange.generated.h"

UCLASS()
class CYROCRISIS_API UBTService_IsPlayerInShootRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_IsPlayerInShootRange();
	
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	float shootRange = 100.f;
};
