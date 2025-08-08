#include "BTService_IsPlayerInShootRange.h"
#include "AIControllerBase.h"
#include "AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"

UBTService_IsPlayerInShootRange::UBTService_IsPlayerInShootRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = "Is Player In Shoot Range";
}

void UBTService_IsPlayerInShootRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get controller and NPC
	auto const * const cont = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());
	auto const * const npc = Cast<AAICharacter>(cont->GetPawn());

	// get player character
	auto const * const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// write true or false to the blackboard key depending on whether or not the player is in range
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), npc->GetDistanceTo(player) <= shootRange);
}
