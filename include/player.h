#ifndef PLAYER_H
#define PLAYER_H

#include "cube.h"

typedef struct Player {
    Cube cube;
    float gravity;
    float jumpPower;
    float movementSpeed;
    float nextPosition;
} Player;

Player createPlayer(float x, float y, float height, float width, int filled, float red, float green, float blue);

void playerMove(Player* player);

void playerJump(Player* player);

void addGravity(Player* player);

void drawPlayer(Player player);

#endif