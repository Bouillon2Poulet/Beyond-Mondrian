#include "movingCube.h"
#include <algorithm>

MovingCube createMovingCube(float x, float y, float height, float width, int filled, float red, float green, float blue, float x1, float y1, float x2, float y2, int directionPoint)
{
    MovingCube movingCube;
    movingCube.cube = createCube(x, y, width, height, filled, red, green, blue, 0);
    movingCube.x1 = x1;
    movingCube.x2 = x2;
    movingCube.y1 = y1;
    movingCube.y2 = y2;
    movingCube.speed = 0.2;
    movingCube.directionPoint = directionPoint;
    return movingCube;
}

void moveCube(MovingCube* movingCube, Player* scenePlayers, int playersCount)
{
    switch (movingCube->directionPoint)
    {
        case 1:
            if (movingCube->cube.x < movingCube->x1)
            {
                movingCube->cube.x += movingCube->speed;
                for (auto &player : movingCube->players)
                {
                    player->cube.x += movingCube->speed;
                }
                if (movingCube->cube.x > movingCube->x1)
                {
                    movingCube->cube.x = movingCube->x1;
                }
            } 
            else if (movingCube->cube.x > movingCube->x1)
            {
                movingCube->cube.x -= movingCube->speed;
                for (auto &player : movingCube->players)
                {
                    player->cube.x -= movingCube->speed;
                }
                if (movingCube->cube.x < movingCube->x1)
                {
                    movingCube->cube.x = movingCube->x1;
                }
            }

            for (int i = 0; i < playersCount; i++)
            {
                if (std::find(movingCube->players.begin(), movingCube->players.end(), &scenePlayers[i]) != movingCube->players.end())
                {
                    break;
                }
                else
                {
                    if (checkCollision(scenePlayers[i], movingCube->cube) == 1)
                    {
                        if (scenePlayers[i].cube.x < movingCube->cube.x)
                        {
                            scenePlayers[i].cube.x = movingCube->cube.x - movingCube->cube.width/2 - scenePlayers[i].cube.width/2;
                        }
                        else
                        {
                            scenePlayers[i].cube.x = movingCube->cube.x + movingCube->cube.width/2 + scenePlayers[i].cube.width/2;
                        }
                    }
                }
            }

            if (movingCube->cube.y < movingCube->y1)
            {
                movingCube->cube.y += movingCube->speed;
                for (auto &player : movingCube->players)
                {
                    player->cube.y += movingCube->speed;
                }
                if (movingCube->cube.y > movingCube->y1)
                {
                    movingCube->cube.y = movingCube->y1;
                }
            } 
            else 
            {
                movingCube->cube.y -= movingCube->speed;
                for (auto &player : movingCube->players)
                {
                    player->cube.y -= movingCube->speed;
                }
                if (movingCube->cube.y < movingCube->y1)
                {
                    movingCube->cube.y = movingCube->y1;
                }
            }

            if (movingCube->cube.x == movingCube->x1 && movingCube->cube.y == movingCube->y1)
            {
                movingCube->directionPoint = 2;
            }
            break;

        case 2:
            if (movingCube->cube.x < movingCube->x2)
            {
                movingCube->cube.x += movingCube->speed;
                for (auto &player : movingCube->players)
                {
                    player->cube.x += movingCube->speed;
                }
                if (movingCube->cube.x > movingCube->x2)
                {
                    movingCube->cube.x = movingCube->x2;
                }
            } 
            else if (movingCube->cube.x > movingCube->x2)
            {
                movingCube->cube.x -= movingCube->speed;
                for (auto &player : movingCube->players)
                {
                    player->cube.x -= movingCube->speed;
                }
                if (movingCube->cube.x < movingCube->x2)
                {
                    movingCube->cube.x = movingCube->x2;
                }
            }

            for (int i = 0; i < playersCount; i++)
            {
                if (std::find(movingCube->players.begin(), movingCube->players.end(), &scenePlayers[i]) != movingCube->players.end())
                {
                    break;
                }
                else
                {
                    if (checkCollision(scenePlayers[i], movingCube->cube) == 1)
                    {
                        if (scenePlayers[i].cube.x < movingCube->cube.x)
                        {
                            scenePlayers[i].cube.x = movingCube->cube.x - movingCube->cube.width/2 - scenePlayers[i].cube.width/2;
                        }
                        else
                        {
                            scenePlayers[i].cube.x = movingCube->cube.x + movingCube->cube.width/2 + scenePlayers[i].cube.width/2;
                        }
                    }
                }
            }

            if (movingCube->cube.y < movingCube->y2)
            {
                movingCube->cube.y += movingCube->speed;
                for (auto &player : movingCube->players)
                {
                    player->cube.y += movingCube->speed;
                }
                if (movingCube->cube.y > movingCube->y2)
                {
                    movingCube->cube.y = movingCube->y2;
                }
            } 
            else 
            {
                movingCube->cube.y -= movingCube->speed;
                for (auto &player : movingCube->players)
                {
                    player->cube.y -= movingCube->speed;
                }
                if (movingCube->cube.y < movingCube->y2)
                {
                    movingCube->cube.y = movingCube->y2;
                }
            }

            if (movingCube->cube.x == movingCube->x2 && movingCube->cube.y == movingCube->y2)
            {
                movingCube->directionPoint = 1;
            }
            break;

        default:
            break;
    }
    movingCube->players.clear();
}