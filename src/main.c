#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "menu.h"
#include "camera.h"
#include "levels.h"
#include "scene.h"
#include "audio.h"
#include <algorithm>

int gameState = 0; //0 : menu, 1 : tuto, 2 : niveau 1
int windowState = 0; //0 : normal, 1 : fullscreen;


/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 1920;
static const unsigned int WINDOW_HEIGHT = 1080;
static const char WINDOW_TITLE[] = "Beyond Mondrian";

/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 1080.;

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

    // Initialisation de SDL_Mixer
    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur initialisation SDL_mixer : %s", Mix_GetError());
        SDL_Quit();
        return -1;
    }

    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    SDL_ShowCursor(SDL_DISABLE);
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

    /* Création du jeu */
    //Audio
    // Mix_Music* musicMenu;
    // Mix_Music* jumpSound;

    Mix_AllocateChannels(2); // Allouer 2 cannaux 
    Mix_Volume(0, MIX_MAX_VOLUME); // Mets le son a 100% en volume pour le premier cannaux
    Mix_Volume(1, MIX_MAX_VOLUME / 2); // Mets le son a 50% en volume pour le deuxième cannaux 

    // loadMusic(&musicMenu,0);
    // loadMusic(&jumpSound,1);

    Mix_Chunk* soundA = Mix_LoadWAV("assets/audio/menu.wav");
    Mix_Chunk* soundB = Mix_LoadWAV("assets/audio/jump.wav");

    //Menu
    StartMenu startMenu = createStartMenu();

    //Scène
    Scene scene, scene2;
    initScene(&scene); //Changes on createScene that seemed to not affect value
    initScene(&scene2); //Test in gameState 5
    scene2.lineCount=0;

    //QuadTree
    QuadTree quadTree = createQuadTree(0, 0, WINDOW_WIDTH,  WINDOW_HEIGHT);
    addQuadTreeToScene(&scene, quadTree);
    std::vector<QuadTree*> playerQuadTree;

    //Caméra
    Camera camera = createCamera(0, 0);

    /* Boucle principale */
    int loop = 1;
    
    while(loop)
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();

        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        switch(gameState)
        {
            case 0:
                while(Mix_Playing(0)==0)//Check if there is a sound playing on channel 0
                {
                    Mix_PlayChannel(0, soundA, -1); // Joue soundA infini fois sur le canal 1
                }
                printf("?\n");
                drawMenu(&startMenu);
                break;
            
            case 1:
            case 2:
                for (int k = 0; k < scene.movingCubesCount; k++)
                {
                    moveCube(&scene.movingCubes[k]);
                }

                for (int j = 0; j < scene.playersCount; j++)
                {
                    addGravity(&scene.players[j]);
                    checkEndCollision(&scene.players[j], scene.playersEnd[j]);
                    findPlayerQuadTree(&scene.quadTree, scene.players[j], playerQuadTree);

                    /* Collisions obstacles qui bougent */

                    int temp = 0;

                    for (int i = 0; i < scene.movingCubesCount; i++)
                    {
                        if (checkCollision(scene.players[j], scene.movingCubes[i].cube) == 1)
                        {
                            temp = 1;
                            if (scene.players[j].cube.y > scene.movingCubes[i].cube.y)
                            {
                                scene.movingCubes[i].players.push_back(&scene.players[j]);
                                scene.players[j].cube.y = scene.movingCubes[i].cube.y + scene.movingCubes[i].cube.height/2 + scene.players[j].cube.height/2;
                                scene.players[j].isGrounded = 1;
                                scene.players[j].gravity = 0;
                            }
                            else if (scene.players[j].cube.y < scene.movingCubes[i].cube.y)
                            {
                                scene.players[j].cube.y = scene.movingCubes[i].cube.y - scene.movingCubes[i].cube.height/2 - scene.players[j].cube.height/2;
                                scene.players[j].gravity = 0;
                            }
                            break;
                        }
                    }
                    
                    /* Collisions joueurs */

                    if (temp == 0)
                    {
                        for (int i = 0; i < scene.playersCount; i++)
                        {
                            if (j != i && checkCollision(scene.players[j], scene.players[i].cube) == 1)
                            {
                                temp = 1;
                                if (scene.players[j].cube.y > scene.players[i].cube.y)
                                {
                                    scene.players[j].cube.y = scene.players[i].cube.y + scene.players[i].cube.height/2 + scene.players[j].cube.height/2;
                                    scene.players[j].isGrounded = 1;
                                }
                                else if (scene.players[j].cube.y < scene.players[i].cube.y)
                                {
                                    scene.players[j].cube.y = scene.players[i].cube.y - scene.players[i].cube.height/2 - scene.players[j].cube.height/2;
                                    scene.players[i].isGrounded = 1;
                                }
                                scene.players[j].gravity = 0;
                                break;
                            }
                        }
                    }
                    

                    /* Collisions obstacles */
                    
                    if (temp == 0)
                    {
                        for (auto quadTree : playerQuadTree)
                        {
                            for (int i = 0; i < quadTree->nbCubes; i++)
                            {
                                if (checkCollision(scene.players[j], quadTree->cubes[i]) == 1)
                                {
                                    if (quadTree->cubes[i].red == 1 && quadTree->cubes[i].green == 0 && quadTree->cubes[i].blue == 0)
                                    {
                                        scene.players[j].cube.x = scene.players[j].startPositions[0];
                                        scene.players[j].cube.y = scene.players[j].startPositions[1];
                                    }
                                    else
                                    {
                                        temp = 1;
                                        if (scene.players[j].cube.y > quadTree->cubes[i].y)
                                        {
                                            scene.players[j].cube.y = quadTree->cubes[i].y + quadTree->cubes[i].height/2 + scene.players[j].cube.height/2;
                                            scene.players[j].isGrounded = 1;
                                            scene.players[j].gravity = 0;
                                        }
                                        else if (scene.players[j].cube.y < quadTree->cubes[i].y)
                                        {
                                            scene.players[j].cube.y = quadTree->cubes[i].y - quadTree->cubes[i].height/2 - scene.players[j].cube.height/2;
                                            scene.players[j].gravity = 0;
                                        }
                                    }
                                    break;
                                }
                                scene.players[j].isGrounded = 0;
                            }
                            if (temp == 1)
                            {
                                break;
                            }
                        }
                        playerQuadTree.clear();
                    }
                }

                glLoadIdentity();
                moveCamera(&camera, scene.players[scene.currentPlayerIndex]);
                glPushMatrix();
                glScalef(0.6, 0.6, 0);
                displayBackground(&scene2, SDL_GetTicks(), gameState);
                glPopMatrix();
                drawScene(scene);
                drawHUD(scene);
                break;
        }
        
        if (checkLevelState(scene) == 1 && gameState > 0 && gameState < 3)
        {
            if (gameState == 1)
            {
                createLevel2(&scene);
            }
            gameState++;
        }

        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);

        /* Contrôles */

        const Uint8* keystates = SDL_GetKeyboardState(NULL);

        if(keystates[SDL_SCANCODE_LEFT] && gameState != 0) 
        {
            int temp1 = 0;

            movePlayer(&scene.players[scene.currentPlayerIndex], -1);
            
            /* Collisions joueurs */

            for (int i = 0; i < scene.playersCount; i++)
            {
                if (scene.currentPlayerIndex != i && checkCollision(scene.players[scene.currentPlayerIndex], scene.players[i].cube) == 1)
                {
                    scene.players[scene.currentPlayerIndex].cube.x = 
                    scene.players[i].cube.x + scene.players[i].cube.width/2 + scene.players[scene.currentPlayerIndex].cube.width/2;
                    break;
                }
            }

            /* Collisions obstacles */

            findPlayerQuadTree(&scene.quadTree, scene.players[scene.currentPlayerIndex], playerQuadTree);

            for (auto quadTree : playerQuadTree)
            {
                for (int i = 0; i < quadTree->nbCubes; i++)
                {
                    if (checkCollision(scene.players[scene.currentPlayerIndex], quadTree->cubes[i]) == 1)
                    {
                        if (quadTree->cubes[i].red == 1 && quadTree->cubes[i].green == 0 && quadTree->cubes[i].blue == 0)
                        {
                            scene.players[scene.currentPlayerIndex].cube.x = scene.players[scene.currentPlayerIndex].startPositions[0];
                            scene.players[scene.currentPlayerIndex].cube.y = scene.players[scene.currentPlayerIndex].startPositions[1];
                        }
                        else
                        {
                            temp1 = 1;
                            scene.players[scene.currentPlayerIndex].cube.x = 
                            quadTree->cubes[i].x + quadTree->cubes[i].width/2 + scene.players[scene.currentPlayerIndex].cube.width/2;
                            break;
                        }
                    }
                }
                if (temp1 == 1)
                {
                    break;
                }
            }
            playerQuadTree.clear();

            /* Collisions obstacles qui bougent */

            for (int i = 0; i < scene.movingCubesCount; i++)
            {
                if (checkCollision(scene.players[scene.currentPlayerIndex], scene.movingCubes[i].cube) == 1)
                {
                    scene.players[scene.currentPlayerIndex].cube.x = 
                    scene.movingCubes[i].cube.x + scene.movingCubes[i].cube.width/2 + scene.players[scene.currentPlayerIndex].cube.width/2;
                    break;
                }
            }
        }
        
        if(keystates[SDL_SCANCODE_RIGHT] && gameState != 0) 
        {
            int temp1 = 0;

            movePlayer(&scene.players[scene.currentPlayerIndex], 1);

            /* Collisions joueurs */

            for (int i = 0; i < scene.playersCount; i++)
            {
                if (scene.currentPlayerIndex != i && checkCollision(scene.players[scene.currentPlayerIndex], scene.players[i].cube) == 1)
                {
                    scene.players[scene.currentPlayerIndex].cube.x = 
                    scene.players[i].cube.x - scene.players[i].cube.width/2 - scene.players[scene.currentPlayerIndex].cube.width/2;
                    break;
                }
            }

            /* Collisions obstacles */

            findPlayerQuadTree(&scene.quadTree, scene.players[scene.currentPlayerIndex], playerQuadTree);
            for (auto quadTree : playerQuadTree)
            {
                for (int i = 0; i < quadTree->nbCubes; i++)
                {
                    if (checkCollision(scene.players[scene.currentPlayerIndex], quadTree->cubes[i]) == 1)
                    {
                        if (quadTree->cubes[i].red == 1 && quadTree->cubes[i].green == 0 && quadTree->cubes[i].blue == 0)
                        {
                            scene.players[scene.currentPlayerIndex].cube.x = scene.players[scene.currentPlayerIndex].startPositions[0];
                            scene.players[scene.currentPlayerIndex].cube.y = scene.players[scene.currentPlayerIndex].startPositions[1];
                        }
                        else
                        {
                            temp1 = 1;
                            scene.players[scene.currentPlayerIndex].cube.x = 
                            quadTree->cubes[i].x - quadTree->cubes[i].width/2 - scene.players[scene.currentPlayerIndex].cube.width/2;
                        }
                        
                        break;
                    }
                }
                if (temp1 == 1)
                {
                    break;
                }
            }
            playerQuadTree.clear();

            /* Collisions obstacles qui bougent */

            for (int i = 0; i < scene.movingCubesCount; i++)
            {
                if (checkCollision(scene.players[scene.currentPlayerIndex], scene.movingCubes[i].cube) == 1)
                {
                    scene.players[scene.currentPlayerIndex].cube.x = 
                    scene.movingCubes[i].cube.x - scene.movingCubes[i].cube.width/2 - scene.players[scene.currentPlayerIndex].cube.width/2;
                    break;
                }
            }
        }

        if(keystates[SDL_SCANCODE_SPACE] && gameState != 0) 
        {
            if (scene.players[scene.currentPlayerIndex].isGrounded == 1)
            {
                playerJump(&scene.players[scene.currentPlayerIndex]);
            }
        }

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
                    if (e.key.keysym.sym == SDLK_f)//Fullscreen
                    {
                        switch(windowState)
                        {
                            case 0:
                                windowState=1;
                                SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
                                break;
                            case 1:
                                windowState=0;
                                SDL_SetWindowFullscreen(window,0);
                                break;
                        }
                    }
                    if (e.key.keysym.sym == SDLK_a && gameState != 0)
                    {
                        switchCurrentPlayer(&scene);
                    }
                    if (e.key.keysym.sym == SDLK_SPACE && gameState > 0) //Jump sound
                    {
                        Mix_PlayChannel(1, soundB, 0); // Joue soundA infini fois sur le canal 1
                    }
                    if (gameState == 0 && e.key.keysym.sym != SDLK_F6) //F6 input was automatic, this aims to avoid skipping menu
                    {
                        if (startTime>=900)
                        {
                            createLevel1(&scene);
                            gameState = 1;
                        }
                    }
                default:
                    break;
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
    //Mix_FreeMusic(musicMenu);
    Mix_FreeChunk(soundA); // Libére la mémoire allouer pour le son
    Mix_FreeChunk(soundB);
    Mix_CloseAudio();
    SDL_Quit();

    return EXIT_SUCCESS;
}