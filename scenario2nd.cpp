/*#include <GL/glut.h>
#include <cmath>

// --- CAR VARIABLES ---
float car1X = 260;
float car2X = 280;
float car3X = 300;
float car7x = 310;
float car8x = 325;

float car4X = -20;
float car5X = -50;
float car6X = -100;
float car9x = -130;

bool carMoving = false;
bool carVisible = false;

// --- BUS VARIABLES ---
float buss = 280;
float bussy = 60;
float busss = 2.5;

bool bussMoving = false;
bool bussVisible = false;

float bussTarget = 100;
float bussTargety = 44;
float bussTargets = 3.8;

// --- COMMUTER PEDESTRIAN VARIABLES ---
float man1X = 130.0f, man1Y = 20.0f, man1S = 1.3f;
float man2X = 152.0f, man2Y = 19.0f, man2S = 1.4f;
float man3X = 145.0f, man3Y = 22.0f, man3S = 1.4f;
float man4X = 138.0f, man4Y = 21.0f, man4S = 1.25f;

bool manMoving = false;
bool manVisible = true;
float manProgress = 0.0f;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 250, 0, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawTree(float x, float y, float scale)
{
    glBegin(GL_POLYGON);
        glColor3f(0.45f, 0.28f, 0.15f);
        glVertex2f(x + 0.00f * scale, y + 0.00f * scale);
        glVertex2f(x + 0.35f * scale, y + 2.00f * scale);
        glVertex2f(x + 0.50f * scale, y + 3.90f * scale);
        glVertex2f(x + 0.30f * scale, y + 5.90f * scale);
        glVertex2f(x + 2.90f * scale, y + 5.80f * scale);
        glVertex2f(x + 2.65f * scale, y + 4.00f * scale);
        glVertex2f(x + 2.70f * scale, y + 2.10f * scale);
        glVertex2f(x + 3.25f * scale, y - 0.20f * scale);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3f(0.20f, 0.60f, 0.10f);
        glVertex2f(x + 0.40f * scale, y + 5.10f * scale);
        glVertex2f(x - 1.00f * scale, y + 3.60f * scale);
        glVertex2f(x - 4.05f * scale, y + 3.30f * scale);
        glVertex2f(x - 6.00f * scale, y + 6.20f * scale);
        glVertex2f(x - 8.75f * scale, y + 9.00f * scale);
        glVertex2f(x - 7.65f * scale, y + 13.50f * scale);
        glVertex2f(x - 6.90f * scale, y + 16.50f * scale);
        glVertex2f(x - 6.90f * scale, y + 19.00f * scale);
        glVertex2f(x - 4.80f * scale, y + 19.60f * scale);
        glVertex2f(x - 3.40f * scale, y + 21.60f * scale);
        glVertex2f(x - 0.45f * scale, y + 22.80f * scale);
        glVertex2f(x + 2.35f * scale, y + 22.90f * scale);
        glVertex2f(x + 4.10f * scale, y + 22.80f * scale);
        glVertex2f(x + 6.25f * scale, y + 24.00f * scale);
        glVertex2f(x + 8.45f * scale, y + 22.90f * scale);
        glVertex2f(x + 9.95f * scale, y + 20.00f * scale);
        glVertex2f(x + 11.30f * scale, y + 18.70f * scale);
        glVertex2f(x + 12.85f * scale, y + 16.70f * scale);
        glVertex2f(x + 13.75f * scale, y + 14.00f * scale);
        glVertex2f(x + 13.30f * scale, y + 11.20f * scale);
        glVertex2f(x + 12.30f * scale, y + 8.00f * scale);
        glVertex2f(x + 10.20f * scale, y + 6.20f * scale);
        glVertex2f(x + 8.25f * scale, y + 6.50f * scale);
        glVertex2f(x + 7.05f * scale, y + 8.70f * scale);
        glVertex2f(x + 5.70f * scale, y + 8.00f * scale);
        glVertex2f(x + 4.55f * scale, y + 5.90f * scale);
        glVertex2f(x + 1.40f * scale, y + 6.30f * scale);
    glEnd();
}

void roadB(float x, float y, float z)
{
    glBegin(GL_QUADS);
        glColor3f(0.95f, 0.20f, 0.05f);

        // 1st quad
        glVertex2f(x - 1.0f * z, y + 0.0f * z);
        glVertex2f(x - 1.0f * z, y + 4.0f * z);
        glVertex2f(x - 1.2f * z, y + 4.0f * z);
        glVertex2f(x - 1.2f * z, y + 0.0f * z);

        // 2nd quad (Fixed degenerate width)
        glVertex2f(x - 2.4f * z, y + 0.0f * z);
        glVertex2f(x - 2.4f * z, y + 4.0f * z);
        glVertex2f(x - 2.2f * z, y + 4.0f * z);
        glVertex2f(x - 2.2f * z, y + 0.0f * z);

        // 3rd quad
        glVertex2f(x - 0.8f * z, y + 3.6f * z);
        glVertex2f(x - 0.8f * z, y + 4.0f * z);
        glVertex2f(x - 4.2f * z, y + 4.0f * z);
        glVertex2f(x - 4.2f * z, y + 3.6f * z);

        // 4th quad
        glVertex2f(x - 4.0f * z, y + 0.0f * z);
        glVertex2f(x - 4.0f * z, y + 4.0f * z);
        glVertex2f(x - 3.8f * z, y + 4.0f * z);
        glVertex2f(x - 3.8f * z, y + 0.0f * z);

        // 5th quad
        glVertex2f(x - 4.0f * z, y + 2.0f * z);
        glVertex2f(x - 1.0f * z, y + 2.0f * z);
        glVertex2f(x - 1.0f * z, y + 2.4f * z);
        glVertex2f(x - 4.0f * z, y + 2.4f * z);
    glEnd();
}

void drawCar(float x, float y, float s)
{
    glBegin(GL_QUADS);
        glColor3f(0.95f, 0.75f, 0.05f);
        glVertex2f(x,        y);
        glVertex2f(x + 10*s, y);
        glVertex2f(x + 10*s, y + 3*s);
        glVertex2f(x,        y + 3*s);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.85f, 0.15f);
        glVertex2f(x + 2*s, y + 3*s);
        glVertex2f(x + 3*s, y + 5*s);
        glVertex2f(x + 7*s, y + 5*s);
        glVertex2f(x + 8*s, y + 3*s);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.2f, 0.3f, 0.4f);
        glVertex2f(x + 5.1f*s, y + 3.2f*s);
        glVertex2f(x + 7.0f*s, y + 3.2f*s);
        glVertex2f(x + 6.6f*s, y + 4.5f*s);
        glVertex2f(x + 5.1f*s, y + 4.5f*s);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.2f, 0.3f, 0.4f);
        glVertex2f(x + 3.0f*s, y + 3.2f*s);
        glVertex2f(x + 4.9f*s, y + 3.2f*s);
        glVertex2f(x + 4.9f*s, y + 4.5f*s);
        glVertex2f(x + 3.4f*s, y + 4.5f*s);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.15f, 0.15f, 0.15f);
        glVertex2f(x,        y + 0.4f*s);
        glVertex2f(x + 10*s, y + 0.4f*s);
        glVertex2f(x + 10*s, y + 1.0f*s);
        glVertex2f(x,        y + 1.0f*s);
    glEnd();

    // Wheels
    glColor3f(0.05f, 0.05f, 0.05f);
    glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i += 30)
        {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(x + 2.5f*s + cosf(angle) * 1.0f*s, y + sinf(angle) * 1.0f*s);
        }
    glEnd();

    glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i += 30)
        {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(x + 7.5f*s + cosf(angle) * 1.0f*s, y + sinf(angle) * 1.0f*s);
        }
    glEnd();
}

void drawBus(float x, float y, float s)
{
    glBegin(GL_QUADS);
        glColor3f(0.85f, 0.12f, 0.08f);
        glVertex2f(x,        y);
        glVertex2f(x + 20*s, y);
        glVertex2f(x + 19*s, y + 8*s);
        glVertex2f(x + 1*s,  y + 8*s);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.70f, 0.08f, 0.06f);
        glVertex2f(x,        y);
        glVertex2f(x + 20*s, y);
        glVertex2f(x + 20*s, y + 1.2f*s);
        glVertex2f(x,        y + 1.2f*s);
    glEnd();

    glColor3f(0.75f, 0.90f, 0.93f);
    // Window 1
    glBegin(GL_QUADS);
        glVertex2f(x + 1.5f*s, y + 4*s);
        glVertex2f(x + 5.5f*s, y + 4*s);
        glVertex2f(x + 5.5f*s, y + 7*s);
        glVertex2f(x + 1.5f*s, y + 7*s);
    glEnd();

    // Window 2
    glBegin(GL_QUADS);
        glVertex2f(x + 6*s,  y + 4*s);
        glVertex2f(x + 10*s, y + 4*s);
        glVertex2f(x + 10*s, y + 7*s);
        glVertex2f(x + 6*s,  y + 7*s);
    glEnd();

    // Open Door
    glBegin(GL_QUADS);
        glVertex2f(x + 11.0f*s, y + 1.2f*s);
        glVertex2f(x + 12.5f*s, y + 1.2f*s);
        glVertex2f(x + 12.5f*s, y + 7.0f*s);
        glVertex2f(x + 11.0f*s, y + 7.0f*s);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(x + 13.2f*s, y + 1.2f*s);
        glVertex2f(x + 14.7f*s, y + 1.2f*s);
        glVertex2f(x + 14.7f*s, y + 7.0f*s);
        glVertex2f(x + 13.2f*s, y + 7.0f*s);
    glEnd();

    glColor3f(0.10f, 0.10f, 0.10f);
    glBegin(GL_QUADS);
        glVertex2f(x + 12.5f*s, y + 1.2f*s);
        glVertex2f(x + 13.2f*s, y + 1.2f*s);
        glVertex2f(x + 13.2f*s, y + 7.0f*s);
        glVertex2f(x + 12.5f*s, y + 7.0f*s);
    glEnd();

    // Front window
    glColor3f(0.75f, 0.90f, 0.93f);
    glBegin(GL_QUADS);
        glVertex2f(x + 15.2f*s, y + 4*s);
        glVertex2f(x + 18.0f*s, y + 4*s);
        glVertex2f(x + 18.0f*s, y + 7*s);
        glVertex2f(x + 15.2f*s, y + 7*s);
    glEnd();

    // Headlight
    glColor3f(1.0f, 0.75f, 0.10f);
    glBegin(GL_QUADS);
        glVertex2f(x + 19*s, y + 3*s);
        glVertex2f(x + 20*s, y + 3*s);
        glVertex2f(x + 20*s, y + 4*s);
        glVertex2f(x + 19*s, y + 4*s);
    glEnd();

    // Wheels
    glColor3f(0.05f, 0.05f, 0.05f);
    glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i += 30) {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(x + 4*s + cosf(angle) * 1.7f*s, y - 0.2f*s + sinf(angle) * 1.7f*s);
        }
    glEnd();

    glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i += 30) {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(x + 16*s + cosf(angle) * 1.7f*s, y - 0.2f*s + sinf(angle) * 1.7f*s);
        }
    glEnd();

    // Hubcaps
    glColor3f(0.85f, 0.75f, 0.65f);
    glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i += 30) {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(x + 4*s + cosf(angle) * 0.8f*s, y - 0.2f*s + sinf(angle) * 0.8f*s);
        }
    glEnd();

    glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i += 30) {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(x + 16*s + cosf(angle) * 0.8f*s, y - 0.2f*s + sinf(angle) * 0.8f*s);
        }
    glEnd();
}

void drawWindow(float x1, float y1, float x2, float y2)
{
    glBegin(GL_QUADS);
        glColor3f(0.30f, 0.30f, 0.30f);
        glVertex2f(x1, y1);
        glVertex2f(x1, y2);
        glVertex2f(x2, y2);
        glVertex2f(x2, y1);
    glEnd();

    glBegin(GL_LINES);
        glColor3f(1, 1, 1);
        glVertex2f(x1, (y1 + y2) / 2);
        glVertex2f(x2, (y1 + y2) / 2);
        glVertex2f((x1 + x2) / 2, y1);
        glVertex2f((x1 + x2) / 2, y2);
    glEnd();
}

void drawWindow2(float x1, float y1, float x2, float y2)
{
    glBegin(GL_QUADS);
        glColor3f(0.10f, 0.10f, 0.10f);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.65f, 0.80f, 0.85f);
        glVertex2f(x1 + 0.8f, y1 + 0.8f);
        glVertex2f(x2 - 0.8f, y1 + 0.8f);
        glVertex2f(x2 - 0.8f, y2 - 0.8f);
        glVertex2f(x1 + 0.8f, y2 - 0.8f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.10f, 0.10f, 0.10f);
        glVertex2f((x1+x2)/2 - 0.4f, y1);
        glVertex2f((x1+x2)/2 + 0.4f, y1);
        glVertex2f((x1+x2)/2 + 0.4f, y2);
        glVertex2f((x1+x2)/2 - 0.4f, y2);

        glVertex2f(x1, (y1+y2)/2 - 0.4f);
        glVertex2f(x2, (y1+y2)/2 - 0.4f);
        glVertex2f(x2, (y1+y2)/2 + 0.4f);
        glVertex2f(x1, (y1+y2)/2 + 0.4f);
    glEnd();
}

void building()
{
    // Building 1
    glBegin(GL_QUADS);
        glColor3f(0.75f, 0.55f, 0.35f);
        glVertex2f(0.0f,  96.6f);
        glVertex2f(0.0f,  143.8f);
        glVertex2f(39.2f, 143.8f);
        glVertex2f(39.7f, 94.0f);

        glColor3f(0.45f, 0.28f, 0.15f);
        glVertex2f(39.7f, 94.0f);
        glVertex2f(39.2f, 143.8f);
        glVertex2f(51.6f, 136.2f);
        glVertex2f(51.9f, 93.2f);
    glEnd();

    // Building 1 horizontal design
    glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(39.6f, 106.8f);
        glVertex2f(39.6f, 109.0f);
        glVertex2f(0.0f,  112.6f);
        glVertex2f(0.0f,  111.4f);

        glVertex2f(39.4f, 123.0f);
        glVertex2f(39.4f, 125.2f);
        glVertex2f(0.0f,  130.2f);
        glVertex2f(0.0f,  129.0f);
    glEnd();

    // Attached High-Rise Complex
    glBegin(GL_QUADS);
        glColor3f(0.800f, 0.824f, 0.843f);
        glVertex2f(100.0f, 90.0f);
        glVertex2f(100.0f, 160.0f);
        glVertex2f(120.0f, 160.0f);
        glVertex2f(120.0f, 88.6f);

        glColor3f(0.914f, 0.941f, 0.969f);
        glVertex2f(120.0f, 88.6f);
        glVertex2f(120.0f, 180.0f);
        glVertex2f(150.0f, 180.0f);
        glVertex2f(150.0f, 86.6f);

        glColor3f(0.800f, 0.824f, 0.843f);
        glVertex2f(150.0f, 86.6f);
        glVertex2f(150.0f, 180.0f);
        glVertex2f(170.0f, 160.0f);
        glVertex2f(170.0f, 85.2f);

        glColor3f(0.914f, 0.941f, 0.969f);
        glVertex2f(170.0f, 85.2f);
        glVertex2f(170.0f, 140.0f);
        glVertex2f(190.0f, 140.0f);
        glVertex2f(190.0f, 84.0f);

        glVertex2f(79.6f,  91.2f);
        glVertex2f(79.8f,  152.2f);
        glVertex2f(100.0f, 151.4f);
        glVertex2f(100.0f, 90.0f);

        glVertex2f(190.0f, 84.0f);
        glVertex2f(190.0f, 180.0f);
        glVertex2f(210.0f, 180.0f);
        glVertex2f(210.0f, 82.6f);

        glColor3f(0.800f, 0.824f, 0.843f);
        glVertex2f(210.0f, 82.6f);
        glVertex2f(210.0f, 180.0f);
        glVertex2f(227.8f, 170.0f);
        glVertex2f(228.0f, 81.4f);

        glColor3f(0.914f, 0.941f, 0.969f);
        glVertex2f(228.0f, 81.4f);
        glVertex2f(228.0f, 188.0f);
        glVertex2f(250.0f, 191.8f);
        glVertex2f(250.0f, 80.0f);
    glEnd();

    for(int y = 100; y <= 146; y += 10) {
        drawWindow(82, y, 85, y + 6);
        drawWindow(87, y, 90, y + 6);
        drawWindow(92, y, 95, y + 6);
        drawWindow(97, y, 99, y + 6);
    }
    for(int y = 100; y <= 158; y += 10) {
        drawWindow2(102, y, 105, y + 6);
        drawWindow2(107, y, 110, y + 6);
        drawWindow2(112, y, 115, y + 6);
        drawWindow2(117, y, 119, y + 6);
    }
    for(int y = 98; y <= 170; y += 11) {
        drawWindow(123, y, 127, y + 7);
        drawWindow(129, y, 133, y + 7);
        drawWindow(136, y, 140, y + 7);
        drawWindow(143, y, 147, y + 7);
    }
    for(int y = 88; y <= 155; y += 9) {
        drawWindow2(152, y, 156, y + 6);
        drawWindow2(157, y, 161, y + 6);
        drawWindow2(163, y, 166, y + 6);
        drawWindow2(167, y, 169, y + 6);
    }
    for(int y = 91; y <= 135; y += 10) {
        drawWindow(172, y, 176, y + 6);
        drawWindow(177, y, 181, y + 6);
        drawWindow(182, y, 186, y + 6);
        drawWindow(187, y, 189, y + 6);
    }
    for(int y = 90; y <= 175; y += 10) {
        drawWindow2(192, y, 196, y + 6);
        drawWindow2(197, y, 201, y + 6);
        drawWindow2(202, y, 206, y + 6);
        drawWindow2(207, y, 209, y + 6);
    }
    for(int y = 89; y <= 166; y += 11) {
        drawWindow(212, y, 216, y + 7);
        drawWindow(217, y, 220, y + 7);
        drawWindow(221, y, 224, y + 7);
        drawWindow(225, y, 227, y + 7);
    }
    for(int y = 88; y <= 176; y += 12) {
        drawWindow2(230, y, 234, y + 7);
        drawWindow2(235, y, 239, y + 7);
        drawWindow2(241, y, 245, y + 7);
        drawWindow2(246, y, 249, y + 7);
    }
}

void carvisi()
{
    if(carVisible)
    {
        drawCar(car1X, 49, 1.4f);
        drawCar(car8x, 45, 2.5f);
        drawCar(car2X, 40, 2.5f);
        drawCar(car3X, 49, 1.3f);
        drawCar(car7x, 42, 2.4f);

        drawCar(car4X, 70, 2.2f);
        drawCar(car5X, 75, 2.9f);
        drawCar(car6X, 73, 2.5f);
        drawCar(car9x, 72, 2.8f);
    }
}

void bussvisi()
{
    if(bussVisible) {
        drawBus(buss, bussy, busss);
    }
}

void drawMan(float x, float y, float s)
{
    const float PI = 3.14159265f;
    int segments = 40;

    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(s, s, 1.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(6.8f, 2.0f);
        glVertex2f(9.5f, 2.0f);
        glVertex2f(9.5f, 10.0f);
        glVertex2f(6.8f, 10.0f);

        glVertex2f(10.5f, 2.0f);
        glVertex2f(13.2f, 2.0f);
        glVertex2f(13.2f, 10.0f);
        glVertex2f(10.5f, 10.0f);

        glVertex2f(5.0f,  0.0f);
        glVertex2f(9.6f,  0.0f);
        glVertex2f(9.6f,  2.0f);
        glVertex2f(5.0f,  2.0f);

        glVertex2f(10.4f, 0.0f);
        glVertex2f(15.0f, 0.0f);
        glVertex2f(15.0f, 2.0f);
        glVertex2f(10.4f, 2.0f);
    glEnd();

    glColor3f(0.96f, 0.77f, 0.62f);
    glBegin(GL_QUADS);
        glVertex2f(4.2f,  11.0f);
        glVertex2f(6.0f,  11.0f);
        glVertex2f(6.0f,  13.0f);
        glVertex2f(4.2f,  13.0f);

        glVertex2f(14.0f, 11.0f);
        glVertex2f(15.8f, 11.0f);
        glVertex2f(15.8f, 13.0f);
        glVertex2f(14.0f, 13.0f);
    glEnd();

    glColor3f(0.16f, 0.44f, 0.74f);
    glBegin(GL_QUADS);
        glVertex2f(4.2f,  13.0f);
        glVertex2f(6.0f,  13.0f);
        glVertex2f(6.0f,  22.5f);
        glVertex2f(4.2f,  22.5f);

        glVertex2f(14.0f, 13.0f);
        glVertex2f(15.8f, 13.0f);
        glVertex2f(15.8f, 22.5f);
        glVertex2f(14.0f, 22.5f);

        glVertex2f(5.9f,  10.0f);
        glVertex2f(14.1f, 10.0f);
        glVertex2f(14.1f, 22.0f);
        glVertex2f(5.9f,  22.0f);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(10.0f, 21.0f);
        for (int i = 0; i <= segments; i++) {
            float a = PI * (float)i / (float)segments;
            glVertex2f(10.0f + 4.1f * cosf(a), 21.0f + 4.1f * sinf(a));
        }
    glEnd();

    // Head
    glColor3f(0.96f, 0.77f, 0.62f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(10.0f, 29.5f);
        for (int i = 0; i <= segments; i++) {
            float a = 2.0f * PI * (float)i / (float)segments;
            glVertex2f(10.0f + 4.3f * cosf(a), 29.5f + 4.3f * sinf(a));
        }
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i <= segments; i++) {
            float a = 2.0f * PI * (float)i / (float)segments;
            glVertex2f(10.0f + 4.3f * cosf(a), 29.5f + 4.3f * sinf(a));
        }
    glEnd();

    glPopMatrix();
}

void moveMan()
{
    if(manMoving && manVisible)
    {
        manProgress += 0.01f;
        if(manProgress >= 1.0f) {
            manProgress = 1.0f;
        }

        man1X = 130.0f + (150.0f - 130.0f) * manProgress;
        man1Y = 20.0f  + (48.0f  - 20.0f)  * manProgress;
        man1S = 1.3f   + (0.5f   - 1.3f)   * manProgress;

        man2X = 152.0f + (150.0f - 152.0f) * manProgress;
        man2Y = 19.0f  + (48.0f  - 19.0f)  * manProgress;
        man2S = 1.4f   + (0.5f   - 1.4f)   * manProgress;

        man3X = 145.0f + (150.0f - 145.0f) * manProgress;
        man3Y = 22.0f  + (48.0f  - 22.0f)  * manProgress;
        man3S = 1.4f   + (0.5f   - 1.4f)   * manProgress;

        man4X = 138.0f + (150.0f - 138.0f) * manProgress;
        man4Y = 21.0f  + (48.0f  - 21.0f)  * manProgress;
        man4S = 1.25f  + (0.5f   - 1.25f)  * manProgress;

        if(manProgress >= 1.0f)
        {
            manMoving = false;
            manVisible = false;
        }
        glutPostRedisplay();
    }
}

void manvisi()
{
    if(manVisible) {
        drawMan(man1X, man1Y, man1S);
        drawMan(man2X, man2Y, man2S);
        drawMan(man3X, man3Y, man3S);
        drawMan(man4X, man4Y, man4S);
    }
}

void drawCircle(float cx, float cy, float rad, int seg)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < seg; i++) {
        float angle = 2.0f * 3.14159f * i / seg;
        glVertex2f(cx + rad * cosf(angle), cy + rad * sinf(angle));
    }
    glEnd();
}

void drawCloud(float x, float y)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, y, 5.0f, 20);
    drawCircle(x + 6.0f, y + 2.0f, 6.5f, 20);
    drawCircle(x + 12.0f, y, 5.0f, 20);
}

void drawGrass(float x, float y, float z)
{
    glColor3f(0.45f, 0.75f, 0.12f);
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x - 1.2f*z, y + 4.5f*z);
        glVertex2f(x - 0.7f*z, y + 4.2f*z);
        glVertex2f(x + 0.2f*z, y + 0.5f*z);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x - 2.0f*z, y + 3.0f*z);
        glVertex2f(x - 1.7f*z, y + 3.3f*z);
        glVertex2f(x + 0.1f*z, y + 0.4f*z);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(x + 0.3f*z, y);
        glVertex2f(x + 1.8f*z, y + 4.8f*z);
        glVertex2f(x + 2.0f*z, y + 5.0f*z);
        glVertex2f(x + 1.0f*z, y + 0.4f*z);
    glEnd();

    glColor3f(0.30f, 0.65f, 0.08f);
    glBegin(GL_POLYGON);
        glVertex2f(x - 0.5f*z, y);
        glVertex2f(x - 1.5f*z, y + 1.8f*z);
        glVertex2f(x - 1.2f*z, y + 2.0f*z);
        glVertex2f(x, y + 0.3f*z);
    glEnd();
}

void background2nd()
{
    // Sky
    glBegin(GL_QUADS);
        glColor3f(0.53f, 0.81f, 0.98f);
        glVertex2f(0.0f,   130.0f);
        glVertex2f(0.0f,   200.0f);
        glVertex2f(250.0f, 200.0f);
        glVertex2f(250.0f, 140.0f);
    glEnd();

    // Road
    glBegin(GL_QUADS);
        glColor3f(0.20f, 0.20f, 0.20f);
        glVertex2f(250.0f, 40.0f);
        glVertex2f(0.0f,   20.0f);
        glVertex2f(0.0f,   96.6f);
        glVertex2f(250.0f, 80.0f);
    glEnd();

    // Clouds
    drawCloud(130, 190);
    drawCloud(145, 190);
    drawCloud(110, 180);
    drawCloud(170, 180);
    drawCloud(90,  160);
    drawCloud(80,  190);
    drawCloud(200, 185);
    drawCloud(50,  165);
    drawCloud(220, 180);

    // Sun
    glColor3f(1.00f, 0.85f, 0.10f);
    drawCircle(20, 185, 8, 100);

    // Front ground
    glBegin(GL_QUADS);
        glColor3f(0.20f, 0.60f, 0.10f);
        glVertex2f(0.0f,   0.0f);
        glVertex2f(0.0f,   20.0f);
        glVertex2f(250.0f, 40.0f);
        glVertex2f(250.0f, 0.0f);
    glEnd();

    // Grass
    drawGrass(190, 20, 1.2f);
    drawGrass(210, 20, 1.2f);
    drawGrass(230, 20, 1.2f);

    for (int x = 0; x <= 250; x += 12) {
        drawGrass(x, 9, 1.1f);
    }
}

void display2nd()
{
    // Re-assert orthogonal bounds specifically for Scene 2
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 250, 0, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    background2nd();
    building();

    drawTree(67.5f, 92.0f, 2.2f);
    drawTree(112.7f, 89.0f, 1.0f);
    drawTree(125.3f, 88.2f, 0.80f);
    drawTree(131.0f, 87.8f, 1.2f);
    drawTree(140.9f, 87.2f, 0.6f);
    drawTree(150.0f, 86.6f, 1.0f);
    drawTree(170.1f, 85.2f, 1.5f);
    drawTree(228.0f, 81.04f, 1.7f);
    drawTree(201.7f, 83.2f, 1.0f);

    carvisi();

    float z = 1.00f;
    for(int i = 250; i > 3; i -= 7) {
        roadB(i, 60, z);
        z += 0.05f;
        if(i < 110) i -= 3;
    }

    bussvisi();
    manvisi();

    glutSwapBuffers(); // Tear-free buffer presentation
}

void update(int value)
{
    if(carMoving && carVisible)
    {
        car1X -= 0.5f;
        car2X -= 0.5f;
        car3X -= 0.5f;
        car7x -= 0.5f;
        car8x -= 0.7f;

        if(car1X < -12) car1X = 260;
        if(car2X < -14) car2X = 280;
        if(car3X < -17) car3X = 300;
        if(car7x < -20) car7x = 310; // FIXED: assigned to car7x
        if(car8x < -23) car8x = 325; // FIXED: assigned to car8x

        car4X += 0.5f;
        car5X += 0.5f;
        car6X += 0.5f;
        car9x += 0.5f;

        if(car4X > 250) car4X = -25;
        if(car5X > 250) car5X = -35;
        if(car6X > 250) car6X = -45;
        if(car9x > 250) car9x = -55; // FIXED: comparison operator & assigned to car9x

        glutPostRedisplay();
    }
    glutTimerFunc(16, update, 0);
}

void updateB(int value)
{
    if(bussMoving && bussVisible)
    {
        buss  -= 0.3f;
        bussy -= 0.02469f;
        busss += 0.002292f;

        if(buss <= bussTarget)
        {
            buss = bussTarget;
            bussy = bussTargety;
            busss = 4.0f;
            bussMoving = false;
        }
        glutPostRedisplay();
    }
    glutTimerFunc(16, updateB, 0);
}

void updateMan(int value)
{
    moveMan();
    glutTimerFunc(16, updateMan, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    if(key == 's' || key == 'S') {
        carVisible = true;
        carMoving = true;
        glutPostRedisplay();
    }
    if(key == 'e' || key == 'E') {
        carMoving = false;
        carVisible = false;
        glutPostRedisplay();
    }
    if(key == 'b' || key == 'B') {
        buss = 300;
        bussy = 60;
        busss = 2.5f;
        bussTarget = 100;
        bussTargety = 44;
        bussTargets = 4.0f;
        bussVisible = true;
        bussMoving = true;
        glutPostRedisplay();
    }
    if(key == 'g' || key == 'G') {
        buss = bussTarget;
        bussy = bussTargety;
        busss = 4.0f;
        bussTarget = -80;
        bussVisible = true;
        bussMoving = true;
        glutPostRedisplay();
    }
    if(key == 'm' || key == 'M') {
        man1X = 130.0f; man1Y = 20.0f; man1S = 1.3f;
        man2X = 152.0f; man2Y = 19.0f; man2S = 1.4f;
        man3X = 145.0f; man3Y = 22.0f; man3S = 1.4f;
        man4X = 138.0f; man4Y = 21.0f; man4S = 1.25f;
        manProgress = 0.0f;
        manVisible = true;
        manMoving = true;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Double buffered
    glutInitWindowSize(1200, 700);
    glutInitWindowPosition(50, 30);
    glutCreateWindow("Bus Journey Scenario - Scene 2");

    init();

    glutDisplayFunc(display2nd);
    glutKeyboardFunc(keyboard);

    glutTimerFunc(16, update, 0);
    glutTimerFunc(16, updateB, 0);
    glutTimerFunc(16, updateMan, 0);

    glutMainLoop();
    return 0;
}
*/
