#ifndef MOVINGCUBE_H
#define MOVINGCUBE_H

#include "cube.h"

typedef struct MovingCube {
    Cube cube;
    float x1;
    float y1;
    float x2;
    float y2;
    float speed;
    int directionPoint;
} MovingCube;

MovingCube createMovingCube(float x, float y, float height, float width, int filled, float red, float green, float blue, float x1, float y1, float x2, float y2, int directionPoint);

void moveCube(MovingCube* movingCube);

#endif