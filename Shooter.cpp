#pragma once
#include <bits/stdc++.h>
using namespace std;
#include "Bullet.cpp"

class Shooter {
public:
    Shooter(float cooldown, float bulletSpeed, float bulletLife)
        : cooldown(cooldown), bulletSpeed(bulletSpeed), bulletLife(bulletLife),
          nextFire(0.0f), elapsedTime(0.0f) {}

    void Update(float deltaTime) {
        elapsedTime += deltaTime;

        for (auto& bullet : bullets) {
            bullet.Update(deltaTime);
        }
        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(),
                           [](const Bullet& b) { return !b.IsAlive(); }),
            bullets.end()
        );
    }

    void TryShoot(const Vector3& muzzlePos) {
        if (elapsedTime >= nextFire) {
            bullets.emplace_back(bulletSpeed, bulletLife, muzzlePos);
            nextFire = elapsedTime + cooldown;
            std::cout << "[Shooter] Bullet fired at (" 
                      << muzzlePos.x << "," << muzzlePos.y << "," << muzzlePos.z << ")\n";
        } else {
            std::cout << "[Shooter] On cooldown. Next shot at " << nextFire << "s\n";
        }
    }

private:
    float cooldown;
    float bulletSpeed;
    float bulletLife;
    float nextFire;
    float elapsedTime;

    std::vector<Bullet> bullets;
};

