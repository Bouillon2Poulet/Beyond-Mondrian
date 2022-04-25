#ifndef CUBE_H
#define CUBE_H

typedef struct Cube {
    float x;
    float y;
    float height;
    float width;
    int filled;
    float red;
    float green;
    float blue;
} Cube;

Cube createCube(float x, float y, float height, float width, int filled, float red, float green, float blue);

void drawCube(Cube cube);

#endif