#pragma once
#include <bits/stdc++.h>
#include "Vector3.h"
using namespace std;

class Bullet {
public:
    Bullet(float speed, float life, const Vector3& pos)
        : speed(speed), life(life), position(pos), alive(true) {}

    void Update(float deltaTime) {
        if (!alive) return;
        position.x += speed * deltaTime;
        
        life -= deltaTime;
        if (life <= 0.0f) {
            alive = false;
            std::cout << "[Bullet] Destroyed after lifetime.\n";
        }
    }

    bool IsAlive() const { return alive; }
    Vector3 GetPosition() const { return position; }

private:
    float speed;      // bullet speed
    float life;       // remaining life
    Vector3 position; // current position
    bool alive;       // active state
};