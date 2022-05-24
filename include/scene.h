#ifndef SCENE_H
#define SCENE_H

#include "line.h"
#include "cube.h"
#include "player.h"
#include "quadTree.h"

#define MAX_PLAYER_COUNT 10
#define MAX_CUBE_COUNT 100

typedef struct Scene {
    Player players[MAX_PLAYER_COUNT];
    Cube playersEnd[MAX_PLAYER_COUNT];
    Cube cubes[MAX_CUBE_COUNT];
    int playersCount;
    int cubesCount;
    int currentPlayerIndex;
    QuadTree quadTree;
    BackgroundLine background[20]; //20 lines max
    int lineCount;
} Scene;

void initScene(Scene* scene);

void addPlayerToScene(Scene* scene, Player player, float x, float y);

void addCubeToScene(Scene* scene, Cube cube);

void switchCurrentPlayer(Scene* scene);

void addQuadTreeToScene(Scene* scene, QuadTree quadTree);

void drawScene(Scene scene);

void drawHUD(Scene scene);

int checkLevelState(Scene scene);

#endif