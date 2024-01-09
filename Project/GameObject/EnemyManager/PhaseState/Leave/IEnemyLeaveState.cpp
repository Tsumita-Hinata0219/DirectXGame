#include "IEnemyLeaveState.h"
#include "EnemyManager/Enemy/Enemy.h"


void IEnemyLeaveState::Update(Enemy* pEnemy) {

	pEnemy->Attack();
}