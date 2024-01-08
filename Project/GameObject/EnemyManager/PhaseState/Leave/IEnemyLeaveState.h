#pragma once
#include "EnemyManager/PhaseState/IEnemyPhaseState.h"

/* IEnemyLeaveStateクラス */
class IEnemyLeaveState : public IEnemyPhaseState {

public:

	void Update(Enemy* pEnemy) override;

};

