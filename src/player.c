#include "player.h"

Player createPlayer(float x, float y, float height, float width, int filled, float red, float green, float blue)
{
    Player player;
    player.cube = createCube(x, y, height, width, filled, red, green, blue);
    player.gravity = 0;
    player.jumpPower = 0.3;
    player.movementSpeed = 0.15;
    player.nextPosition = player.cube.x;
    return player;
}

void playerMove(Player* player)
{
    if (player->cube.x < player->nextPosition)
    {
        player->cube.x += player->movementSpeed;
    }
    if (player->cube.x > player->nextPosition)
    {
        player->cube.x -= player->movementSpeed;
    }
}

void playerJump(Player* player)
{
    if (player->gravity == 0)
    {
        player->gravity = -player->jumpPower;
    }
}

void addGravity(Player* player)
{
    if (player->cube.y > 0)
    {
        player->gravity += 0.01;
    }
    else if (player->gravity > 0)
    {
        player->gravity = 0;
    }
    player->cube.y -= player->gravity;
}

void drawPlayer(Player player)
{
    drawCube(player.cube);
}