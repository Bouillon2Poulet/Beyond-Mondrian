#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
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
    srand(time(NULL)); //init random seed
    for (int i = 0; i<30;i++)
    {
        //Position
        int x=(rand() % 3000)-1500; //random x position between -1500 and 1500 px (marging)
        int y=(rand() % 3000)-1500; //random x position between -1500 and 1500 px (marging)

        //Size
        int width=(rand() % (50 - 20 + 1)) + 20; //random width between 20 and 50 px
        int height=(rand() % (50 - 20 + 1)) + 20; //random height between 20 and 50 px

        //Colour
        int filled=1;
        float blue=(rand() % (100 - 0 + 1))/100; //random blue value between 0 and 1
        float green=(rand() % (100 - 0 + 1))/100; //random green value between 0 and 1
        float red=(rand() % (100 - 0 + 1))/100; //random red value between 0 and 1
        
        printf("\nCube n°%d\n",i+1);
        printf("newCube.x : %d\n",x);
        printf("newCube.y : %d\n",y);
        tabCube[i]=createCube(x,y,width,height,filled,red,green,blue);
    }
}