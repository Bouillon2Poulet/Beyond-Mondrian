#ifndef SCENE_H
#define SCENE_H

#include "background.h"
#include "cube.h"
#include "movingCube.h"
#include "player.h"
#include "quadTree.h"

#define MAX_PLAYER_COUNT 10
#define MAX_MOVINGCUBE_COUNT 10
#define MAX_CUBE_COUNT 100


typedef struct Scene {
    Player players[MAX_PLAYER_COUNT];
    Cube playersEnd[MAX_PLAYER_COUNT];
    Cube cubes[MAX_CUBE_COUNT];
    MovingCube movingCubes[MAX_MOVINGCUBE_COUNT];
    int playersCount;
    int cubesCount;
    int movingCubesCount;
    int currentPlayerIndex;
    QuadTree quadTree;
    BackgroundLine background[500]; //500 lines max
    int lineCount;
} Scene;

void initScene(Scene* scene);

void addPlayerToScene(Scene* scene, Player player, float x, float y);

void addCubeToScene(Scene* scene, Cube cube);

void addMovingCubeToScene(Scene* scene, MovingCube movingCube);

void switchCurrentPlayer(Scene* scene);

void addQuadTreeToScene(Scene* scene, QuadTree quadTree);

void drawScene(Scene scene);

void drawHUD(Scene scene);

int checkLevelState(Scene scene);

void checkGravityCollisions(Scene* scene, std::vector<QuadTree*> playerQuadTree);

void checkLeftCollisions(Scene* scene, std::vector<QuadTree*> playerQuadTree);

void checkRightCollisions(Scene* scene, std::vector<QuadTree*> playerQuadTree);

#endif