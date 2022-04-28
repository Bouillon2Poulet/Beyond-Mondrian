#ifndef MAP_H
#define MAP_H
#include "cube.h"
#include "player.h"

typedef struct MapNode{
    //Children
    struct MapNode* TLMapNode; //Top Left
    struct MapNode* BLMapNode; //Bottom Left
    struct MapNode* TRMapNode; //Top Right
    struct MapNode* BRMapNode; //Bottom Right
    int hasChildren; //1 if parent

    //Map properties
    char name[300];
    int leftSide;
    int rightSide;
    int topSide;
    int botSide;

    //Cubes
    int nbCubes;
    Cube tabCubes[4]; //4 cubes max per leaf;
} MapNode;

MapNode createMapNode (char* name, int left, int right, int top, int bot);
void splitIntoFourChildren (MapNode* mapNode);
void addCubeToMapTree (MapNode* mapNode, Cube cube);
MapNode* findActualMapNode (Player player, MapNode* mapNode);

#endif  