#include "levels.h"
#include "screen.h"

void createLevel1(Scene* scene)
{
    //Joueurs
    Player player = createPlayer(0, 0, 10, 10, 1, 1, 0, 0);
    Player player2 = createPlayer(-20, 0, 5, 20, 1, 1, 1, 0);
    Player player3 = createPlayer(20, 0, 20, 5, 1, 0, 0, 1);
    addPlayerToScene(scene, player, 341, -20);
    addPlayerToScene(scene, player2, 102, -75);
    addPlayerToScene(scene, player3, 210, 63.5);

    /* Cubes qui bougent */
    MovingCube movingCube = createMovingCube(150, 25, 5, 30, 1, 0, 0, 0, 120, 25, 170, 25, 1);
    addMovingCubeToScene(scene, movingCube);

    //Cubes
    Cube tabCube[15];

    //Cadre dessus/dessous
    tabCube[0] = createCube(120, -100, 300, 30, 1, 0, 0, 0, 0);
    tabCube[1] = createCube(120, 100, 300, 30, 1, 0, 0, 0, 0);

    //Cadre Coté Gauche (jaune)
    tabCube[2] = createCube(-10, -100, 50, 30, 1, 0, 0, 0, 0);
    tabCube[3] = createCube(-10, 100, 50, 30, 1, 0, 0, 0, 0);
    tabCube[4] = createCube(-34, 0, 2, 200, 1, 0, 0, 0, 0);

    //Cadre Coté Droit (rouge)
    tabCube[5] = createCube(300, -70, 70, 90, 1, 0, 0, 0, 0);
    tabCube[6] = createCube(300, 60, 70, 110, 1, 0, 0, 0, 0);
    tabCube[7] = createCube(340, -26, 14, 2, 1, 0, 0, 0, 0);
    tabCube[8] = createCube(347, -10, 2, 34, 1, 0, 0, 0, 0);
    tabCube[9] = createCube(340, 6, 14, 2, 1, 0, 0, 0, 0);

    //Elements du jeu
    tabCube[10] = createCube(80, -75, 20, 20, 1, 0, 0, 0, 0);
    tabCube[11] = createCube(105, -50, 20, 20, 1, 0, 0, 0, 0);
    tabCube[12] = createCube(115, -75, 20, 30, 1, 0, 0, 0, 0);
    tabCube[13] = createCube(210, 60, 20, 2, 1, 0, 0, 0, 0);

    //Piques
    tabCube[14] = createCube(200, -75, 20, 20, 1, 0, 0, 0, 1);
    
    for (int i = 0; i < 15; i++)
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
    Player player = createPlayer(0, -45, 10, 10, 1, 1, 0, 0);
    Player player2 = createPlayer(-20, -45, 5, 20, 1, 1, 1, 0);
    Player player3 = createPlayer(20, -45, 20, 5, 1, 0, 0, 1);
    addPlayerToScene(&newScene, player, 110, 52.5);
    addPlayerToScene(&newScene, player2, -20, 20);
    addPlayerToScene(&newScene, player3, 480, -72.5);

    MovingCube movingCube = createMovingCube(150, 10, 5, 30, 1, 0, 0, 0, 150, 20, 150, 0, 1);
    addMovingCubeToScene(&newScene, movingCube);
    
    //Cubes
    Cube tabCube[17];

    //Cadre dessus/dessous
    tabCube[0] = createCube(20, -97, 100, 45, 1, 0, 0, 0, 0);
    tabCube[1] = createCube(75, -124, 220, 10, 1, 0, 0, 0, 0);
    tabCube[2] = createCube(220, -80, 200, 10, 1, 0, 0, 0, 0);
    tabCube[3] = createCube(150, -105, 60, 28, 1, 0, 0, 0, 0);
    tabCube[4] = createCube(260, -124, 180, 10, 1, 0, 0, 0, 0);
    tabCube[5] = createCube(275, -98, 90, 28, 1, 0, 0, 0, 0);
    tabCube[6] = createCube(361, -105, 20, 20, 1, 0, 0, 0, 0);
    tabCube[7] = createCube(385, -95, 20, 20, 1, 0, 0, 0, 0);
    tabCube[8] = createCube(449, -85, 100, 20, 1, 0, 0, 0, 0);
    tabCube[9] = createCube(-35, -200, 10, 800, 1, 0, 0, 0, 0);
    tabCube[10] = createCube(-15, -15, 50, 50, 1, 0, 0, 0, 0);
    tabCube[11] = createCube(91, -37.5, 200, 5, 1, 0, 0, 0, 0);
    tabCube[12] = createCube(110, 45, 20, 5, 1, 0, 0, 0, 0);
    tabCube[13] = createCube(500, -200, 10, 800, 1, 0, 0, 0, 0);
    
    //Piques
    tabCube[14] = createCube(220, -65, 20, 20, 1, 0, 0, 0, 1);
    tabCube[15] = createCube(240, -65, 20, 20, 1, 0, 0, 0, 1);
    tabCube[16] = createCube(260, -65, 20, 20, 1, 0, 0, 0, 1);

    for (int i = 0; i < 17; i++)
    {
        addCubeToScene(&newScene, tabCube[i]);
    }

    //Génération du QuadTree
    generateQuadTree(&newScene.quadTree);

    *scene = newScene;
}

void createLevel3(Scene* scene)
{
    Scene newScene;
    initScene(&newScene);
    
    QuadTree quadTree = createQuadTree(0, 0, 1920, 1080);
    addQuadTreeToScene(&newScene, quadTree);

    //Joueurs
    Player player = createPlayer(0, -45, 10, 10, 1, 1, 0, 0);
    Player player2 = createPlayer(-70, 5, 5, 20, 1, 1, 1, 0);
    Player player3 = createPlayer(20, -45, 20, 5, 1, 0, 0, 1);
    addPlayerToScene(&newScene, player, 40, 182.5);
    addPlayerToScene(&newScene, player2, 110, -64.5);
    addPlayerToScene(&newScene, player3, -43, -40);

    MovingCube movingCube = createMovingCube(20, 5, 5, 10, 1, 0, 0, 0, 20, -30, 20, 60, 1);
    MovingCube movingCube2 = createMovingCube(80, 125, 5, 10, 1, 0, 0, 0, 80, 70, 80, 160, 2);
    addMovingCubeToScene(&newScene, movingCube);
    addMovingCubeToScene(&newScene, movingCube2);

    //Cubes
    Cube tabCube[21];

    //Cadre dessus/dessous
    tabCube[0] = createCube(20, -97, 200, 45, 1, 0, 0, 0, 0);
    tabCube[1] = createCube(-10, 75, 5, 300, 1, 0, 0, 0, 0);
    tabCube[2] = createCube(-77.5, 200, 5, 550, 1, 0, 0, 0, 0);
    tabCube[3] = createCube(-70, -25, 15, 15, 1, 0, 0, 0, 0);
    tabCube[4] = createCube(-73, 25, 5, 15, 1, 0, 0, 0, 0);
    tabCube[5] = createCube(-73, 75, 5, 15, 1, 0, 0, 0, 0);
    tabCube[6] = createCube(-73, 125, 5, 15, 1, 0, 0, 0, 0);
    tabCube[7] = createCube(-15, 0, 5, 15, 1, 0, 0, 0, 0);
    tabCube[8] = createCube(-15, 50, 5, 15, 1, 0, 0, 0, 0);
    tabCube[9] = createCube(-15, 100, 5, 15, 1, 0, 0, 0, 0);
    tabCube[10] = createCube(-15, 150, 5, 15, 1, 0, 0, 0, 0);
    tabCube[11] = createCube(-73, 175, 5, 15, 1, 0, 0, 0, 0);
    tabCube[12] = createCube(-15, 200, 5, 15, 1, 0, 0, 0, 0);
    tabCube[13] = createCube(35, 175, 25, 5, 1, 0, 0, 0, 0);
    tabCube[14] = createCube(117.5, 200, 5, 550, 1, 0, 0, 0, 0);

    //Piques
    tabCube[15] = createCube(-69, -70, 10, 10, 1, 0, 0, 0, 1);
    tabCube[16] = createCube(-59, -70, 10, 10, 1, 0, 0, 0, 1);
    tabCube[17] = createCube(-49, -70, 10, 10, 1, 0, 0, 0, 1);
    tabCube[18] = createCube(-39, -70, 10, 10, 1, 0, 0, 0, 1);
    tabCube[19] = createCube(-29, -70, 10, 10, 1, 0, 0, 0, 1);
    tabCube[20] = createCube(-19, -70, 10, 10, 1, 0, 0, 0, 1);

    for (int i = 0; i < 21; i++)
    {
        addCubeToScene(&newScene, tabCube[i]);
    }

    //Génération du QuadTree
    generateQuadTree(&newScene.quadTree);

    *scene = newScene;
}
