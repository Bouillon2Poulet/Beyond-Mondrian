#ifndef MOVINGCUBE_H
#define MOVINGCUBE_H

#include "cube.h"

typedef struct MovingCube {
    Cube cube;
    float movementSpeed;
    float x1;
    float y1;
    float x2;
    float y2;
    int directionPoint;
} MovingCube;

MovingCube createMovingCube(float x, float y, float width, float height, int filled, float red, float green, float blue, float x1, float y1, float x2, float y2, float movementSpeed, float directionPoint);

#endif