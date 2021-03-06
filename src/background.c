#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "background.h"

void drawLine(BackgroundLine line)
{
    if (line.time>=line.endTime)
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

void updateBackgroundLine(BackgroundLine* line)
{
    line->time+=line->speedFactor;
}

BackgroundLine randomNewLine()
{
    BackgroundLine randomLine;

    srand(time(NULL)); //init random seed
    //Position
    randomLine.width=(rand() % 5)+15; //random width between 15 and 20
    randomLine.speedFactor=(rand()%3)+2; //random speedFactor between 2 and 5
    randomLine.xStart=1000;
    randomLine.yStart=800;

    randomLine.sens=0;
    while (randomLine.sens!=-1 && randomLine.sens!=1)
    {
        randomLine.sens=(rand() % 4)-2; //random sens between -1 and 1
    }

    randomLine.mode=rand() % 2; //random mode
    if (randomLine.mode==0)
    {
        randomLine.yStart=(rand() % 1080)-540; //random xStart between -540 and +540
        switch (randomLine.sens)
        {
            case -1 : break;
            case 1 : randomLine.xStart*=-1; break;
            default : printf("error sens new random line\n");
        }
    }
    else
    {
        randomLine.xStart=(rand() % 1920)-960; //random xStart between -960 and 960
        switch(randomLine.sens)
        {
            case -1 : break;
            case 1 : randomLine.yStart*=-1; break;
            default : printf("error sens new random line\n"); 
        }
    }

    randomLine.time=0;
    randomLine.endTime=(rand() % 3000)+7000; //random endTime between 7000 and 10000
    
    int a = (rand() % 20) + 85; //random grey between 0.85 et 0.95
    float b = a;
    float colour =b/100;
    randomLine.r=colour;
    randomLine.g=colour;
    randomLine.b=colour;

    return randomLine;
}

void addRandomLineToScene (Scene* scene)
{
    scene->background[scene->lineCount] = randomNewLine();
    scene->lineCount++;
}

void displayLineInfo (BackgroundLine line)
{
    printf("\n//Line//\n");
    printf("-width:%d\n",line.width);
    printf("-time:%d\n",line.time);
    printf("-endTime:%d\n",line.endTime);
    printf("-speedFactor:%d\n",line.speedFactor);
    printf("-rvb:%f,%f,%f\n",line.r,line.g,line.b);
}

void displayBackground(Scene* scene, Uint32 currentTime, int gameState)
{
    glPushMatrix(); //Background
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.97,0.97,0.97);
        glVertex2f(-1920,1080);
        glVertex2f(1920,1080);
        glVertex2f(1920,-1080);
        glVertex2f(-1920,-1080);
        glEnd();
    glPopMatrix();

    int nbLinesMax= 20;
    int count=scene->lineCount;
    if(scene->lineCount>=nbLinesMax)
    {
        count = 20;
    }

    int start=scene->lineCount%nbLinesMax;
    int loop=(scene->lineCount/nbLinesMax)-1;
    if(currentTime%60==0 && gameState!=0) //Each 60 frames
    {
        if(scene->lineCount>=nbLinesMax) //If more than 20 lines, restart from first
        {
            scene->background[scene->lineCount]=randomNewLine();
            scene->lineCount++;
            count=20;
        }
        else
        {
            scene->background[scene->lineCount]=randomNewLine();
            scene->lineCount++;
        }
    }
    
    for (int i=start+loop*nbLinesMax;i<start+loop*nbLinesMax+count;i++)
        {
            updateBackgroundLine(&scene->background[i]);
            drawLine(scene->background[i]);
        }  
}
