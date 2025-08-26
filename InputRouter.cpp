#pragma once
#include "PlayerController.cpp"

class InputRouter {
private:
    PlayerController* player;
    bool tracking;
    float startTime;
    float startX, startY;

public:
    InputRouter(PlayerController* player) : player(player), tracking(false), startTime(0), startX(0), startY(0) {}

    void Update(char input) {
        // Example: WASD + space
        if (input == 'w') player->OnLaneDelta(+1);
        if (input == 's') player->OnLaneDelta(-1);
        if (input == ' ') player->OnShoot();
    }
};
