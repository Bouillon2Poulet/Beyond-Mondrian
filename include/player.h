#ifndef PLAYER_H
#define PLAYER_H

#include "cube.h"

typedef struct Player {
    Cube cube;
    float movementSpeed;
    float jumpPower;
    float gravity;
    int isGrounded;
} Player;

Player createPlayer(float x, float y, float height, float width, int filled, float red, float green, float blue);

void movePlayer(Player* player, int direction);

void playerJump(Player* player);

void addGravity(Player* player);

int checkCollision(Player player, Cube cube);

void drawPlayer(Player player);

#endif