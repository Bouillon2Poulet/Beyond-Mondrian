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
    }
    else //Draw a frame with a stroke
    {
        float innerStroke = 1;

        //Top Line
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cube.x - cube.width/2, cube.y + cube.height/2); //Top Left corner
        glVertex2f(cube.x + cube.width/2, cube.y + cube.height/2); //Top right corner
        glVertex2f(cube.x - cube.width/2 +  innerStroke, cube.y + cube.height/2 - innerStroke); //Inner Top Left corner
 
        glVertex2f(cube.x - cube.width/2 +  innerStroke, cube.y + cube.height/2 - innerStroke); //Inner Top Left corner
        glVertex2f(cube.x + cube.width/2 - innerStroke, cube.y + cube.height/2 - innerStroke); //Inner Top right corner
        glVertex2f(cube.x + cube.width/2, cube.y + cube.height/2); //Top right corner
        glEnd();

        //Left Line
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cube.x - cube.width/2, cube.y + cube.height/2); //Top Left corner
        glVertex2f(cube.x - cube.width/2, cube.y - cube.height/2); //Bot Left corner
        glVertex2f(cube.x - cube.width/2 +  innerStroke, cube.y - cube.height/2 + innerStroke); //Inner Bot Left corner

        glVertex2f(cube.x - cube.width/2 +  innerStroke, cube.y - cube.height/2 + innerStroke); //Inner Bot Left corner
        glVertex2f(cube.x - cube.width/2 +  innerStroke, cube.y + cube.height/2 - innerStroke); //Inner Top Left corner
        glVertex2f(cube.x - cube.width/2, cube.y + cube.height/2); //Top Left corner  
        glEnd(); 

        //Bot Line
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cube.x - cube.width/2, cube.y - cube.height/2); //Bot Left corner
        glVertex2f(cube.x + cube.width/2, cube.y - cube.height/2); //Bot right corner
        glVertex2f(cube.x + cube.width/2 -  innerStroke, cube.y - cube.height/2 + innerStroke); //Inner Bot Right corner

        glVertex2f(cube.x + cube.width/2 -  innerStroke, cube.y - cube.height/2 + innerStroke); //Inner Bot Right corner
        glVertex2f(cube.x - cube.width/2 +  innerStroke, cube.y - cube.height/2 + innerStroke); //Inner Bot Left corner
        glVertex2f(cube.x - cube.width/2, cube.y - cube.height/2); //Bot Left corner
        glEnd();

        //Right Line
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cube.x + cube.width/2, cube.y - cube.height/2); //Bot right corner
        glVertex2f(cube.x + cube.width/2, cube.y + cube.height/2); //Top right corner
        glVertex2f(cube.x + cube.width/2 - innerStroke, cube.y + cube.height/2 - innerStroke); //Inner Top right corner

        glVertex2f(cube.x + cube.width/2 - innerStroke, cube.y + cube.height/2 - innerStroke); //Inner Top right corner
        glVertex2f(cube.x + cube.width/2 -  innerStroke, cube.y - cube.height/2 + innerStroke); //Inner Bot Right corner
        glVertex2f(cube.x + cube.width/2, cube.y - cube.height/2); //Bot right corner
        glEnd();
    }
    glEnd();
}