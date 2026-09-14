#include <GL/glut.h>
#include <cstdlib>


// Scene 1: Waiting at Bus Stop
extern void initScene1();
extern void displayScene1();
extern void updateScene1();
extern void keyboardScene1(unsigned char key);

// Scene 2: Bus Arrival & Boarding (Tonmoy)
extern void initScene2();
extern void displayScene2();
extern void updateScene2();
extern void keyboardScene2(unsigned char key);

// Scene 3: Traffic Signal
extern void initScene3();
extern void displayScene3();
extern void updateScene3();
extern void keyboardScene3(unsigned char key);

// Scene 4: Disembarking at Destination
extern void initScene4();
extern void displayScene4();
extern void updateScene4();
extern void keyboardScene4(unsigned char key);

// Scene 5: Inside Room / Destination
extern void initScene5();
extern void displayScene5();
extern void updateScene5();
extern void keyboardScene5(unsigned char key);


int currentScene = 1;

// Central Display Router
void masterDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    switch (currentScene) {
        case 1: displayScene1(); break;
        case 2: displayScene2(); break;
        case 3: displayScene3(); break;
        case 4: displayScene4(); break;
        case 5: displayScene5(); break;
    }

    glutSwapBuffers();
}

// Master Animation Timer (60 FPS)
void masterTimer(int value) {
    switch (currentScene) {
        case 1: updateScene1(); break;
        case 2: updateScene2(); break;
        case 3: updateScene3(); break;
        case 4: updateScene4(); break;
        case 5: updateScene5(); break;
    }

    glutPostRedisplay();
    glutTimerFunc(16, masterTimer, 0);
}

// Central Keyboard Event Router
void masterKeyboard(unsigned char key, int x, int y) {
    // Direct numerical switching between all 5 scenarios
    if (key >= '1' && key <= '5') {
        currentScene = key - '0';

        // Re-initialize scene state when switched
        if (currentScene == 1) initScene1();
        if (currentScene == 2) initScene2();
        if (currentScene == 3) initScene3();
        if (currentScene == 4) initScene4();
        if (currentScene == 5) initScene5();

        glutPostRedisplay();
        return;
    }

    // Exit application
    if (key == 27) {
        exit(0);
    }

    // Route active scene-specific keys
    switch (currentScene) {
        case 1: keyboardScene1(key); break;
        case 2: keyboardScene2(key); break; // S, E, B, G, M
        case 3: keyboardScene3(key); break;
        case 4: keyboardScene4(key); break; // W, E, L
        case 5: keyboardScene5(key); break; // F, +, -, W, B, R
    }
}

// Reshape Callback
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 700);
    glutInitWindowPosition(50, 30);
    glutCreateWindow("Bus Journey Simulation - 5 Integrated Scenarios");

    // Initialize all scenes
    initScene1();
    initScene2();
    initScene3();
    initScene4();
    initScene5();

    // Register GLUT callbacks
    glutDisplayFunc(masterDisplay);
    glutKeyboardFunc(masterKeyboard);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, masterTimer, 0);

    glutMainLoop();
    return 0;
}
