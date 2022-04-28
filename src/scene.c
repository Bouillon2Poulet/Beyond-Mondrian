#include <stdio.h>
#include "scene.h"

Scene createScene()
{
    Scene scene;
    MapNode root;
    return scene;
}

void addPlayerToScene(Scene* scene, Player player)
{
    scene->player = player;
}

/*
void addCubeToScene(Scene* scene, Cube cube)
{
    if (scene->cubesCount < 10)
    {
        scene->cubes[scene->cubesCount] = cube;
        scene->cubesCount++;
    }
}
*/

void drawScene(Scene scene)
{
    drawPlayer(scene.player);
    MapNode actualNode = *findActualMapNode(scene.player, &scene.map);
    printf("actualNode[0].x : %f",actualNode.tabCubes[0].x);
    for (int i = 0; i < actualNode.nbCubes; i++)
    {
        drawCube(actualNode.tabCubes[i]);
    }
}