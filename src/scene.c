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

void addPlayerToScene(Scene* scene, Player player, float x, float y)
{
    if (scene->playersCount < MAX_PLAYER_COUNT)
    {
        scene->players[scene->playersCount] = player;
        scene->playersEnd[scene->playersCount] = createCube(x, y, player.cube.width, player.cube.height, 0, 1, 1, 1);
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
    scene->quadTree.cubes[scene->quadTree.nbCubes] = cube;
    scene->quadTree.nbCubes = scene->cubesCount;
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
    
    for (int i = 0; i < scene.playersCount; i++)
    {
        drawPlayer(scene.players[i]);
        drawCube(scene.playersEnd[i]);
    }

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1, 1, 1);
    glVertex2f(scene.players[scene.currentPlayerIndex].cube.x - 0.25, scene.players[scene.currentPlayerIndex].cube.y + scene.players[scene.currentPlayerIndex].cube.height/2 + 0.5);
    glVertex2f(scene.players[scene.currentPlayerIndex].cube.x + 0.25, scene.players[scene.currentPlayerIndex].cube.y + scene.players[scene.currentPlayerIndex].cube.height/2 + 0.5);
    glVertex2f(scene.players[scene.currentPlayerIndex].cube.x, scene.players[scene.currentPlayerIndex].cube.y + scene.players[scene.currentPlayerIndex].cube.height/2 + 0.25);
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
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(1, 1, 1);
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