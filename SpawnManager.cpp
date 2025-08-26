#pragma once
#include <vector>
#include <random>
#include "Obstacle.cpp"
#include "Pool.cpp"
#include "Vector3.h"

class SpawnManager {
private:
    float laneHeight;
    float spawnX;
    float despawnX;
    std::string destructiblePrefab;
    std::string indestructiblePrefab;

    float t;
    float nextSpawn;
    int lastSafeLane;

    bool running;

public:
    SpawnManager(float laneHeight, float spawnX, float despawnX,
                 const std::string& destructible, const std::string& indestructible)
        : laneHeight(laneHeight), spawnX(spawnX), despawnX(despawnX),
          destructiblePrefab(destructible), indestructiblePrefab(indestructible),
          t(0), nextSpawn(0), lastSafeLane(1), running(false) {}

    void Begin() { t = 0; nextSpawn = 0; running = true; }
    void StopAll() { running = false; }

    void Update(float deltaTime) {
        if (!running) return;
        t += deltaTime;

        if (t >= nextSpawn) {
            SpawnColumn();
            ScheduleNext();
        }
    }

private:
    void ScheduleNext() {
        // For now fixed 2 seconds, can use curve later
        nextSpawn = t + 2.0f;
    }

    void SpawnColumn() {
        std::vector<bool> safe(3, false);
        int safeLane = rand() % 3;
        safe[safeLane] = true;

        for (int lane = 0; lane < 3; lane++) {
            if (safe[lane]) continue;
            bool destructible = (rand() % 100 < 70); // 70% chance destructible
            std::string prefab = destructible ? destructiblePrefab : indestructiblePrefab;
            Vector3 pos(spawnX, LaneY(lane), 0);
            Pool::Get(prefab, pos);
        }
        lastSafeLane = safeLane;
    }

    float LaneY(int lane) const { return lane * laneHeight; }
};
