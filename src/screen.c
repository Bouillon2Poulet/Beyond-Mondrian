#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "cube.h"
#include "lodepng.h"
#include "background.h"

GLuint loadTextureScreen (int indexTexture, Screen screen)
{
    ///SURFACE
    SDL_Surface* surface;
    const char* names[7]={"logo.png","controls.png","rom1.png","antoine.png","mathurin.png","start.png","end.png"};
    
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
        //printf("image chargée !\n");
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


Screen createScreen(int mode)
{
    Screen screen;
    switch (mode)
    {
        case 0 :
            screen.type=0;
            screen.nbTextures = 6; //To change for more textures
            glGenTextures(6, screen.textureTab);
            for (int i=0;i<screen.nbTextures;i++)
            {
                screen.textureTab[i] = loadTextureScreen(i,screen);
            }

            //Lines screen
            screen.tabLines[0]=createBackgroundLine(10,0,1,-2000,250,0,5000,0,0,0); //first horizontal 
            screen.tabLines[1]=createBackgroundLine(10,0,1,-3500,-80,0,8000,0,0,0); //second horizontal
            screen.tabLines[2]=createBackgroundLine(10,1,-1,-98,3000,0,5000,0,0,0); //first vertical
            screen.tabLines[3]=createBackgroundLine(10,1,1,170,-4000,0,4250,0,0,0); //second vertical
            screen.tabLines[4]=createBackgroundLine(10,1,-1, 670,4750,0,4825,0,0,0); //third vertical
            return screen;
            break;
        case 1 :
                screen.type=1;
                screen.nbTextures = 1; //To change for more textures
                glGenTextures(1, screen.textureTab);
                screen.textureTab[0] = loadTextureScreen(6,screen);

                // //Lines screen
                // screen.tabLines[0]=createBackgroundLine(10,0,1,-2000,250,0,5000,0,0,0); //first horizontal 
                // screen.tabLines[1]=createBackgroundLine(10,0,1,-3500,-80,0,8000,0,0,0); //second horizontal
                // screen.tabLines[2]=createBackgroundLine(10,1,-1,-98,3000,0,5000,0,0,0); //first vertical
                // screen.tabLines[3]=createBackgroundLine(10,1,1,170,-4000,0,4250,0,0,0); //second vertical
                // screen.tabLines[4]=createBackgroundLine(10,1,-1, 670,4750,0,4825,0,0,0); //third vertical
                return screen;
    }
    return screen;
}

void drawScreen(Screen* screen)
{
    switch (screen->type)
    {
        case 0:
            drawCube(createCube(0,0,2500,1300,1,1,1,1, 0)); //Background

            //SDL_GetTicks()=90000;
            glPushAttrib(GL_CURRENT_BIT);
            if(SDL_GetTicks()>=3700)
            {
                drawCube(createCube(-600,85,1000,325,1,0,0,1, 0));
                if(SDL_GetTicks()>=4500)
                {
                    drawCube(createCube(35,85,260,320,1,1,0,0, 0));
                    if (SDL_GetTicks()>=4900)
                    {
                        drawCube(createCube(35,-325,260,500,1,1,1,0, 0));
                        if (SDL_GetTicks()>=5500)
                        {
                            drawCube(createCube(853,400,360,300,1,0,0,1, 0)); 
                            if (SDL_GetTicks()>=6600)
                            {
                                drawCube(createCube(853,85,360,320,1,1,0,0, 0));
                            }
                        }
                    }
                }
            }

                for (int i=0;i<5;i++)
                {
                    screen->tabLines[i].time=SDL_GetTicks();
                    drawLine(screen->tabLines[i]);
                }

            
            glPopAttrib();
        
            if (SDL_GetTicks()>=1700)
            {
                displayImage(-520,370,screen->textureTab[0]);//logo.png
                if (SDL_GetTicks()>=4800)
                {
                    displayImage(460,315,screen->textureTab[3]);//antoine.png
                    if (SDL_GetTicks()>=5600)
                    {
                        displayImage(40,180,screen->textureTab[2]);//rom1.png
                        if (SDL_GetTicks()>=5900)
                        {
                            displayImage(440,180,screen->textureTab[4]);//mathurin.png
                            if (SDL_GetTicks()>=7500)
                            {
                                displayImage(610,-300,screen->textureTab[1]);//controls.png
                                if (SDL_GetTicks()>=9000)
                                {
                                    displayImage(-580,-310,screen->textureTab[5]);//start.png
                                }
                            }
                        }
                    }
                }
            }
            break;
        case 1:
            drawCube(createCube(0,0,2500,1300,1,1,1,1, 0)); //Background
            displayImage(0,0,screen->textureTab[0]);//end.png
            break;
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
