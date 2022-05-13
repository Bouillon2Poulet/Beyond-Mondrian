#include "movingCube.h"

MovingCube createMovingCube(float x, float y, float width, float height, int filled, float red, float green, float blue, float x1, float y1, float x2, float y2, float movementSpeed, float directionPoint)
{
    MovingCube movingCube;
    movingCube.cube = createCube(x, y, width, height, filled, red, green, blue);
    movingCube.x1 = x1;
    movingCube.y1 = y1;
    movingCube.x2 = x2;
    movingCube.y2 = y2;
    movingCube.movementSpeed = 0.05;
    movingCube.directionPoint = 1;
    return movingCube;
}