#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "screen.h"
#include "camera.h"
#include "levels.h"
#include "scene.h"

int gameState = 0; //0 -> MENU | 1 -> LEVEL 1 | 2 -> LEVEL 2 | 3 -> LEVEL 3 | 4 -> END
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
    //*SDL initialisation */

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        const char* error = SDL_GetError();
        fprintf(
            stderr,
            "Erreur lors de l'intialisation de la SDL : %s\n", error);

        SDL_Quit();
        return EXIT_FAILURE;
    }

    // SDL_Mixer initialisation
    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur initialisation SDL_mixer : %s", Mix_GetError());
        SDL_Quit();
        return -1;
    }

    /* Window opening and OpenGL context creation */
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
                "Erreur while creating window : %s\n", error);

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
                "Erreur while creating OpenGL context : %s\n", error);

            SDL_DestroyWindow(window);
            SDL_Quit();
            return EXIT_FAILURE;
        }
    }

    onWindowResized(WINDOW_WIDTH, WINDOW_HEIGHT);

    /* Game creation*/
    //Audio
    Mix_AllocateChannels(2); // Allocate 2 channels
    Mix_Volume(0, MIX_MAX_VOLUME); //volume 100% for channel 0
    Mix_Volume(1, MIX_MAX_VOLUME / 2); // volume 50% channel 1

    Mix_Chunk* mainTheme = Mix_LoadWAV("assets/audio/main.wav");
    Mix_Chunk* jumpSound = Mix_LoadWAV("assets/audio/jump.wav");
    Mix_Chunk* endTheme = Mix_LoadWAV("assets/audio/end.wav");

    //Start and end screens
    Screen startScreen = createScreen(0);
    Screen endScreen = createScreen(1);

    //Scene
    Scene scene, scene2;
    initScene(&scene); // Levels
    initScene(&scene2); // For background
    scene2.lineCount=0;

    //QuadTree
    QuadTree quadTree = createQuadTree(0, 0, WINDOW_WIDTH,  WINDOW_HEIGHT);
    addQuadTreeToScene(&scene, quadTree);
    std::vector<QuadTree*> playerQuadTree;

    //Camera
    Camera camera = createCamera(0, 0);

    /* Main loop */
    int loop = 1;
    
    while(loop)
    {
        /* Get time since the window opened */
        Uint32 startTime = SDL_GetTicks();

        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        switch(gameState)
        {
            case 0:
                while(Mix_Playing(0)==0)//Check if there is a sound playing on channel 0
                {
                    Mix_PlayChannel(0, mainTheme, -1); // Play main theme infinite time on channel 0
                }
                drawScreen(&startScreen);
                break;
            
            case 1:
            case 2:
            case 3:
                checkGravityCollisions(&scene, playerQuadTree); //CHECKING COLLISIONS DUE TO GRAVITY
                glLoadIdentity();
                moveCamera(&camera, scene.players[scene.currentPlayerIndex]);
                glPushMatrix();
                glScalef(0.6, 0.6, 0);
                displayBackground(&scene2, SDL_GetTicks(), gameState);
                glPopMatrix();
                drawScene(scene);
                drawHUD(scene);
                break;
            case 4 :
                drawScreen(&endScreen);
                break;
        }
        
        /* Checking game level state */

        if (checkLevelState(scene) == 1 && gameState > 0 && gameState < 4)
        {
            gameState++;
            if(gameState==4)
            {
                Mix_PlayChannel(0, endTheme, 1); // Play endTheme 1 time on channel 0
            }
            if (gameState == 2)
            {
                createLevel2(&scene);
            }
            else if (gameState == 3)
            {
                createLevel3(&scene);
            }
        }

        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);

        /* Input */

        const Uint8* keystates = SDL_GetKeyboardState(NULL);

        if(keystates[SDL_SCANCODE_LEFT] && gameState != 0) 
        {
            movePlayer(&scene.players[scene.currentPlayerIndex], -1);
            checkLeftCollisions(&scene, playerQuadTree);
        }
        
        if(keystates[SDL_SCANCODE_RIGHT] && gameState != 0) 
        {
            movePlayer(&scene.players[scene.currentPlayerIndex], 1);
            checkRightCollisions(&scene, playerQuadTree);
        }

        if(keystates[SDL_SCANCODE_SPACE] && gameState != 0) 
        {
            if (scene.players[scene.currentPlayerIndex].isGrounded == 1)
            {
                Mix_PlayChannel(1, jumpSound, 0);
                playerJump(&scene.players[scene.currentPlayerIndex]);
            }
        }

        /* Events loop */
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            /* Close window : */
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
                        /* Window resized */
                        case SDL_WINDOWEVENT_RESIZED:
                            onWindowResized(e.window.data1, e.window.data2);
                            break;

                        default:
                            break;
                    }
                    break;

                /* Mouse click */
                case SDL_MOUSEBUTTONUP:
                    break;

                /* Keyboard*/
                case SDL_KEYDOWN:
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

                    if (gameState == 0 && e.key.keysym.sym != SDLK_F6) //F6 input was automatic, this aims to avoid skipping screen
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

        /* Calculated elapsed time */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* If not enough elapsed time, pause the program */
        if(elapsedTime < FRAMERATE_MILLISECONDS)
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Free SDL ressources */
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    Mix_FreeChunk(mainTheme); // Free audio memory
    Mix_FreeChunk(jumpSound);
    Mix_FreeChunk(endTheme); 
    Mix_CloseAudio();
    SDL_Quit();

    return EXIT_SUCCESS;
}