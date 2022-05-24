#ifndef QUADTREE_H
#define QUADTREE_H

#include <SDL2/SDL.h>
#include <vector>
#include "cube.h"
#include "player.h"

#define MAX_CUBE_COUNT_PER_NODE 4

typedef struct QuadTree {
    float x;
    float y;
    float width;
    float height;
    struct QuadTree* nodes[4];
    Cube* cubes;
    int nbCubes;
    int isLeaf;
} QuadTree;

QuadTree createQuadTree(float x, float y, float width, float height);

void splitQuadTree(QuadTree* quadTree);

int checkQuadTreeCollision(Cube cube, QuadTree quadTree);

void generateQuadTree(QuadTree* quadTree);

void findPlayerQuadTree(QuadTree* quadTree, Player player, std::vector<QuadTree*> &playerQuadTree);

#endif