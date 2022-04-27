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

    //Map properties
    int width;
    int height;
    int nbCubes;
    Cube tabCubes[10]; //10 cubes max. per leaf, 0 for parents
} MapNode;

MapNode createMapNode (int width, int height);
void buildMapTree (MapNode* mapNode);
void addCubeToMapTree (MapNode* mapNode, Cube cube);
MapNode findActualMapNode (Player player, MapNode mapNode); 

#endif