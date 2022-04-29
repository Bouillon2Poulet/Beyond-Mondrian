#include "quadTree.h"
#include "scene.h"

QuadTree createQuadTree(int x, int y, int width, int height)
{
    QuadTree quadTree;
    quadTree.bbox.x = x;
    quadTree.bbox.y = y;
    quadTree.bbox.w = width;
    quadTree.bbox.h = height;
    quadTree.cubes = malloc(sizeof(Cube) * MAX_CUBE_COUNT);
    quadTree.nbCubes = 0;
    quadTree.isLeaf = 1;
    return quadTree;
}

void splitQuadTree(QuadTree* quadTree)
{
    quadTree->isLeaf = 0;

    //TOP LEFT
    QuadTree* quadTreeTL = malloc(sizeof(QuadTree));
    *quadTreeTL = createQuadTree(quadTree->bbox.x, quadTree->bbox.y, quadTree->bbox.w/2, quadTree->bbox.h/2);
    quadTree->nodes[0] = quadTreeTL;

    //TOP RIGHT
    QuadTree* quadTreeTR = malloc(sizeof(QuadTree));
    *quadTreeTR = createQuadTree(quadTree->bbox.x + quadTree->bbox.w/2, quadTree->bbox.y, quadTree->bbox.w/2, quadTree->bbox.h/2);
    quadTree->nodes[1] = quadTreeTR;

    //BOTTOM LEFT
    QuadTree* quadTreeBL = malloc(sizeof(QuadTree));
    *quadTreeBL = createQuadTree(quadTree->bbox.x, quadTree->bbox.y + quadTree->bbox.h/2, quadTree->bbox.w/2, quadTree->bbox.h/2);
    quadTree->nodes[2] = quadTreeBL;

    //BOTTOM RIGHT
    QuadTree* quadTreeBR = malloc(sizeof(QuadTree));
    *quadTreeBR = createQuadTree(quadTree->bbox.x + quadTree->bbox.w/2, quadTree->bbox.y + quadTree->bbox.h/2, quadTree->bbox.w/2, quadTree->bbox.h/2);
    quadTree->nodes[3] = quadTreeBR;

    for (int i = 0; i < quadTree->nbCubes; i++)
    {
        float x = quadTree->cubes[i].x + quadTree->bbox.w/2;
        float y = quadTree->bbox.h/2 - quadTree->cubes[i].y;

        if (x <= quadTree->bbox.x + quadTree->bbox.w/2 && y <= quadTree->bbox.y + quadTree->bbox.h/2)
        {
            quadTreeTL->cubes[quadTreeTL->nbCubes] = quadTree->cubes[i];
            quadTreeTL->nbCubes += 1;
        }
        if (x >= quadTree->bbox.x + quadTree->bbox.w/2 && y <= quadTree->bbox.y + quadTree->bbox.h/2)
        {
            quadTreeTR->cubes[quadTreeTR->nbCubes] = quadTree->cubes[i];
            quadTreeTR->nbCubes += 1;
        }
        if (x <= quadTree->bbox.x + quadTree->bbox.w/2 && y >= quadTree->bbox.y + quadTree->bbox.h/2)
        {
            quadTreeBL->cubes[quadTreeBL->nbCubes] = quadTree->cubes[i];
            quadTreeBL->nbCubes += 1;
        }
        if (x >= quadTree->bbox.x + quadTree->bbox.w/2 && y >= quadTree->bbox.y + quadTree->bbox.h/2)
        {
            quadTreeBR->cubes[quadTreeBR->nbCubes] = quadTree->cubes[i];
            quadTreeBR->nbCubes += 1;
        }
    }

    free(quadTree->cubes);
}

void generateQuadTree(QuadTree* quadTree)
{
    if (quadTree->nbCubes > MAX_CUBE_COUNT_PER_NODE)
    {
        splitQuadTree(quadTree);
        for (int i = 0; i < 4; i++)
        {
            generateQuadTree(quadTree->nodes[i]);
        }
    }
}

QuadTree* findPlayerQuadTree(QuadTree* quadTree, Player player)
{
    if (quadTree->isLeaf == 0)
    {
        float x = player.cube.x + quadTree->bbox.w/2;
        float y = quadTree->bbox.h/2 - player.cube.y;

        if (x < quadTree->bbox.x + quadTree->bbox.w/2 && y < quadTree->bbox.y + quadTree->bbox.h/2)
        {
            return findPlayerQuadTree(quadTree->nodes[0], player);
        }
        else if (x > quadTree->bbox.x + quadTree->bbox.w/2 && y < quadTree->bbox.y + quadTree->bbox.h/2)
        {
            return findPlayerQuadTree(quadTree->nodes[1], player);
        }
        else if (x < quadTree->bbox.x + quadTree->bbox.w/2 && y > quadTree->bbox.y + quadTree->bbox.h/2)
        {
            return findPlayerQuadTree(quadTree->nodes[2], player);
        }
        else
        {
            return findPlayerQuadTree(quadTree->nodes[3], player);
        }
    }
    else
    {
        return quadTree;
    }
}