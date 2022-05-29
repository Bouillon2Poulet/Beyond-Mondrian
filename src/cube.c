#include <GL/gl.h>
#include "cube.h"

Cube createCube(float x, float y, float width, float height, int filled, float red, float green, float blue, int isSpike)
{
    Cube cube;
    cube.x = x;
    cube.y = y;
    cube.width = width;
    cube.height = height;
    cube.filled = filled;
    cube.red = red;
    cube.green = green;
    cube.blue = blue;
    cube.isSpike = isSpike;
    return cube;
}

void drawCube(Cube cube)
{
    if(cube.filled)
    {
        glBegin(GL_TRIANGLE_FAN);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }

    glColor3f(cube.red, cube.green, cube.blue);

    if (cube.isSpike == 0)
    {
        glVertex2f(cube.x + cube.width/2, cube.y - cube.height/2);
        glVertex2f(cube.x + cube.width/2, cube.y + cube.height/2);
        glVertex2f(cube.x - cube.width/2, cube.y + cube.height/2);
        glVertex2f(cube.x - cube.width/2, cube.y - cube.height/2);
    }
    else
    {
        glVertex2f(cube.x - cube.width/2, cube.y - cube.height/2);
        glVertex2f(cube.x + cube.width/2, cube.y - cube.height/2);
        glVertex2f(cube.x, cube.y + cube.height/2);
    }

    glEnd();
}