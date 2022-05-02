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
    char* names[2]={"logo.png","textStartMenu.png"};
    
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
    menu.nbTextures = 2; //To change for more textures
    menu.deltaTime=0;
    glGenTextures(10, menu.textureTab);
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
    int caseID;
    int w,h;
    drawCube(createCube(0,0,1920,1080,1,1,1,1)); //Background

    glPushMatrix();
        glTranslatef(-250,0,0);
        glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, menu.textureTab[0]);
                glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w); //Get texture width -> w
                glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
                caseID = drawCase(w,h);
                glCallList(caseID);
            glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(300,0,0);
        glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, menu.textureTab[1]);
                glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w); //Get texture width -> w
                glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
                caseID = drawCase(w,h);
                glCallList(caseID);
            glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    return;
}