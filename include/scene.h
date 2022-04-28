#ifndef SCENE_H
#define SCENE_H

#include "cube.h"
#include "player.h"
#include "map.h"

#define MAX_CUBE_COUNT 10

typedef struct Scene {
    Player player;
    MapNode map; //MapTree root;
} Scene;

Scene createScene();

void addPlayerToScene(Scene* scene, Player player);
void addMapToScene(Scene* scene, MapNode root);

void addCubeToScene(Scene* scene, Cube cube);

void drawScene(Scene scene);

#endif