#include "IEnemyApproachState.h"
#include "EnemyManager/Enemy/Enemy.h"


void IEnemyApproachState::Update(Enemy* pEnemy) {

	pEnemy->Approach2BattlePosition();

	if (pEnemy->GetInitMoveFlag()) {
		
		pEnemy->ChangePhaseState(new IEnemyLeaveState());
	}
}
