#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "TD03 Minimal";

/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 150.;

/* Subdivisions cercle */
static const int CIRCLE_SUBDIVS = 2<<5;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int lastMousePress = 0;


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


/* Objets cannoniques */
void drawOrigin()
{
    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR,currentColor);

    glBegin(GL_LINES);

    glColor3f(1., 0., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 1.0 , 0.0);

    glColor3f(0., 1., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 0.0 , 1.0);

    glEnd();

    glColor3fv(currentColor);
}

void drawSquare(int filled)
{
    if(filled)
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else
    {
        glBegin(GL_LINE_STRIP);
    }

    glVertex2f( 0.5 , -0.5);
    glVertex2f( 0.5 , 0.5);
    glVertex2f( -0.5 , 0.5);
    glVertex2f( -0.5 , -0.5);
    glVertex2f( 0.5 , -0.5);

    glEnd();
}

void drawCircle(int filled)
{
    int i = 0;

    if(filled)
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else
    {
        glBegin(GL_LINE_STRIP);
    }

    for(i = 0; i < CIRCLE_SUBDIVS; i++)
    {
        glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)),
                    sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)));
    }
    glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)),
                sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)));

    glEnd();
}


GLuint createFirstArmIDList(float l, float c1, float c2) // l = 30, c1 = 10, c2 = 5
{
    GLuint id = glGenLists(1);
    glNewList(id, GL_COMPILE);

    glPushMatrix();
        glScalef(c1, c1, 1.);
        drawCircle(0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(l, 0., 0.);
        glScalef(c2, c2, 1.);
        drawCircle(0);
    glPopMatrix();
    glBegin(GL_LINES);
        glVertex2f(0., c1);
        glVertex2f(l, c2);
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(0., -c1);
        glVertex2f(l, -c2);
    glEnd();

    glEndList();
    return id;
}

GLuint createSecondArmIDList(float w, float h)
{
    GLuint id = glGenLists(1);
    glNewList(id, GL_COMPILE);

    glPushMatrix();
        glTranslatef(w/2., 0, 0); // le rectangle part du centre du canvas
        glScalef(w, h, 1.);
        drawSquare(0);
    glPopMatrix();

    glEndList();
    return id;
}


GLuint createThirdArmIDList(float w, float h, float r)
{
    GLuint id = glGenLists(1);
    glNewList(id, GL_COMPILE);

    glPushMatrix();
        glTranslatef(w/2., 0, 0); // le rectangle part du centre du canvas
        glScalef(w, h, 1.);
        drawSquare(0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(w, 0, 0);
        glScalef(r, r, 1.);
        drawCircle(0);
    glPopMatrix();

    glEndList();
    return id;
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

    float alpha = 30.;
    float beta = -30.;
    float delta = 30.;
    int alphaRotationMode = 1;

    float firstArmSize = 30.;
    float secondArmSize = 25.;
    float thirdArmSize = 20.;

    int firstArmID = createFirstArmIDList(firstArmSize, 10., 5.);
    int secondArmID = createSecondArmIDList(secondArmSize, 5.);
    int thirdArmID = createThirdArmIDList(thirdArmSize, 3., 4.);

    while(loop)
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();

        /* Placer ici le code de dessin //////////////////////////////////////////////////////////////*/
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glPushMatrix();
            glRotatef(alpha, 0, 0, 1.);
            glCallList(firstArmID);

            glTranslatef(firstArmSize, 0, 0);
            glRotatef(beta, 0, 0, 1.);
            glCallList(secondArmID);

            glTranslatef(secondArmSize-2.5, 0., 0.);
            glCallList(thirdArmID);

            glRotatef(delta, 0, 0, 1.);
            glCallList(thirdArmID);

            glRotatef(-(delta*2), 0, 0, 1.);
            glCallList(thirdArmID);
        glPopMatrix();

        // 3) Il n'est pas intéressant de créer une liste d'affichage pour le bras entier parce qu'on veut modifier
        // des parties du bras et une liste d'affichage est pas modifiable.

        // 4) Avantages : + rapide à éxecuter
        //    Inconvenients : Pas possible à modifier


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
                    lastMousePress = e.button.button;
                    break;

                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    break;

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

        //alpha = startTime * 0.01; //10 °/s
        if (alpha > 45)
            alphaRotationMode = 0;
        if (alpha < -45)
            alphaRotationMode = 1;

        if (alphaRotationMode == 1)
            alpha += elapsedTime * 0.05;
        else
            alpha -= elapsedTime * 0.05;

        if (lastMousePress == 1)
            beta += elapsedTime * 0.1;
        else
            beta -= elapsedTime * 0.1;

    }

    /* Liberation des ressources associees a la SDL */
    SDL_GL_DeleteContext(context);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}