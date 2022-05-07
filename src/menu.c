#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "menu.h"
#include "cube.h"
#include "lodepng.h"

GLuint loadTextureStartMenu (int indexTexture, StartMenu menu)
{
    ///SURFACE
    SDL_Surface* surface;
    const char* names[6]={"logo.png","controls.png","rom1.png","antoine.png","mathurin.png","start.png"};
    
    ///TEXTURE
    GLuint texture;
    glGenTextures(1, &texture);
    char fileName[150];
    sprintf(fileName,"assets/textImage/%s",names[indexTexture]);
    surface = IMG_Load(fileName);
    if (surface==NULL)
    {
        printf("image non chargée !\n");
    }
    else
    {
        printf("image chargée !\n");
    }

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    ///GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return texture;
}

SDL_Surface* IMG_Load(const char* filename) {
	unsigned char* image;
	unsigned w, h;
	unsigned error = lodepng_decode32_file(&image, &w, &h, filename);
	if(error) {
		printf("decoder error %u: %s\n", error, lodepng_error_text(error));
		return 0;
	}
	unsigned rmask = 0xff000000;
	unsigned gmask = 0x00ff0000;
	unsigned bmask = 0x0000ff00;
	unsigned amask = 0x000000ff;
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(image, w, h, 32, 4*w, rmask, gmask, bmask, amask);
	return surface;
}

//Display lists
GLuint drawCase(int w, int h)
{
    GLuint id = glGenLists(1);
    glNewList(id, GL_COMPILE); //Logo.png : 0
        glBegin(GL_QUADS);
            glTexCoord2f(0,1);
            glVertex2f(-w/2, -h/2);
            glTexCoord2f(1,1);
            glVertex2f(w/2, -h/2);
            glTexCoord2f(1,0);
            glVertex2f(w/2, h/2);
            glTexCoord2f(0,0);
            glVertex2f(-w/2, h/2);
        glEnd();  
    glEndList();
    return id;
}


StartMenu createStartMenu()
{
    StartMenu menu;
    menu.nbTextures = 6; //To change for more textures
    menu.deltaTime=0;
    glGenTextures(6, menu.textureTab);
    for (int i=0;i<menu.nbTextures;i++)
    {
        menu.textureTab[i] = loadTextureStartMenu(i,menu);
    }
    return menu;
}

void updateMenu(StartMenu* menu, Uint32 deltaTime)
{
    menu->deltaTime=deltaTime;
}

void drawMenu(StartMenu menu)
{
    drawCube(createCube(0,0,2500,1300,1,1,1,1)); //Background

    //menu.deltaTime=90000;
    glPushAttrib(GL_CURRENT_BIT);
    if(menu.deltaTime>=3700)
    {
        drawCube(createCube(-600,85,1000,325,1,0,0,1));
        if(menu.deltaTime>=4500)
        {
            drawCube(createCube(35,85,260,320,1,1,0,0));
            if (menu.deltaTime>=4900)
            {
                drawCube(createCube(35,-325,260,500,1,1,1,0));
                if (menu.deltaTime>=5500)
                {
                    drawCube(createCube(853,400,360,300,1,0,0,1)); 
                    if (menu.deltaTime>=6600)
                    {
                        drawCube(createCube(853,85,360,320,1,1,0,0));
                    }
                }
            }
        }
    }
        drawLine(10,0,1,-2000,250,menu.deltaTime,5000); //first horizontal
        drawLine(10,0,1,-3500,-80,menu.deltaTime,8000); //second horizontal
        drawLine(10,1,-1,-98,3000,menu.deltaTime,5000); //first vertical
        drawLine(10,1,1,170,-4000,menu.deltaTime,4250); //second vertical
        drawLine(10,1,-1, 670,4750,menu.deltaTime,4825); //third vertical
    glPopAttrib();
  
    if (menu.deltaTime>=1700)
    {
        displayImage(-520,370,menu.textureTab[0]);//logo.png
        if (menu.deltaTime>=4800)
        {
            displayImage(190,315,menu.textureTab[3]);//antoine.png
            if (menu.deltaTime>=5600)
            {
                displayImage(40,180,menu.textureTab[2]);//rom1.png
                if (menu.deltaTime>=5900)
                {
                    displayImage(440,180,menu.textureTab[4]);//mathurin.png
                    if (menu.deltaTime>=7500)
                    {
                        displayImage(610,-300,menu.textureTab[1]);//controls.png
                        if (menu.deltaTime>=9000)
                        {
                            displayImage(-580,-310,menu.textureTab[5]);//start.png
                        }
                    }
                }
            }
        }
    }
}

void displayImage(int x, int y, GLuint texture) //Display an image from center of screen
{
    int caseID;
    int w,h;
    glPushMatrix();
    glTranslatef(x,y,0);
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w); //Get texture width -> w
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
            caseID = drawCase(w,h);
            glCallList(caseID);
        glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void drawLine(int width, int mode, int sens, int xStart,int yStart, int time, int endTime)
{
    if(time>=endTime)
    {
        time=endTime;
    }
    glPushMatrix();
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0,0,0);
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

        switch (mode)
        {
        case 0: //Horizontal
            xA=xStart;
            yA=yStart+width/2;
            xB=xStart;
            yB=yStart-width/2;
            xC=xB+sens*time;
            yC=yB;
            xD=xA+sens*time;
            yD=yA;
            break;
        
        default: //Vertical
            xA=xStart-width/2;
            yA=yStart;
            xB=xStart+width/2;
            yB=yStart;
            xC=xB;
            yC=yB+sens*time;
            xD=xA;
            yD=yA+sens*time;
            break;
        }
        glVertex2f(xA,yA);
        glVertex2f(xB,yB);
        glVertex2f(xC,yC);
        glVertex2f(xD,yD);

        glEnd();
    glPopMatrix();
}