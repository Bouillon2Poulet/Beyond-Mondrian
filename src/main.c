#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "scene.h"
#include "camera.h"
#include "menu.h"

int gamestate = 0; //0 : menu, 1 : tuto, 2 : niveau 1

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 1920;
static const unsigned int WINDOW_HEIGHT = 1080;
static const char WINDOW_TITLE[] = "Project";

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

    /* Création du jeu */

    //Menu
    StartMenu startMenu = createStartMenu();

    //Scène
    Scene scene = createScene();

    //QuadTree
    QuadTree quadTree = createQuadTree(0, 0, WINDOW_WIDTH,  WINDOW_HEIGHT);
    addQuadTreeToScene(&scene, quadTree);

    //Joueurs
    Player player = createPlayer(0, 0, 1, 1, 1, 1, 0, 0);
    Player player2 = createPlayer(-2, 0, 0.5, 2, 1, 0, 1, 0);
    Player player3 = createPlayer(2, 0, 2, 0.5, 1, 0.5, 0, 0.5);
    addPlayerToScene(&scene, player, -4, -3);
    addPlayerToScene(&scene, player2, 4, -0.5);
    addPlayerToScene(&scene, player3, 3, -4.25);

    //Cubes
    Cube cube = createCube(3, -5, 10, 1, 1, 0, 0, 1);
    Cube cube1 = createCube(4, -2, 1, 1, 1, 0, 0, 1);
    Cube cube2 = createCube(-4, -4, 1, 1, 1, 0, 0, 1);
    Cube cube3 = createCube(5, -0.5, 1, 1, 1, 0, 0, 1);
    Cube cube4 = createCube(-5, 0, 1, 1, 1, 0, 0, 1);
    addCubeToScene(&scene, cube);
    addCubeToScene(&scene, cube1);
    addCubeToScene(&scene, cube2);
    addCubeToScene(&scene, cube3);
    addCubeToScene(&scene, cube4);
    
    //Génération du QuadTree
    generateQuadTree(&scene.quadTree);
    std::vector<QuadTree*> playerQuadTree;
    
    //Caméra
    Camera camera = createCamera(scene.players[scene.currentPlayerIndex].cube.x, scene.players[scene.currentPlayerIndex].cube.y);
    
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
        switch(gamestate)
        {
            case 0:
                updateMenu(&startMenu, startTime); 
                drawMenu(startMenu);
                break;
            
            case 1:
                drawHUD(scene);
                moveCamera(&camera, scene.players[scene.currentPlayerIndex]);
                
                for (int j = 0; j < scene.playersCount; j++)
                {
                    addGravity(&scene.players[j]);
                    checkEndCollision(&scene.players[j], scene.playersEnd[j]);
                    findPlayerQuadTree(&scene.quadTree, scene.players[j], playerQuadTree);
                    int temp = 0;
                    for (auto quadTree : playerQuadTree)
                    {
                        for (int i = 0; i < quadTree->nbCubes; i++)
                        {
                            if (checkCollision(scene.players[j], quadTree->cubes[i]) == 1)
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

                drawScene(scene);
                checkLevelState(scene);
        }
        

        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);

        /* Contrôles */

        const Uint8* keystates = SDL_GetKeyboardState(NULL);

        if(keystates[SDL_SCANCODE_LEFT] && gamestate != 0) 
        {
            movePlayer(&scene.players[scene.currentPlayerIndex], -1);
            findPlayerQuadTree(&scene.quadTree, scene.players[scene.currentPlayerIndex], playerQuadTree);
            for (auto quadTree : playerQuadTree)
            {
                for (int i = 0; i < quadTree->nbCubes; i++)
                {
                    if (checkCollision(scene.players[scene.currentPlayerIndex], quadTree->cubes[i]) == 1)
                    {
                        scene.players[scene.currentPlayerIndex].cube.x = 
                        quadTree->cubes[i].x + quadTree->cubes[i].width/2 + scene.players[scene.currentPlayerIndex].cube.width/2;
                    }
                }
            }
            playerQuadTree.clear();
        }
        
        if(keystates[SDL_SCANCODE_RIGHT] && gamestate != 0) 
        {
            movePlayer(&scene.players[scene.currentPlayerIndex], 1);
            findPlayerQuadTree(&scene.quadTree, scene.players[scene.currentPlayerIndex], playerQuadTree);
            for (auto quadTree : playerQuadTree)
            {
                for (int i = 0; i < quadTree->nbCubes; i++)
                {
                    if (checkCollision(scene.players[scene.currentPlayerIndex], quadTree->cubes[i]) == 1)
                    {
                        scene.players[scene.currentPlayerIndex].cube.x = 
                        quadTree->cubes[i].x - quadTree->cubes[i].width/2 - scene.players[scene.currentPlayerIndex].cube.width/2;
                    }
                }
            }
            playerQuadTree.clear();
        }

        if(keystates[SDL_SCANCODE_SPACE] && gamestate != 0) 
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
                    if (e.key.keysym.sym == SDLK_a && gamestate != 0)
                    {
                        switchCurrentPlayer(&scene);
                    }
                    if (gamestate == 0 && e.key.keysym.sym != SDLK_F6) //F6 input was automatic, this aims to avoid skipping menu
                    {
                        gamestate = 1;
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
    SDL_Quit();

    return EXIT_SUCCESS;
}