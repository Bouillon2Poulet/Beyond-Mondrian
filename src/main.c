#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "map.h"
#include "scene.h"

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "Project";

/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 15.;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void onWindowResized(unsigned int width, unsigned int height)
{
    float aspectRatio = width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if( aspectRatio > 1)
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
    }
    else
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
        -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
    }
}

int main(int argc, char** argv)
{
    //* Initialisation de la SDL */

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        const char* error = SDL_GetError();
        fprintf(
            stderr,
            "Erreur lors de l'intialisation de la SDL : %s\n", error);

        SDL_Quit();
        return EXIT_FAILURE;
    }

    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */

    SDL_Window* window;
    {
        window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if(NULL == window)
        {
            const char* error = SDL_GetError();
            fprintf(
                stderr,
                "Erreur lors de la creation de la fenetre : %s\n", error);

            SDL_Quit();
            return EXIT_FAILURE;
        }
    }

    SDL_GLContext context;
    {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        context = SDL_GL_CreateContext(window);

        if(NULL == context)
        {
            const char* error = SDL_GetError();
            fprintf(
                stderr,
                "Erreur lors de la creation du contexte OpenGL : %s\n", error);

            SDL_DestroyWindow(window);
            SDL_Quit();
            return EXIT_FAILURE;
        }
    }

    onWindowResized(WINDOW_WIDTH, WINDOW_HEIGHT);

    /* Boucle principale */
    int loop = 1;

    Scene scene = createScene();
    Player player = createPlayer(0, 0, 1, 1, 1, 1, 0, 0);
    addPlayerToScene(&scene, player);

    //Rom1
    MapNode root = createMapNode("root",-1600,1600,1600,-1600);

    Cube cube = createCube(0, -5, 10, 1, 1, 0, 0, 1);
    Cube cube1 = createCube(4, -1, 1, 1, 1, 0, 1, 1);
    Cube cube2 = createCube(-4, -4, 1, 1, 1, 0, 0, 1);
    Cube cube3 = createCube(10, 3, 4, 2, 1, 0, 0, 1);

    Cube tabCube[30];
    tabCube[0]=cube;
    tabCube[1]=cube1;
    tabCube[2]=cube2;
    tabCube[3]=cube3;

    //fillRandomTabCube(tabCube); //Fill tabCube with 30 random cubes

    for (int i=0;i<3;i++) //3->30 if using fillRandomTabCube function
    {
        printf("-----\nCube n°%d, x : %f, y : %f\n",i+1,tabCube[i].x,tabCube[i].y);
        addCubeToMapTree(&root,tabCube[i]);
    }
    printf("-----\nNodeTree filled !!!\n-----");
    addMapToScene(&scene,root);

    while(loop)
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();

        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        addGravity(&scene.player);
        MapNode* actualMapNode = findActualMapNode(scene.player,&scene.map);
        printf("actualMapNode.name: %s\n",actualMapNode->name);
        for (int i = 0; i < actualMapNode->nbCubes; i++)
        {
            if (checkCollision(scene.player, actualMapNode->tabCubes[i]) == 1)
            {
                if (actualMapNode->tabCubes[i].y)
                {
                    scene.player.cube.y = actualMapNode->tabCubes[i].y + actualMapNode->tabCubes[i].height/2 + scene.player.cube.height/2;
                    scene.player.isGrounded = 1;
                    scene.player.gravity = 0;
                    break;
                }
                else if (scene.player.cube.y < actualMapNode->tabCubes[i].y)
                {
                    scene.player.cube.y = actualMapNode->tabCubes[i].y - actualMapNode->tabCubes[i].height/2 - scene.player.cube.height/2;
                    scene.player.gravity = 0;
                }
            }
            scene.player.isGrounded = 0;
        }
        drawScene(scene);

        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);

        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            /* L'utilisateur ferme la fenetre : */
			if(e.type == SDL_QUIT)
			{
				loop = 0;
				break;
			}

			if(	e.type == SDL_KEYDOWN
				&& (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
			{
				loop = 0;
				break;
			}

            switch(e.type)
            {
                case SDL_WINDOWEVENT:
                    switch (e.window.event)
                    {
                        /* Redimensionnement fenetre */
                        case SDL_WINDOWEVENT_RESIZED:
                            onWindowResized(e.window.data1, e.window.data2);
                            break;

                        default:
                            break;
                    }
                    break;

                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    printf("clic en (%d, %d)\n", e.button.button, e.button.y);
                    break;

                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);

                default:
                    break;
            }
        }

        const Uint8* keystates = SDL_GetKeyboardState(NULL);

        if(keystates[SDL_SCANCODE_LEFT]) 
        {
            scene.player.cube.x -= scene.player.movementSpeed;
            for (int i = 0; i < actualMapNode->nbCubes; i++)
            {
                if (checkCollision(scene.player, actualMapNode->tabCubes[i]) == 1)
                {
                    scene.player.cube.x = actualMapNode->tabCubes[i].x + actualMapNode->tabCubes[i].width/2 + scene.player.cube.width/2;
                }
            }
        }
        
        if(keystates[SDL_SCANCODE_RIGHT]) 
        {
            scene.player.cube.x += scene.player.movementSpeed;
            for (int i = 0; i < actualMapNode->nbCubes; i++)
            {
                if (checkCollision(scene.player, actualMapNode->tabCubes[i]) == 1)
                {
                    scene.player.cube.x = actualMapNode->tabCubes[i].x - actualMapNode->tabCubes[i].width/2 - scene.player.cube.width/2;
                }
            }
        }

        if(keystates[SDL_SCANCODE_SPACE]) 
        {
            if (scene.player.isGrounded == 1)
            {
                playerJump(&scene.player);
            }
        }

        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS)
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }
    /* Liberation des ressources associees a la SDL */
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}