#include "player.h"

Player createPlayer(float x, float y, float width, float height, int filled, float red, float green, float blue)
{
    Player player;
    player.cube = createCube(x, y, width, height, filled, red, green, blue);
    player.movementSpeed = 0.15;
    player.jumpPower = 0.3;
    player.gravity = 0;
    player.isGrounded = 0;
    return player;
}

void playerJump(Player* player)
{
    player->gravity = -player->jumpPower;
}

void addGravity(Player* player)
{
    player->gravity += 0.01;
    player->cube.y -= player->gravity;
}

int checkCollision(Player player, Cube cube)
{
    if (player.cube.x + player.cube.width/2 > cube.x - cube.width/2 &&
    player.cube.x - player.cube.width/2 < cube.x + cube.width/2 &&
    player.cube.y + player.cube.width/2 > cube.y - cube.height/2 &&
    player.cube.y - player.cube.height/2 < cube.y + cube.height/2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void drawPlayer(Player player)
{
    drawCube(player.cube);
}