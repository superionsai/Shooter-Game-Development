#pragma once
#include <bits/stdc++.h>

class ScoreSystem {
public:
    static ScoreSystem& Instance() {
        static ScoreSystem instance;
        return instance;
    }

    void ResetScore() {
        Score = 0;
        timeAcc = 0.0f;
        lastTick = std::chrono::steady_clock::now();
        std::cout << "[ScoreSystem] Score reset.\n";
    }

    void Update(float deltaTimeMs) {
        timeAcc += deltaTimeMs;
        if (timeAcc >= timePerPointMs) {
            int points = static_cast<int>(timeAcc / timePerPointMs);
            Score += points;
            timeAcc -= points * timePerPointMs;
        }
    }

    void AddKillScore() {
        Score += killScore;
        std::cout << "[ScoreSystem] Kill! +" << killScore 
                  << " points (Total: " << Score << ")\n";
    }

    int GetScore() const { return Score; }

private:
    ScoreSystem() = default;
    ScoreSystem(const ScoreSystem&) = delete;
    ScoreSystem& operator=(const ScoreSystem&) = delete;

    int Score = 0;                  // Current score
    int killScore = 100;            // Points per kill
    int timePerPointMs = 500;       // Passive +1 point per 500ms
    float timeAcc = 0.0f;           // Accumulator for time-based score
    std::chrono::steady_clock::time_point lastTick;
};
