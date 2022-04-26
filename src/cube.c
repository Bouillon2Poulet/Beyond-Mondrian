#include <GL/gl.h>
#include <GL/glu.h>
#include "cube.h"

Cube createCube(float x, float y, float width, float height, int filled, float red, float green, float blue)
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
        glBegin(GL_LINE_STRIP);
    }

    glColor3f(cube.red, cube.green, cube.blue);

    glVertex2f(cube.x + cube.width/2, cube.y - cube.height/2);
    glVertex2f(cube.x + cube.width/2, cube.y + cube.height/2);
    glVertex2f(cube.x - cube.width/2, cube.y + cube.height/2);
    glVertex2f(cube.x - cube.width/2, cube.y - cube.height/2);

    glEnd();
}