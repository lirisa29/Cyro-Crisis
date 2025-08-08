#pragma once

#include "CoreMinimal.h"
#include "AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ShootAttack.generated.h"

UCLASS()
class CYROCRISIS_API UBTTask_ShootAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_ShootAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	bool MontageHasFinished(AAICharacter* const npc);
};
