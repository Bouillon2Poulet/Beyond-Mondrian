#ifndef CUBE_H
#define CUBE_H

typedef struct Cube {
    float x;
    float y;
    float width;
    float height;
    int filled;
    float red;
    float green;
    float blue;
    int isSpike;
} Cube;

Cube createCube(float x, float y, float width, float height, int filled, float red, float green, float blue, int isSpike);

void drawCube(Cube cube);

#endif