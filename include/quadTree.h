#ifndef QUADTREE_H
#define QUADTREE_H

#include <SDL2/SDL.h>
#include "cube.h"
#include "player.h"

#define MAX_CUBE_COUNT_PER_NODE 4

typedef struct QuadTree {
    SDL_Rect bbox;
    struct QuadTree* nodes[4];
    Cube* cubes;
    int nbCubes;
    int isLeaf;
} QuadTree;

QuadTree createQuadTree(int x, int y, int width, int height);

void splitQuadTree(QuadTree* quadTree);

void generateQuadTree(QuadTree* quadTree);

QuadTree* findPlayerQuadTree(QuadTree* quadTree, Player player);

#endif