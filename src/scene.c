#include <GL/gl.h>
#include <GL/glu.h>
#include "scene.h"

void initScene(Scene* scene)
{
    scene->playersCount = 0;
    scene->cubesCount = 0;
    scene->currentPlayerIndex = 0;
    scene->movingCubesCount = 0;
    scene->lineCount = 0;
}

void addPlayerToScene(Scene* scene, Player player, float x, float y)
{
    if (scene->playersCount < MAX_PLAYER_COUNT)
    {
        scene->players[scene->playersCount] = player;
        scene->playersEnd[scene->playersCount] = createCube(x, y, player.cube.width, player.cube.height, 0, player.cube.red, player.cube.green, player.cube.blue, 0);
        scene->playersCount++;
    }
}

void addCubeToScene(Scene* scene, Cube cube)
{
    if (scene->cubesCount < MAX_CUBE_COUNT)
    {
        scene->cubes[scene->cubesCount] = cube;
        scene->cubesCount++;
        scene->quadTree.cubes[scene->quadTree.nbCubes] = cube;
        scene->quadTree.nbCubes = scene->cubesCount;
    }
}

void addMovingCubeToScene(Scene* scene, MovingCube movingCube)
{
    if (scene->cubesCount < MAX_MOVINGCUBE_COUNT)
    {
        scene->movingCubes[scene->movingCubesCount] = movingCube;
        scene->movingCubesCount++;
    }
}

void switchCurrentPlayer(Scene* scene)
{
    if (scene->currentPlayerIndex + 1 < scene->playersCount)
    {
        scene->currentPlayerIndex++;
    }
    else
    {
        scene->currentPlayerIndex = 0;
    }
}

void addQuadTreeToScene(Scene* scene, QuadTree quadTree)
{
    scene->quadTree = quadTree;
}

void drawScene(Scene scene)
{
    for (int i = 0; i < scene.cubesCount; i++)
    {
        drawCube(scene.cubes[i]);
    }

    for (int i = 0; i < scene.movingCubesCount; i++)
    {
        drawCube(scene.movingCubes[i].cube);
    }
    
    for (int i = 0; i < scene.playersCount; i++)
    {
        drawPlayer(scene.players[i]);
        drawCube(scene.playersEnd[i]);
    }

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(scene.players[scene.currentPlayerIndex].cube.x - 2.5, scene.players[scene.currentPlayerIndex].cube.y + scene.players[scene.currentPlayerIndex].cube.height/2 + 5);
    glVertex2f(scene.players[scene.currentPlayerIndex].cube.x + 2.5, scene.players[scene.currentPlayerIndex].cube.y + scene.players[scene.currentPlayerIndex].cube.height/2 + 5);
    glVertex2f(scene.players[scene.currentPlayerIndex].cube.x, scene.players[scene.currentPlayerIndex].cube.y + scene.players[scene.currentPlayerIndex].cube.height/2 + 2.5);
    glEnd();
}

void drawHUD(Scene scene)
{
    glLoadIdentity();
    glScalef(50, 50, 0);
    glTranslatef(19, -10, 0);
    for (int i = scene.playersCount; i > 0; i--)
    {
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(scene.players[scene.playersCount - i].startColors[0], scene.players[scene.playersCount - i].startColors[1], scene.players[scene.playersCount - i].startColors[2]);
        glVertex2f(-0.5 - (i-1), 0.5);
        glVertex2f(0.5 - (i-1), 0.5);
        glVertex2f(0.5 - (i-1), -0.5);
        glVertex2f(-0.5 - (i-1), -0.5);
        glEnd();

        if (scene.playersCount - i == scene.currentPlayerIndex)
        {
            glBegin(GL_TRIANGLE_FAN); //Triangle current player
            glColor3f(0.5, 0.5, 0.5);
            glVertex2f(-0.25 - (i-1), 1);
            glVertex2f(0.25 - (i-1), 1);
            glVertex2f(0 - (i-1), 0.75);
            glEnd();
        }
    }
}

int checkLevelState(Scene scene)
{
    for (int i = 0; i < scene.playersCount; i++)
    {
        if (scene.players[i].cube.red != 1 ||
        scene.players[i].cube.green != 1 ||
        scene.players[i].cube.blue != 1)
        {
            return 0;
        }
    }
    return 1;
}

void checkGravityCollisions(Scene* scene, std::vector<QuadTree*> playerQuadTree)
{
    for (int k = 0; k < scene->movingCubesCount; k++)
    {
        moveCube(&scene->movingCubes[k], scene->players, scene->playersCount);
    }

    for (int j = 0; j < scene->playersCount; j++)
    {
        addGravity(&scene->players[j]);
        checkEndCollision(&scene->players[j], scene->playersEnd[j]);
        findPlayerQuadTree(&scene->quadTree, scene->players[j], playerQuadTree);

        /* Collisions with moving obstacles */

        int temp = 0;

        for (int i = 0; i < scene->movingCubesCount; i++)
        {
            if (checkCollision(scene->players[j], scene->movingCubes[i].cube) == 1)
            {
                temp = 1;
                if (scene->players[j].cube.y > scene->movingCubes[i].cube.y)
                {
                    scene->movingCubes[i].players.push_back(&scene->players[j]);
                    scene->players[j].cube.y = scene->movingCubes[i].cube.y + scene->movingCubes[i].cube.height/2 + scene->players[j].cube.height/2;
                    scene->players[j].isGrounded = 1;
                    scene->players[j].gravity = 0;
                }
                else if (scene->players[j].cube.y < scene->movingCubes[i].cube.y)
                {
                    scene->players[j].cube.y = scene->movingCubes[i].cube.y - scene->movingCubes[i].cube.height/2 - scene->players[j].cube.height/2;
                    scene->players[j].gravity = 0.5;
                    scene->players[j].isGrounded = 0;
                }
                break;
            }
        }
                    
        /* Collisions players */

        if (temp == 0)
        {
            for (int i = 0; i < scene->playersCount; i++)
            {
                if (j != i && checkCollision(scene->players[j], scene->players[i].cube) == 1)
                {
                    temp = 1;
                    if (scene->players[j].cube.y > scene->players[i].cube.y)
                    {
                        scene->players[j].cube.y = scene->players[i].cube.y + scene->players[i].cube.height/2 + scene->players[j].cube.height/2;
                        scene->players[j].isGrounded = 1;
                    }
                    else if (scene->players[j].cube.y < scene->players[i].cube.y)
                    {
                        scene->players[j].cube.y = scene->players[i].cube.y - scene->players[i].cube.height/2 - scene->players[j].cube.height/2;
                        scene->players[i].isGrounded = 1;
                    }
                    scene->players[j].gravity = 0;
                    break;
                }
            }
        }
        
        /* Collisions obstacles */
                    
        if (temp == 0)
        {
            for (auto quadTree : playerQuadTree)
            {
                for (int i = 0; i < quadTree->nbCubes; i++)
                {
                    if (checkCollision(scene->players[j], quadTree->cubes[i]) == 1)
                    {
                        if (quadTree->cubes[i].isSpike == 1)
                        {
                            scene->players[j].cube.x = scene->players[j].startPositions[0];
                            scene->players[j].cube.y = scene->players[j].startPositions[1];
                        }
                        else
                        {
                            temp = 1;
                            if (scene->players[j].cube.y > quadTree->cubes[i].y)
                            {
                                scene->players[j].cube.y = quadTree->cubes[i].y + quadTree->cubes[i].height/2 + scene->players[j].cube.height/2;
                                scene->players[j].isGrounded = 1;
                                scene->players[j].gravity = 0;
                            }
                            else if (scene->players[j].cube.y < quadTree->cubes[i].y)
                            {
                                scene->players[j].cube.y = quadTree->cubes[i].y - quadTree->cubes[i].height/2 - scene->players[j].cube.height/2;
                                scene->players[j].gravity = 0.5;
                            }
                        }
                        break;
                    }
                    scene->players[j].isGrounded = 0;
                }
                if (temp == 1)
                {
                    break;
                }
            }
            playerQuadTree.clear();
        }
    }
}

void checkLeftCollisions(Scene* scene, std::vector<QuadTree*> playerQuadTree)
{
    int temp1 = 0;

    /* Collisions players */

            for (int i = 0; i < scene->playersCount; i++)
            {
                if (scene->currentPlayerIndex != i && checkCollision(scene->players[scene->currentPlayerIndex], scene->players[i].cube) == 1)
                {
                    scene->players[scene->currentPlayerIndex].cube.x = 
                    scene->players[i].cube.x + scene->players[i].cube.width/2 + scene->players[scene->currentPlayerIndex].cube.width/2;
                    break;
                }
            }

            /* Collisions obstacles */

            findPlayerQuadTree(&scene->quadTree, scene->players[scene->currentPlayerIndex], playerQuadTree);

            for (auto quadTree : playerQuadTree)
            {
                for (int i = 0; i < quadTree->nbCubes; i++)
                {
                    if (checkCollision(scene->players[scene->currentPlayerIndex], quadTree->cubes[i]) == 1)
                    {
                        if (quadTree->cubes[i].isSpike == 1)
                        {
                            scene->players[scene->currentPlayerIndex].cube.x = scene->players[scene->currentPlayerIndex].startPositions[0];
                            scene->players[scene->currentPlayerIndex].cube.y = scene->players[scene->currentPlayerIndex].startPositions[1];
                        }
                        else
                        {
                            temp1 = 1;
                            scene->players[scene->currentPlayerIndex].cube.x = 
                            quadTree->cubes[i].x + quadTree->cubes[i].width/2 + scene->players[scene->currentPlayerIndex].cube.width/2;
                            break;
                        }
                    }
                }
                if (temp1 == 1)
                {
                    break;
                }
            }
            playerQuadTree.clear();
}

void checkRightCollisions(Scene* scene, std::vector<QuadTree*> playerQuadTree)
{
    int temp1 = 0;

    /* Collisions players */

    for (int i = 0; i < scene->playersCount; i++)
    {
        if (scene->currentPlayerIndex != i && checkCollision(scene->players[scene->currentPlayerIndex], scene->players[i].cube) == 1)
        {
            scene->players[scene->currentPlayerIndex].cube.x = 
            scene->players[i].cube.x - scene->players[i].cube.width/2 - scene->players[scene->currentPlayerIndex].cube.width/2;
            break;
        }
    }

    /* Collisions obstacles */

    findPlayerQuadTree(&scene->quadTree, scene->players[scene->currentPlayerIndex], playerQuadTree);
    for (auto quadTree : playerQuadTree)
    {
        for (int i = 0; i < quadTree->nbCubes; i++)
        {
            if (checkCollision(scene->players[scene->currentPlayerIndex], quadTree->cubes[i]) == 1)
            {
                if (quadTree->cubes[i].isSpike == 1)
                {
                    scene->players[scene->currentPlayerIndex].cube.x = scene->players[scene->currentPlayerIndex].startPositions[0];
                    scene->players[scene->currentPlayerIndex].cube.y = scene->players[scene->currentPlayerIndex].startPositions[1];
                }
                else
                {
                    temp1 = 1;
                    scene->players[scene->currentPlayerIndex].cube.x = 
                    quadTree->cubes[i].x - quadTree->cubes[i].width/2 - scene->players[scene->currentPlayerIndex].cube.width/2;
                }
                break;
            }
        }
        if (temp1 == 1)
        {
            break;
        }
    }
    playerQuadTree.clear();
}