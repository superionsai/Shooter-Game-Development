#pragma once
#include <bits/stdc++.h>
using namespace std;
#include "Shooter.cpp"
#include "Vector3.h"

class PlayerController {
public:
    PlayerController(float laneHeight, float moveSpeed, Shooter* shooter)
    : laneHeight(laneHeight), moveSpeed(moveSpeed), shooter(shooter), CurrentLane(1), position(0,0,0), targetPos(0,0,0) {}

    void Start() {
        CurrentLane = 1;
        targetPos = Vector3(0, LaneY(CurrentLane), 0);
        position = targetPos;
        cout << "[PlayerController] Starting at lane" << CurrentLane << endl;
    }
    void Update(float deltaTime) {
        float diffY = targetPos.y - position.y;
        if (fabs(diffY) > 0.01f) {
            float step = moveSpeed * deltaTime;
            if (fabs(diffY) < step) position.y = targetPos.y;
            else position.y += (diffY > 0 ? step : -step);
        }
    }
    void OnLaneDelta(int delta) {
        int newLane = CurrentLane + delta;
        if (newLane <0) newLane = 0;
        if (newLane >2) newLane = 2;

        if (newLane != CurrentLane) {
            CurrentLane = newLane;
            targetPos = Vector3(0, LaneY(CurrentLane), 0);
            cout << "[PlayerController] Moved to lane" << CurrentLane << endl;
        }
    } 
    void OnShoot() {
        if (shooter)
        shooter->TryShoot(position);
        cout << "[PlayerController] Shooting from lane" << CurrentLane << endl;
    }            
    void ResetToLane(int lane) {
        if (lane < 0) lane = 0;
        if (lane > 2) lane = 2;
        CurrentLane = lane;
        targetPos = Vector3(0, LaneY(CurrentLane), 0);
        position = targetPos;
        cout << "[PlayerController] Reset to lane " << CurrentLane << endl;
    }             
    int GetCurrentLane() const { return CurrentLane; }

private:             
    float LaneY(int lane) const {
    return lane*laneHeight; }

    float laneHeight;
    float moveSpeed;
    Shooter* shooter;
    int CurrentLane;
    Vector3 position;
    Vector3 targetPos;
}; 