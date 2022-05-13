#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "line.h"

void drawLine(BackgroundLine line)
{
    if(line.time>=line.endTime)
    {
        line.time=line.endTime;
    }

    glPushMatrix();
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(line.r,line.g,line.b);
        int xA;
        int yA;
        int xB;
        int yB;
        int xC;
        int yC;
        int xD;
        int yD;

        //sens = 1 -> right//up
        //sens = -1 -> left//down

        switch (line.mode)
        {
        case 0: //Horizontal
            xA=line.xStart;
            yA=line.yStart+line.width/2;
            xB=line.xStart;
            yB=line.yStart-line.width/2;
            xC=xB+line.sens*line.time;
            yC=yB;
            xD=xA+line.sens*line.time;
            yD=yA;
            break;
        
        default: //Vertical
            xA=line.xStart-line.width/2;
            yA=line.yStart;
            xB=line.xStart+line.width/2;
            yB=line.yStart;
            xC=xB;
            yC=yB+line.sens*line.time;
            xD=xA;
            yD=yA+line.sens*line.time;
            break;
        }
        glVertex2f(xA,yA);
        glVertex2f(xB,yB);
        glVertex2f(xC,yC);
        glVertex2f(xD,yD);

        glEnd();
    glPopMatrix();
}

BackgroundLine createBackgroundLine(int width, int mode, int sens, int xStart,int yStart, int time, int endTime, float r, float g, float b)
{
    BackgroundLine newLine;
    newLine.width=width;
    newLine.mode=mode;
    newLine.sens=sens,
    newLine.xStart=xStart;
    newLine.yStart=yStart;
    newLine.time=time;
    newLine.endTime=endTime;
    newLine.r=r;
    newLine.g=g;
    newLine.b=b;
    return newLine;
}

void updateBackgroundLine(BackgroundLine* line, Uint32 deltatime)
{
    line->time=deltatime;
}

BackgroundLine randomNewLine()
{
    printf("RandomNewLine\n");
    /*Créer tableau de lignes (10 lignes max à l'écran)
    si random -> random newLignes
    si time=endTime, supprimer ligne';*/

    BackgroundLine randomLine;

    srand(time(NULL)); //init random seed
    //Position
    randomLine.width=(rand() % 5)+5; //random width between 0 and 5
    printf("width:%d\n",randomLine.width);
    randomLine.mode=rand() % 2; //random 
    printf("mode:%d\n",randomLine.mode);
    randomLine.sens=(rand() % 3)-2; //random sens between -1 and 1
    printf("sens:%d\n",randomLine.sens);
    randomLine.xStart=(rand() % 3000)+2000; //random xStart between 2000 and 5000
    randomLine.yStart=(rand() % 3000)+2000; //random xStart between 2000 and 5000
    randomLine.time=(rand() % 3000)+2000; //random xStart between 2000 and 5000
    if (randomLine.mode==0)
    {
        switch (randomLine.sens)
        {
            case -1 : break;
            case 1 : randomLine.xStart*=-1; break;
            default : printf("error sens new random line\n");
        }
    }
    else
    {
        switch(randomLine.sens)
        {
            case -1 : break;
            case 1 : randomLine.yStart*=-1; break;
            default : printf("error sens new random line\n"); 
        }
    }

    randomLine.endTime=(rand() % 7000)+2000; //random endTime between 2000 and 5000
    float colour =(rand() % 1)/2; //random red value between 0 and 1
    randomLine.r=colour;
    randomLine.g=colour;
    randomLine.b=colour;

    return randomLine;
}

void fillSceneLineTab(Scene* scene)
{
    int nbLine = (rand()%10)+30; //between 30 and 40
    for (int i=0;i<nbLine;i++)
    {
        scene->background[i]=randomNewLine();
        printf("scene.background[%d].width : %d\n",i,scene->background->width);
    }
}