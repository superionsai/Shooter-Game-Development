#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "Vector3.h"
#include "Bullet.cpp"
#include "Shooter.cpp"
#include "PlayerController.cpp"
#include "InputRouter.cpp"
#include "Obstacle.cpp"
#include "SpawnManager.cpp"
#include "ScrollSystem.cpp"
#include "ScoreSystem.cpp"

// -----------------------------
// ENUM for Game State
// -----------------------------
enum class GameState {
    Ready,
    Playing,
    Paused,
    GameOver
};

// -----------------------------
// GameManager (Singleton)
// -----------------------------
class GameManager {
public:
    static GameManager& Instance() {
        static GameManager instance;
        return instance;
    }

    void StartRun() {
        cout << "[GameManager] Starting Run..." << endl;
        State = GameState::Playing;

        scoreSystem->ResetScore();
        player->ResetToLane(1);
        spawner->Begin();
        scroll->OnEnable();
    }

    void Pause() {
        if (State == GameState::Playing) {
            State = GameState::Paused;
            cout << "[GameManager] Paused." << endl;
        }
    }

    void Resume() {
        if (State == GameState::Paused) {
            State = GameState::Playing;
            cout << "[GameManager] Resumed." << endl;
        }
    }

    void GameOver() {
        if (State != GameState::GameOver) {
            State = GameState::GameOver;
            cout << "[GameManager] Game Over! Final Score = " 
                 << scoreSystem->GetScore() << endl;
            spawner->StopAll();
        }
    }

    void Update(float deltaTime, char input) {
        if (State != GameState::Playing) return;

        // update systems
        scroll->Update(deltaTime);
        scoreSystem->Update(deltaTime * 1000); // ms
        shooter->Update(deltaTime);
        player->Update(deltaTime);
        spawner->Update(deltaTime);

        // handle input
        inputRouter->Update(input);
    }

    // --- Setup references ---
    void Init(PlayerController* p, Shooter* s, SpawnManager* sp, 
              ScrollSystem* sc, ScoreSystem* scs, InputRouter* ir) {
        player = p; shooter = s; spawner = sp;
        scroll = sc; scoreSystem = scs; inputRouter = ir;
    }

    GameState GetState() const { return State; }

private:
    GameManager() = default;
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    GameState State = GameState::Ready;

    PlayerController* player = nullptr;
    Shooter* shooter = nullptr;
    SpawnManager* spawner = nullptr;
    ScrollSystem* scroll = nullptr;
    ScoreSystem* scoreSystem = nullptr;
    InputRouter* inputRouter = nullptr;
};