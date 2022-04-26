#ifndef SCENE_H
#define SCENE_H

#include "cube.h"
#include "player.h"

#define MAX_CUBE_COUNT 10

typedef struct Scene {
    Player player;
    Cube cubes[MAX_CUBE_COUNT];
    int cubesCount;
} Scene;

Scene createScene();

void addPlayerToScene(Scene* scene, Player player);

void addCubeToScene(Scene* scene, Cube cube);

void drawScene(Scene scene);

#endif