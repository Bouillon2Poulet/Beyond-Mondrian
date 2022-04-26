#include "scene.h"

Scene createScene()
{
    Scene scene;
    scene.cubesCount = 0;
    return scene;
}

void addPlayerToScene(Scene* scene, Player player)
{
    scene->player = player;
}

void addCubeToScene(Scene* scene, Cube cube)
{
    if (scene->cubesCount < 10)
    {
        scene->cubes[scene->cubesCount] = cube;
        scene->cubesCount++;
    }
}

void drawScene(Scene scene)
{
    drawPlayer(scene.player);
    for (int i = 0; i < scene.cubesCount; i++)
    {
        drawCube(scene.cubes[i]);
    }
}