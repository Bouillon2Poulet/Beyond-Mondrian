#include "levels.h"
#include "menu.h"

void createLevel1(Scene* scene)
{
    //Joueurs
    Player player = createPlayer(0, 0, 1, 1, 1, 1, 0, 0);
    // create player : Posx, Posy, largeur, hauteur, fill?, R,G,B
    Player player2 = createPlayer(-2, 0, 0.5, 2, 1, 0, 1, 0);
    Player player3 = createPlayer(2, 0, 2, 0.5, 1, 0.5, 0, 0.5);
    addPlayerToScene(scene, player, 34, -2);
    addPlayerToScene(scene, player2, 10, -7.5);
    addPlayerToScene(scene, player3, 21, 7.5);

    //Cubes
    Cube tabCube[16];
    //Cadre dessus/dessous
    tabCube[0] = createCube(12, -10, 30, 3, 1, 1, 1, 1);
    tabCube[1] = createCube(12, 10, 30, 3, 1, 0, 0, 1);

    //Cadre Coté Gauche (jaune)
    tabCube[2] = createCube(-1, -10, 5, 3, 1, 1, 1, 0);
    tabCube[3] = createCube(-1, 10, 5, 3, 1, 1, 1, 0);
    tabCube[4] = createCube(-3.4, 0, 0.2, 20, 1, 1, 1, 0);

    //Cadre Coté Droit (rouge)
    tabCube[5] = createCube(30, -7, 7, 9, 1, 1, 0, 0);
    tabCube[6] = createCube(30, 6, 7, 11, 1, 1, 0, 0);
    tabCube[7] = createCube(34, -2.6, 1.4, 0.2, 1, 1, 0, 0);
    tabCube[8] = createCube(34.7, -1, 0.2, 3.4, 1, 1, 0, 0);
    tabCube[9] = createCube(34, 0.6, 1.4, 0.2, 1, 1, 0, 0);

    //Elements du jeu
    tabCube[10] = createCube(8, -7.5, 2, 2, 1, 1, 1, 1);
    tabCube[11] = createCube(10.5, -5, 2, 2, 1, 1, 1, 1);
    tabCube[12] = createCube(11.5, -7.5, 2, 3, 1, 1, 1, 1);

    tabCube[13] = createCube(13, 1, 2, 0.2, 1, 1, 1, 1);
    tabCube[14] = createCube(15, 3, 2, 0.2, 1, 1, 1, 1);
    tabCube[15] = createCube(21, 7, 2, 0.2, 1, 1, 1, 1);



    for (int i=0;i<16;i++)
    {
        addCubeToScene(scene,tabCube[i]);
    }

    //Génération du QuadTree
    generateQuadTree(&scene->quadTree);
}

void createLevel2(Scene* scene)
{
    Scene newScene = createScene();
    
    QuadTree quadTree = createQuadTree(0, 0, 1920,  1080);
    addQuadTreeToScene(&newScene, quadTree);

    //Joueurs
    Player player = createPlayer(0, 0, 1, 1, 1, 1, 0, 0);
    Player player2 = createPlayer(-2, 0, 0.5, 2, 1, 0, 1, 0);
    addPlayerToScene(&newScene, player, -4, -3);
    addPlayerToScene(&newScene, player2, 4, -0.5);

    //Cubes
    Cube cube = createCube(3, -5, 10, 1, 1, 0, 0, 1);
    Cube cube1 = createCube(3, -2, 1, 1, 1, 0, 0, 1);
    Cube cube2 = createCube(-4, -6, 1, 1, 1, 0, 0, 1);
    Cube cube3 = createCube(5, 4, 1, 1, 1, 0, 0, 1);
    Cube cube4 = createCube(5, 3, 3, 1, 1, 0, 0, 1);
    addCubeToScene(&newScene, cube);
    addCubeToScene(&newScene, cube1);
    addCubeToScene(&newScene, cube2);
    addCubeToScene(&newScene, cube3);
    addCubeToScene(&newScene, cube4);
    
    //Génération du QuadTree
    generateQuadTree(&newScene.quadTree);

    *scene = newScene;
}

void displayBackground(Scene* scene, Uint32 currentTime)
{
    glPushMatrix();
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1,1,1);
        glVertex2f(-960,540);
        glVertex2f(960,540);
        glVertex2f(960,-540);
        glVertex2f(-960,-540);
        glEnd();
    glPopMatrix();

    //BackgroundLine newBackgroundLine = createBackgroundLine(10,0,1,-2000,250,0,5000,0,0,0); //first horizontal 
    //printf("????\n");
    if(currentTime%60==0)
    {
        printf("\nnum.%d",scene->lineCount);
        //addRandomLineToScene(scene, currentTime);
        scene->background[scene->lineCount]=randomNewLine(currentTime);
        printf("time: %d\n",scene->background[scene->lineCount].time);
        printf("endTime: %d\n\n",scene->background[scene->lineCount].endTime);
        scene->lineCount++;
    }
    //updateBackgroundLine(&newBackgroundLine, currentTime);
    

    for (int i=0;i<=scene->lineCount;i++)
    {
        updateBackgroundLine(&scene->background[i],currentTime);
        drawLine(scene->background[i]);
    }

    // printf("scene.background[0].b = %f\n",scene->background[0].b);
    // printf("celle qui marche : 10,0,1,-2000,250,0,5000,0,0,0\n");
    // printf("celle qui marche pas : %d,%d,%d,%d,%d,%d,%d,%f,%f,%f\n",scene->background[0].width, scene->background[0].mode, scene->background[0].sens, scene->background[0].xStart, scene->background[0].yStart,scene->background[0].time, scene->background[0].endTime, scene->background[0].r, scene->background[0].g, scene->background[0].b);
    // updateBackgroundLine(&scene->background[0], currentTime);
    // printf("background[0].sens=%d",scene->background[0].sens);
    // printf("background[0].mode=%d",scene->background[0].mode);
    // printf("background[0].xStart=%d",scene->background[0].xStart);
    // printf("background[0].yStart=%d",scene->background[0].yStart);
    // drawLine(scene->background[0]);
    return;
}
