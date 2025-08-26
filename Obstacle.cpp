#pragma once
#include <iostream>
#include "GameManager.cpp"
#include "ScrollSystem.cpp"
#include "ScoreSystem.cpp"
#include "Pool.cpp"
#include "Vector3.h"

class Obstacle {
protected:
    bool isDestructible;
    int hp;
    float despawnX;
    std::string prefabRef;   // pool key reference
    Vector3 position;

public:
    Obstacle(bool destructible, int hp, float despawnX, const std::string& prefabRef, Vector3 startPos)
        : isDestructible(destructible), hp(hp), despawnX(despawnX), prefabRef(prefabRef), position(startPos) {}

    bool IsDestructible() const { return isDestructible; }

    virtual void Update(float deltaTime) {
        // Scroll left
        position.x -= ScrollSystem::CurrentSpeed * deltaTime;

        // Despawn if out of screen
        if (position.x < despawnX) {
            Pool::Return(prefabRef, this);
        }
    }

    virtual void TakeDamage(int dmg) {
        if (!isDestructible) return;
        hp -= dmg;
        if (hp <= 0) {
            Die();
        }
    }

protected:
    virtual void Die() {
        ScoreSystem::Instance().AddKillScore(); // award points
        Pool::Return(prefabRef, this);
    }

    virtual void OnTriggerEnterPlayer() {
        GameManager::Instance().GameOver();
    }
};
