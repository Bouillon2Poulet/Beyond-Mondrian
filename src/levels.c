#include "levels.h"
#include "menu.h"

void createLevel1(Scene* scene)
{
    //Joueurs
    Player player = createPlayer(0, 0, 10, 10, 1, 1, 0, 0);
    Player player2 = createPlayer(-20, 0, 5, 20, 1, 1, 1, 0);
    Player player3 = createPlayer(20, 0, 20, 5, 1, 0, 0, 1);
    addPlayerToScene(scene, player, 340, -20);
    addPlayerToScene(scene, player2, 100, -75);
    addPlayerToScene(scene, player3, 210, 75);

    //Cubes
    Cube tabCube[16];

    //Cadre dessus/dessous
    tabCube[0] = createCube(120, -100, 300, 30, 1, 0, 0, 0);
    tabCube[1] = createCube(120, 100, 300, 30, 1, 0, 0, 0);

    //Cadre Coté Gauche (jaune)
    tabCube[2] = createCube(-10, -100, 50, 30, 1, 0, 0, 0);
    tabCube[3] = createCube(-10, 100, 50, 30, 1, 0, 0, 0);
    tabCube[4] = createCube(-34, 0, 2, 200, 1, 0, 0, 0);

    //Cadre Coté Droit (rouge)
    tabCube[5] = createCube(300, -70, 70, 90, 1, 0, 0, 0);
    tabCube[6] = createCube(300, 60, 70, 110, 1, 0, 0, 0);
    tabCube[7] = createCube(340, -26, 14, 2, 1, 0, 0, 0);
    tabCube[8] = createCube(347, -10, 2, 34, 1, 0, 0, 0);
    tabCube[9] = createCube(340, 6, 14, 2, 1, 0, 0, 0);

    //Elements du jeu
    tabCube[10] = createCube(80, -75, 20, 20, 1, 0, 0, 0);
    tabCube[11] = createCube(105, -50, 20, 20, 1, 0, 0, 0);
    tabCube[12] = createCube(115, -75, 20, 30, 1, 0, 0, 0);
    tabCube[13] = createCube(130, 10, 20, 2, 1, 0, 0, 0);
    tabCube[14] = createCube(150, 30, 20, 2, 1, 0, 0, 0);
    tabCube[15] = createCube(210, 70, 20, 2, 1, 0, 0, 0);

    for (int i = 0; i < 16; i++)
    {
        addCubeToScene(scene, tabCube[i]);
    }

    //Génération du QuadTree
    generateQuadTree(&scene->quadTree);
}

void createLevel2(Scene* scene)
{
    Scene newScene;
    initScene(&newScene);
    
    QuadTree quadTree = createQuadTree(0, 0, 1920, 1080);
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
    glPushMatrix(); //Background
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1,1,1);
        glVertex2f(-1200,600);
        glVertex2f(1200,600);
        glVertex2f(1200,-600);
        glVertex2f(-1200,-600);
        glEnd();
    glPopMatrix();

    if(currentTime%60==0)
    {
        int index = scene->lineCount;
        printf("scene->lineCount:%d",scene->lineCount);
        if(scene->lineCount%20==0)
        {
            index = scene->lineCount%20;
        }
        scene->background[index]=randomNewLine();
        displayLineInfo(scene->background[scene->lineCount]);
        scene->lineCount++;
    }

    for (int i=0;i<scene->lineCount;i++)
    {
        updateBackgroundLine(&scene->background[i]);
        drawLine(scene->background[i]);
    }
}
