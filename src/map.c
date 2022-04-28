#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "map.h"

MapNode createMapNode (int left, int right, int top, int bot)
{
    MapNode newMapNode;
    newMapNode.leftSide=left;
    newMapNode.rightSide=right;
    newMapNode.topSide=top;
    newMapNode.botSide=bot;
    newMapNode.nbCubes=0;
    newMapNode.hasChildren=0;
    return newMapNode;
}
void splitIntoFourChildren (MapNode* mapNode) //Add 4 children to a parent mapNode and split its cubes.
{
    //Create 4 children :
    MapNode* TLChildren = malloc(sizeof(MapNode));
    *TLChildren=createMapNode(mapNode->leftSide,(mapNode->rightSide-mapNode->leftSide)/2,mapNode->topSide,(mapNode->topSide-mapNode->botSide)/2);
    mapNode->TLMapNode=TLChildren;
    MapNode* BLChildren = malloc(sizeof(MapNode));
    *BLChildren=createMapNode(mapNode->leftSide,(mapNode->rightSide-mapNode->leftSide)/2,(mapNode->topSide-mapNode->botSide)/2,mapNode->botSide);
    mapNode->BLMapNode=BLChildren;
    MapNode* TRChildren = malloc(sizeof(MapNode));
    *TRChildren=createMapNode((mapNode->rightSide-mapNode->leftSide)/2,mapNode->rightSide,mapNode->topSide,(mapNode->topSide-mapNode->botSide)/2);
    mapNode->TRMapNode=TRChildren;
    MapNode* BRChildren = malloc(sizeof(MapNode));
    *BRChildren=createMapNode((mapNode->rightSide-mapNode->leftSide)/2,mapNode->rightSide,(mapNode->topSide-mapNode->botSide)/2,mapNode->botSide);
    mapNode->BRMapNode=BRChildren;

    //Fill 4 children with parent's cubes
    for (int i=0;i<4;i++)
    {
        printf("filling children\n");
        printf("tabCubes[%d].x : %f\n",i,mapNode->tabCubes[i].x);
        printf("tabCubes[%d].y : %f\n",i,mapNode->tabCubes[i].y);

        printf("mapNode.leftSide : %d\n",mapNode->leftSide);
        printf("mapNode.rightSide : %d\n",mapNode->rightSide);
        printf("mapNode.topSide : %d\n",mapNode->topSide);
        printf("mapNode.botSide : %d\n",mapNode->botSide);

        if(mapNode->tabCubes[i].x<=(mapNode->rightSide+mapNode->leftSide)/2) //Case : left side
        {
            printf("%f est inferieur à %d\n",mapNode->tabCubes[i].x,(mapNode->rightSide-mapNode->leftSide)/2);
            if (mapNode->tabCubes[i].y>=(mapNode->botSide+mapNode->topSide)/2) //Case : top side
            {
                mapNode->TLMapNode->tabCubes[mapNode->TLMapNode->nbCubes]=mapNode->tabCubes[i];
                mapNode->TLMapNode->nbCubes++;
                printf("TLChildren.nbCubes :%d\n",mapNode->TLMapNode->nbCubes);
            }
            else //Case : bottom side
            {
                mapNode->BLMapNode->tabCubes[mapNode->BLMapNode->nbCubes]=mapNode->tabCubes[i];
                mapNode->BLMapNode->nbCubes++;
                printf("BLChildren.nbCubes :%d\n",mapNode->BLMapNode->nbCubes);
            }
        }
        else //Case : right side
        {
            if (mapNode->tabCubes[i].y>=(mapNode->botSide+mapNode->topSide)/2) //Case : top side
            {
                mapNode->TRMapNode->tabCubes[mapNode->TRMapNode->nbCubes]=mapNode->tabCubes[i];
                mapNode->TRMapNode->nbCubes++;
                printf("TRChildren.nbCubes :%d\n",mapNode->TRMapNode->nbCubes);
            }
            else //Case : bottom side
            {
                mapNode->BRMapNode->tabCubes[mapNode->BRMapNode->nbCubes]=mapNode->tabCubes[i];
                mapNode->BRMapNode->nbCubes++;
                printf("BRChildren.nbCubes :%d\n",mapNode->BRMapNode->nbCubes);
            }
        }
    //Remove current cube from parent's tab
    mapNode->tabCubes[i]=createCube(0,0,0,0,0,0,0,0);
    }
}

void addCubeToMapTree (MapNode* mapNode, Cube cube) //Recursive way to add a cube to a leaf, take root as first argument
{
    printf("nbCube before adding=%d\n",mapNode->nbCubes);
    printf("mapNode->hasChildren :%d \n",mapNode->hasChildren);
    if (mapNode->nbCubes>=4) //Case parent
    {
        if (mapNode->hasChildren==0) //If no children
        {
            printf("Going to be splitted\n");
            mapNode->hasChildren=1;
            printf("Avant split mapNode.tabCubes[0].x : %f",mapNode->tabCubes[0].x);
            splitIntoFourChildren(mapNode); //Then add 4 children and split its cubes
            /*int a;
            fflush( stdout );
            scanf("%d\n",&a);
            fgetc( stdin );*/
        }
        printf("mapNode has children\n");
        //Put new cube in the correct children
        if(cube.x<=(mapNode->rightSide+mapNode->leftSide)/2) //Case : left side
        {
            if (cube.y<=(mapNode->botSide+mapNode->topSide)/2) //Case : top side
            {
                printf("adding cube to TLChildren\n");
                addCubeToMapTree(mapNode->TLMapNode,cube);
            }
            else //Case : bottom side
            {
                printf("adding cube to BLChildren\n");
                addCubeToMapTree(mapNode->BLMapNode,cube);
            }
        }       
        else //Case : right side
        {
            if (cube.y<=(mapNode->botSide+mapNode->topSide)/2) //Case : top side
            {
                printf("adding cube to TRChildren\n");
                addCubeToMapTree(mapNode->TRMapNode,cube);
            }
            else //Case : bottom side
            {
                printf("adding cube to BRChildren\n");
                addCubeToMapTree(mapNode->BRMapNode,cube);
            }
        } 
    }

    else //No subdivide
    {
        printf("Cube added !\n");
        mapNode->tabCubes[mapNode->nbCubes]=cube;
        mapNode->nbCubes++;
        printf("cube.x : %f, cube.y : %f\n",mapNode->tabCubes[mapNode->nbCubes].x,mapNode->tabCubes[mapNode->nbCubes].y);
        return;
    }
}

MapNode* findActualMapNode (Player player, MapNode* mapNode) //Recursive way to find actual MapNode leaf where the player is, take root as first argument
{
    if (mapNode->hasChildren==1) //Case : parent
    {
        if(player.cube.x<(mapNode->rightSide+mapNode->leftSide)/2) //Case : left side
        {
            if (player.cube.y>=(mapNode->botSide+mapNode->topSide)/2) //Case : top side
            {
                findActualMapNode(player, mapNode->TLMapNode);
            }
            else //Case : bottom side
            {
                findActualMapNode(player, mapNode->BLMapNode);
            }
        }
        else //Case : right side
        {
            if (player.cube.y>=(mapNode->botSide+mapNode->topSide)/2)//Case : top side
            {
                findActualMapNode(player, mapNode->TRMapNode);
            }
            else //Case : bottom side
            {
                findActualMapNode(player, mapNode->BRMapNode);
            }
        }
    }
    else //Case : leaf
    {
        return mapNode;
    }
}