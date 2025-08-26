#pragma once

class ScrollSystem {
public:
    static float CurrentSpeed;

private:
    float baseSpeed;
    float addPerStep;
    float stepSeconds;
    float maxSpeed;
    float t;

public:
    ScrollSystem(float base, float addStep, float stepSec, float max)
        : baseSpeed(base), addPerStep(addStep), stepSeconds(stepSec), maxSpeed(max), t(0) {}

    void OnEnable() { t = 0; CurrentSpeed = baseSpeed; }

    void Update(float deltaTime) {
        t += deltaTime;
        int steps = static_cast<int>(t / stepSeconds);
        CurrentSpeed = baseSpeed + steps * addPerStep;
        if (CurrentSpeed > maxSpeed) CurrentSpeed = maxSpeed;
    }
};

float ScrollSystem::CurrentSpeed = 0.0f;
