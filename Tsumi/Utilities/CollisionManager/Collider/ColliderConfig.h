#pragma once
#include<cstdint>

const uint32_t kCollisionAttributePlayer = 0b0001;
const uint32_t kCollisionAttributeEnemy = 0b0010;

const uint32_t kCollisionMaskPlayer = 0b1110;
const uint32_t kCollisionMaskEnemy = 0b1101;

const uint32_t playerID = 0b00001;
const uint32_t playerBulletID = 0b00010;
const uint32_t EnemyID = 0b0011;
const uint32_t EnemyBulletID = 0b00100;
