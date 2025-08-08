#include "BTTask_ShootAttack.h"
#include "CombatInterface.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UBTTask_ShootAttack::UBTTask_ShootAttack()
{
	NodeName = "Shoot Attack";
}

EBTNodeResult::Type UBTTask_ShootAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// if we are out of range, do not attack the player
	auto const OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if (OutOfRange)
	{
		// finish the task
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	// we are in range so get the AI's controller and the NPC itself
	auto const* const cont = OwnerComp.GetAIOwner();

	auto* const npc = Cast<AAICharacter>(cont->GetPawn());

	// if the NPC supports the ICombatInterface, cast and call the Execute_Shoot function
	if (auto* const icombat = Cast<ICombatInterface>(npc))
	{
		// checks if montage is finished so we don't play it again
		if (MontageHasFinished(npc))
		{
			icombat->Execute_Shoot(npc);
		}
	}

	// finish the task
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}

bool UBTTask_ShootAttack::MontageHasFinished(AAICharacter* const npc)
{
	return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetMontage());
}
