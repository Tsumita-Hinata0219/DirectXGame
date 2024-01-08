#include "IEnemyApproachState.h"
#include "EnemyManager/Enemy/Enemy.h"


void IEnemyApproachState::Update(Enemy* pEnemy) {

	pEnemy->SubtractTransform(pEnemy->GetVelocity());

	if (pEnemy->GetWorldTransform().GetWorldPos().z < 30) {
		
		pEnemy->ChangePhaseState(new IEnemyLeaveState());
	}
}
