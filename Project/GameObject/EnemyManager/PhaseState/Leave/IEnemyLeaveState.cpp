#include "IEnemyLeaveState.h"
#include "EnemyManager/Enemy/Enemy.h"


void IEnemyLeaveState::Update(Enemy* pEnemy) {

	pEnemy->AddTransform(pEnemy->GetVelocity());

	if (pEnemy->GetWorldTransform().GetWorldPos().z > 80) {

		pEnemy->ChangePhaseState(new IEnemyApproachState);
	}
}