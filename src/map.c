#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "map.h"

MapNode createMapNode (int width, int height)
{
    MapNode newMapNode;
    newMapNode.width=width;
    newMapNode.height=height;
    newMapNode.nbCubes=0;
    return newMapNode;
}

void buildMapTree (MapNode* mapNode) //Recursive way to build MapTree in 4 steps, take root as first argument
{
    for (int i=0;i<4;i++) //Case : parent
    {
        MapNode* newMapNode = malloc(sizeof(MapNode));
        *newMapNode=createMapNode(mapNode->width/2,mapNode->height/2);
        switch(i)
        {
            case 0 : mapNode->TLMapNode = newMapNode; buildMapTree(mapNode->TLMapNode); break;
            case 1 : mapNode->BLMapNode = newMapNode; buildMapTree(mapNode->BLMapNode); break;
            case 2 : mapNode->TRMapNode = newMapNode; buildMapTree(mapNode->TRMapNode); break;
            case 3 : mapNode->BRMapNode = newMapNode; buildMapTree(mapNode->BRMapNode); break;
        }
    }
    if (mapNode->height==50) //Case : leaf
    {
        return;
    }
}

void addCubeToMapTree (MapNode* mapNode, Cube cube) //Recursive way to add a cube to a leaf, take root as first argument
{
    if (mapNode->TLMapNode!=NULL) //Case : parent
    {
        if(cube.x<=mapNode->width/2) //Case : left side
        {
            if (cube.y<=mapNode->height/2) //Case : top side
            {
                addCubeToMapTree(mapNode->TLMapNode, cube);
            }
            else //Case : bottom side
            {
                addCubeToMapTree(mapNode->BLMapNode, cube);
            }
        }
        else //Case : right side
        {
            if (cube.y<=mapNode->height/2) //Case : top side
            {
                addCubeToMapTree(mapNode->TRMapNode, cube);
            }
            else //Case : bottom side
            {
                addCubeToMapTree(mapNode->BRMapNode, cube);
            }
        }
    }
    else //Case : leaf
    {
        mapNode->tabCubes[mapNode->nbCubes]=cube;
        mapNode->nbCubes++;
    }
}

MapNode findActualMapNode (Player player, MapNode mapNode) //Recursive way to find actual MapNode leaf where the player is, take root as first argument
{
    if (mapNode.TLMapNode!=NULL) //Case : parent
    {
        if(player.cube.x<=mapNode.width/2) //Case : left side
        {
            if (player.cube.y<=mapNode.height/2) //Case : top side
            {
                findActualMapNode(player, *mapNode.TLMapNode);
            }
            else //Case : bottom side
            {
                findActualMapNode(player, *mapNode.BLMapNode);
            }
        }
        else //Case : right side
        {
            if (player.cube.y<=mapNode.height/2) //Case : top side
            {
                findActualMapNode(player, *mapNode.TRMapNode);
            }
            else //Case : bottom side
            {
                findActualMapNode(player, *mapNode.BRMapNode);
            }
        }
    }
    else //Case : leaf
    {
        return mapNode;
    }
}