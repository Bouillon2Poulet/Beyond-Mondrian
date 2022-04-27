#include <GL/gl.h>
#include <GL/glu.h>
#include "scene.h"

Scene createScene()
{
    Scene scene;
    scene.playersCount = 0;
    scene.cubesCount = 0;
    scene.currentPlayerIndex = 0;
    return scene;
}

void addPlayerToScene(Scene* scene, Player player)
{
    if (scene->playersCount < MAX_PLAYER_COUNT)
    {
        scene->players[scene->playersCount] = player;
        scene->playersCount++;
    }
}

void addCubeToScene(Scene* scene, Cube cube)
{
    if (scene->cubesCount < MAX_CUBE_COUNT)
    {
        scene->cubes[scene->cubesCount] = cube;
        scene->cubesCount++;
    }
}

void switchCurrentPlayer(Scene* scene)
{
    if (scene->currentPlayerIndex + 1 < MAX_PLAYER_COUNT)
    {
        scene->currentPlayerIndex++;
    }
    else
    {
        scene->currentPlayerIndex = 0;
    }
}

void drawScene(Scene scene)
{
    for (int i = 0; i < scene.cubesCount; i++)
    {
        drawCube(scene.cubes[i]);
    }
    
    for (int i = 0; i < scene.playersCount; i++)
    {
        if (i == scene.currentPlayerIndex)
        {
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(1, 1, 1);
            glVertex2f(scene.players[i].cube.x - 0.2, scene.players[i].cube.y + scene.players[i].cube.height/2 + 0.5);
            glVertex2f(scene.players[i].cube.x + 0.2, scene.players[i].cube.y + scene.players[i].cube.height/2 + 0.5);
            glVertex2f(scene.players[i].cube.x, scene.players[i].cube.y + scene.players[i].cube.height/2 + 0.25);
            glEnd();
        }
        drawPlayer(scene.players[i]);
    }
}