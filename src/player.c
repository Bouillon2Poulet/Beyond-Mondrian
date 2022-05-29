#include "player.h"

Player createPlayer(float x, float y, float width, float height, int filled, float red, float green, float blue)
{
    Player player;
    player.cube = createCube(x, y, width, height, filled, red, green, blue, 0);
    player.movementSpeed = 1.5;
    player.jumpPower = 3;
    player.gravity = 0;
    player.isGrounded = 0;
    player.startColors[0] = player.cube.red;
    player.startColors[1] = player.cube.green;
    player.startColors[2] = player.cube.blue;
    player.startPositions[0] = player.cube.x;
    player.startPositions[1] = player.cube.y;
    return player;
}

void movePlayer(Player* player, int direction)
{
    if (direction == -1)
    {
        player->cube.x -= player->movementSpeed;
    }
    else if (direction == 1)
    {
        player->cube.x += player->movementSpeed;
    }
}

void playerJump(Player* player)
{
    player->gravity = -player->jumpPower;
}

void addGravity(Player* player)
{
    player->gravity += 0.1;
    player->cube.y -= player->gravity;
}

int checkCollision(Player player, Cube cube)
{
    if (player.cube.x + player.cube.width/2 > cube.x - cube.width/2 &&
    player.cube.x - player.cube.width/2 < cube.x + cube.width/2 &&
    player.cube.y + player.cube.height/2 > cube.y - cube.height/2 &&
    player.cube.y - player.cube.height/2 < cube.y + cube.height/2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void checkEndCollision(Player* player, Cube cube)
{
    if (player->cube.x > cube.x - cube.width/2 &&
    player->cube.x < cube.x + cube.width/2 &&
    player->cube.y > cube.y - cube.height/2 &&
    player->cube.y < cube.y + cube.height/2)
    {
        player->cube.red = 1;
        player->cube.green = 1;
        player->cube.blue = 1;
    }
    else
    {
        player->cube.red = player->startColors[0];
        player->cube.green = player->startColors[1];
        player->cube.blue = player->startColors[2];
    }
}

void drawPlayer(Player player)
{
    drawCube(player.cube);
}