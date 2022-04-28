#include <stdio.h>
#include "scene.h"

Scene createScene(MapNode root)
{
    Scene scene;
    return scene;
}

void addPlayerToScene(Scene* scene, Player player)
{
    scene->player = player;
}

void addMapToScene(Scene* scene, MapNode root)
{
    scene->map = root;
}

void drawScene(Scene scene)
{
    drawPlayer(scene.player);
    MapNode actualNode = *findActualMapNode(scene.player, &scene.map);
    for (int i = 0; i < scene.map.nbCubes; i++)
    {
        drawCube(actualNode.tabCubes[i]);
    }
}