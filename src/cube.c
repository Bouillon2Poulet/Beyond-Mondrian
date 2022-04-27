#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <time.h>
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

void fillRandomTabCube(Cube* tabCube)
{
    for (int i = 0; i<30;i++)
    {
        //Position
        srand(time(NULL)); //init random seed
        int x=(rand() % (3000 - 2000 + 1)) + 200; //random x position between 200 and 3000 px (marging)
        srand(time(NULL)); //init random seed
        int y=(rand() % (3000 - 2000 + 1)) + 200; //random y position between 200 and 3000 px (marging)

        //Size
        srand(time(NULL)); //init random seed
        int width=(rand() % (50 - 20 + 1)) + 20; //random width between 20 and 50 px
        srand(time(NULL)); //init random seed
        int height=(rand() % (50 - 20 + 1)) + 20; //random height between 20 and 50 px

        //Colour
        int filled=1;
        srand(time(NULL)); //init random seed
        float blue=(rand() % (100 - 0 + 1))/100; //random blue value between 0 and 1
        srand(time(NULL)); //init random seed
        float green=(rand() % (100 - 0 + 1))/100; //random green value between 0 and 1
        srand(time(NULL)); //init random seed
        float red=(rand() % (100 - 0 + 1))/100; //random red value between 0 and 1
        
        tabCube[i]=createCube(x,y,width,height,filled,red,green,blue);
    }
}