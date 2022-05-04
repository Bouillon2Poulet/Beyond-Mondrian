#include "quadTree.h"
#include "scene.h"

QuadTree createQuadTree(int x, int y, int width, int height)
{
    QuadTree quadTree;
    quadTree.x = x;
    quadTree.y = y;
    quadTree.width = width;
    quadTree.height = height;
    quadTree.cubes = new Cube[MAX_CUBE_COUNT];
    quadTree.nbCubes = 0;
    quadTree.isLeaf = 1;
    return quadTree;
}

void splitQuadTree(QuadTree* quadTree)
{
    quadTree->isLeaf = 0;

    //TOP LEFT
    QuadTree* quadTreeTL = new QuadTree;
    *quadTreeTL = createQuadTree(quadTree->x, quadTree->y, quadTree->width/2, quadTree->height/2);
    quadTree->nodes[0] = quadTreeTL;

    //TOP RIGHT
    QuadTree* quadTreeTR = new QuadTree;
    *quadTreeTR = createQuadTree(quadTree->x + quadTree->width/2, quadTree->y, quadTree->width/2, quadTree->height/2);
    quadTree->nodes[1] = quadTreeTR;

    //BOTTOM LEFT
    QuadTree* quadTreeBL = new QuadTree;
    *quadTreeBL = createQuadTree(quadTree->x, quadTree->y + quadTree->height/2, quadTree->width/2, quadTree->height/2);
    quadTree->nodes[2] = quadTreeBL;

    //BOTTOM RIGHT
    QuadTree* quadTreeBR = new QuadTree;
    *quadTreeBR = createQuadTree(quadTree->x + quadTree->width/2, quadTree->y + quadTree->height/2, quadTree->width/2, quadTree->height/2);
    quadTree->nodes[3] = quadTreeBR;

    for (int i = 0; i < quadTree->nbCubes; i++)
    {
        if (checkQuadTreeCollision(quadTree->cubes[i], *quadTreeTL) == 1)
        {
            quadTreeTL->cubes[quadTreeTL->nbCubes] = quadTree->cubes[i];
            quadTreeTL->nbCubes += 1;
        }
        if (checkQuadTreeCollision(quadTree->cubes[i], *quadTreeTR) == 1)
        {
            quadTreeTR->cubes[quadTreeTR->nbCubes] = quadTree->cubes[i];
            quadTreeTR->nbCubes += 1;
        }
        if (checkQuadTreeCollision(quadTree->cubes[i], *quadTreeBL) == 1)
        {
            quadTreeBL->cubes[quadTreeBL->nbCubes] = quadTree->cubes[i];
            quadTreeBL->nbCubes += 1;
        }
        if (checkQuadTreeCollision(quadTree->cubes[i], *quadTreeBR) == 1)
        {
            quadTreeBR->cubes[quadTreeBR->nbCubes] = quadTree->cubes[i];
            quadTreeBR->nbCubes += 1;
        }
    }

    free(quadTree->cubes);
}

int checkQuadTreeCollision(Cube cube, QuadTree quadTree)
{
    float x = cube.x + 1920/2; //Conversion coordonnées
    float y = 1080/2 - cube.y;
    
    if (x - cube.width/2 <= quadTree.x + quadTree.width &&
    x + cube.width/2 >= quadTree.x &&
    y - cube.height/2 <= quadTree.y + quadTree.height &&
    y + cube.height/2 >= quadTree.y)
    {
        return 1;
    }
    else
    {
        return 0;
    }
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

void findPlayerQuadTree(QuadTree* quadTree, Player player, std::vector<QuadTree*> &playerQuadTree)
{
    if (quadTree->isLeaf == 0)
    {
        if (checkQuadTreeCollision(player.cube, *quadTree->nodes[0]))
        {
            findPlayerQuadTree(quadTree->nodes[0], player, playerQuadTree);
        }
        if (checkQuadTreeCollision(player.cube, *quadTree->nodes[1]))
        {
            findPlayerQuadTree(quadTree->nodes[1], player, playerQuadTree);
        }
        if (checkQuadTreeCollision(player.cube, *quadTree->nodes[2]))
        {
            findPlayerQuadTree(quadTree->nodes[2], player, playerQuadTree);
        }
        if (checkQuadTreeCollision(player.cube, *quadTree->nodes[3]))
        {
            findPlayerQuadTree(quadTree->nodes[3], player, playerQuadTree);
        }
    }
    else
    {
        playerQuadTree.push_back(quadTree);
    }
}

