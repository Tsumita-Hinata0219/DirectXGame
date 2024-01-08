#pragma once
#include "EnemyManager/PhaseState/IEnemyPhaseState.h"

/* IEnemySpproachStateクラス */
class IEnemyApproachState : public IEnemyPhaseState {

public:

	void Update(Enemy* pEnemy) override;

};

