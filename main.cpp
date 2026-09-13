#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;


//Car

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


//Buss

float buss = 280;
float bussy = 60;
float busss = 2.5;


bool bussMoving = false;
bool bussVisible = false;

float bussTarget = 100;
float bussTargety = 44;
float bussTargets = 3.8;


// Man
float man1X = 130.0f, man1Y = 20.0f, man1S = 1.3f;
float man2X = 152.0f, man2Y = 19.0f, man2S = 1.4f;
float man3X = 145.0f, man3Y = 22.0f, man3S = 1.4f;
float man4X = 138.0f, man4Y = 21.0f, man4S = 1.25f;

bool manMoving = false;
bool manVisible = true;

// Animation progress
float manProgress = 0.0f;


void init()
{
    glClearColor(1.0, 1.0, 1.0 , 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,250,0,200);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void drawTree(float x, float y, float scale)
{
    glBegin(GL_POLYGON);
        glColor3f(0.45, 0.28, 0.15);

        glVertex2f(x + 0.00 * scale, y + 0.00 * scale);
        glVertex2f(x + 0.35 * scale, y + 2.00 * scale);
        glVertex2f(x + 0.50 * scale, y + 3.90 * scale);
        glVertex2f(x + 0.30 * scale, y + 5.90 * scale);
        glVertex2f(x + 2.90 * scale, y + 5.80 * scale);
        glVertex2f(x + 2.65 * scale, y + 4.00 * scale);
        glVertex2f(x + 2.70 * scale, y + 2.10 * scale);
        glVertex2f(x + 3.25 * scale, y - 0.20 * scale);

    glEnd();


    glBegin(GL_POLYGON);
        glColor3f(0.20, 0.60, 0.10);

        glVertex2f(x + 0.40 * scale, y + 5.10 * scale);
        glVertex2f(x - 1.00 * scale, y + 3.60 * scale);
        glVertex2f(x - 4.05 * scale, y + 3.30 * scale);
        glVertex2f(x - 6.00 * scale, y + 6.20 * scale);
        glVertex2f(x - 8.75 * scale, y + 9.00 * scale);
        glVertex2f(x - 7.65 * scale, y + 13.50 * scale);
        glVertex2f(x - 6.90 * scale, y + 16.50 * scale);
        glVertex2f(x - 6.90 * scale, y + 19.00 * scale);
        glVertex2f(x - 4.80 * scale, y + 19.60 * scale);
        glVertex2f(x - 3.40 * scale, y + 21.60 * scale);
        glVertex2f(x - 0.45 * scale, y + 22.80 * scale);
        glVertex2f(x + 2.35 * scale, y + 22.90 * scale);
        glVertex2f(x + 4.10 * scale, y + 22.80 * scale);
        glVertex2f(x + 6.25 * scale, y + 24.00 * scale);
        glVertex2f(x + 8.45 * scale, y + 22.90 * scale);
        glVertex2f(x + 9.95 * scale, y + 20.00 * scale);
        glVertex2f(x + 11.30 * scale, y + 18.70 * scale);
        glVertex2f(x + 12.85 * scale, y + 16.70 * scale);
        glVertex2f(x + 13.75 * scale, y + 14.00 * scale);
        glVertex2f(x + 13.30 * scale, y + 11.20 * scale);
        glVertex2f(x + 12.30 * scale, y + 8.00 * scale);
        glVertex2f(x + 10.20 * scale, y + 6.20 * scale);
        glVertex2f(x + 8.25 * scale, y + 6.50 * scale);
        glVertex2f(x + 7.05 * scale, y + 8.70 * scale);
        glVertex2f(x + 5.70 * scale, y + 8.00 * scale);
        glVertex2f(x + 4.55 * scale, y + 5.90 * scale);
        glVertex2f(x + 1.40 * scale, y + 6.30 * scale);

    glEnd();
}

void roadB(float x, float y, float z)
{
    glBegin(GL_QUADS);

        glColor3f(0.95, 0.20, 0.05);

        // 1st quad
        glVertex2f(x - 1.0 * z, y + 0.0 * z);
        glVertex2f(x - 1.0 * z, y + 4.0 * z);
        glVertex2f(x - 1.2 * z, y + 4.0 * z);
        glVertex2f(x - 1.2 * z, y + 0.0 * z);


        // 2nd quad
        glVertex2f(x - 2.4 * z, y + 0.0 * z);
        glVertex2f(x - 2.4 * z, y + 4.0 * z);
        glVertex2f(x - 2.4 * z, y + 4.0 * z);
        glVertex2f(x - 2.4 * z, y + 0.0 * z);


        // 3rd quad
        glVertex2f(x - 0.8 * z, y + 3.6 * z);
        glVertex2f(x - 0.8 * z, y + 4.0 * z);
        glVertex2f(x - 4.2 * z, y + 4.0 * z);
        glVertex2f(x - 4.2 * z, y + 3.6 * z);


        // 4th quad
        glVertex2f(x - 4.0 * z, y + 0.0 * z);
        glVertex2f(x - 4.0 * z, y + 4.0 * z);
        glVertex2f(x - 4.0 * z, y + 4.0 * z);
        glVertex2f(x - 3.8 * z, y + 0.0 * z);


        // 5th quad
        glVertex2f(x - 4.0 * z, y + 2.0 * z);
        glVertex2f(x - 1.0 * z, y + 2.0 * z);
        glVertex2f(x - 1.0 * z, y + 2.4 * z);
        glVertex2f(x - 4.0 * z, y + 2.4 * z);

    glEnd();
}


void drawCar(float x, float y, float s)
{
    // Lower body
    glBegin(GL_QUADS);
        glColor3f(0.95, 0.75, 0.05);

        glVertex2f(x,          y);
        glVertex2f(x + 10*s,   y);
        glVertex2f(x + 10*s,   y + 3*s);
        glVertex2f(x,          y + 3*s);
    glEnd();

    // Upper roof/cabin
    glBegin(GL_POLYGON);
        glColor3f(1.0, 0.85, 0.15);

        glVertex2f(x + 2*s, y + 3*s);
        glVertex2f(x + 3*s, y + 5*s);
        glVertex2f(x + 7*s, y + 5*s);
        glVertex2f(x + 8*s, y + 3*s);
    glEnd();

    // Rear window: Tinted blue-gray
    glBegin(GL_QUADS);
        glColor3f(0.2, 0.3, 0.4);

        glVertex2f(x + 5.1*s, y + 3.2*s);
        glVertex2f(x + 7.0*s, y + 3.2*s);
        glVertex2f(x + 6.6*s, y + 4.5*s);
        glVertex2f(x + 5.1*s, y + 4.5*s);
    glEnd();

    // Front window: Tinted blue-gray
    glBegin(GL_QUADS);
        glColor3f(0.2, 0.3, 0.4);

        glVertex2f(x + 3.0*s, y + 3.2*s);
        glVertex2f(x + 4.9*s, y + 3.2*s);
        glVertex2f(x + 4.9*s, y + 4.5*s);
        glVertex2f(x + 3.4*s, y + 4.5*s);
    glEnd();

    // Lower trim stripe
    glBegin(GL_QUADS);
        glColor3f(0.15, 0.15, 0.15);

        glVertex2f(x,          y + 0.4*s);
        glVertex2f(x + 10*s,   y + 0.4*s);
        glVertex2f(x + 10*s,   y + 1.0*s);
        glVertex2f(x,          y + 1.0*s);
    glEnd();


    glBegin(GL_POLYGON);
        glColor3f(0.05, 0.05, 0.05);

        for(int i = 0; i < 360; i += 30)
        {
            float angle = i * 3.14159 / 180.0;

            glVertex2f(
                x + 2.5*s + cos(angle) * 1.0*s,
                y + sin(angle) * 1.0*s
            );
        }
    glEnd();


    glBegin(GL_POLYGON);
        glColor3f(0.05, 0.05, 0.05);

        for(int i = 0; i < 360; i += 30)
        {
            float angle = i * 3.14159 / 180.0;

            glVertex2f(
                x + 7.5*s + cos(angle) * 1.0*s,
                y + sin(angle) * 1.0*s
            );
        }
    glEnd();
}


void drawBus(float x, float y, float s)
{
    // Bus body
    glBegin(GL_QUADS);
        glColor3f(0.85, 0.12, 0.08);

        glVertex2f(x, y);
        glVertex2f(x + 20*s, y);
        glVertex2f(x + 19*s, y + 8*s);
        glVertex2f(x + 1*s, y + 8*s);
    glEnd();


    // Lower part of bus
    glBegin(GL_QUADS);
        glColor3f(0.70, 0.08, 0.06);

        glVertex2f(x, y);
        glVertex2f(x + 20*s, y);
        glVertex2f(x + 20*s, y + 1.2*s);
        glVertex2f(x, y + 1.2*s);
    glEnd();


    // Window 1
    glBegin(GL_QUADS);
        glColor3f(0.75, 0.90, 0.93);

        glVertex2f(x + 1.5*s, y + 4*s);
        glVertex2f(x + 5.5*s, y + 4*s);
        glVertex2f(x + 5.5*s, y + 7*s);
        glVertex2f(x + 1.5*s, y + 7*s);
    glEnd();


    // Window 2
    glBegin(GL_QUADS);
        glColor3f(0.75, 0.90, 0.93);

        glVertex2f(x + 6*s, y + 4*s);
        glVertex2f(x + 10*s, y + 4*s);
        glVertex2f(x + 10*s, y + 7*s);
        glVertex2f(x + 6*s, y + 7*s);
    glEnd();


    // Open Door - left side
    glBegin(GL_QUADS);
        glColor3f(0.75, 0.90, 0.93);

        glVertex2f(x + 11*s, y + 1.2*s);
        glVertex2f(x + 12.5*s, y + 1.2*s);
        glVertex2f(x + 12.5*s, y + 7*s);
        glVertex2f(x + 11*s, y + 7*s);
    glEnd();


    // Open Door - right side
    glBegin(GL_QUADS);
        glColor3f(0.75, 0.90, 0.93);

        glVertex2f(x + 13.2*s, y + 1.2*s);
        glVertex2f(x + 14.7*s, y + 1.2*s);
        glVertex2f(x + 14.7*s, y + 7*s);
        glVertex2f(x + 13.2*s, y + 7*s);
    glEnd();


    // Door black gap
    glBegin(GL_QUADS);
        glColor3f(0.10, 0.10, 0.10);

        glVertex2f(x + 12.5*s, y + 1.2*s);
        glVertex2f(x + 13.2*s, y + 1.2*s);
        glVertex2f(x + 13.2*s, y + 7*s);
        glVertex2f(x + 12.5*s, y + 7*s);
    glEnd();


    // Front window
    glBegin(GL_QUADS);
        glColor3f(0.75, 0.90, 0.93);

        glVertex2f(x + 15.2*s, y + 4*s);
        glVertex2f(x + 18*s, y + 4*s);
        glVertex2f(x + 18*s, y + 7*s);
        glVertex2f(x + 15.2*s, y + 7*s);
    glEnd();


    // Front light
    glBegin(GL_QUADS);
        glColor3f(1.0, 0.75, 0.10);

        glVertex2f(x + 19*s, y + 3*s);
        glVertex2f(x + 20*s, y + 3*s);
        glVertex2f(x + 20*s, y + 4*s);
        glVertex2f(x + 19*s, y + 4*s);
    glEnd();


    // Back wheel
    glBegin(GL_POLYGON);
        glColor3f(0.05, 0.05, 0.05);

        for(int i = 0; i < 360; i += 30)
        {
            float angle = i * 3.14159 / 180.0;

            glVertex2f(
                x + 4*s + cos(angle) * 1.7*s,
                y - 0.2*s + sin(angle) * 1.7*s
            );
        }
    glEnd();


    // Front wheel
    glBegin(GL_POLYGON);
        glColor3f(0.05, 0.05, 0.05);

        for(int i = 0; i < 360; i += 30)
        {
            float angle = i * 3.14159 / 180.0;

            glVertex2f(
                x + 16*s + cos(angle) * 1.7*s,
                y - 0.2*s + sin(angle) * 1.7*s
            );
        }
    glEnd();


    // Back wheel center
    glBegin(GL_POLYGON);
        glColor3f(0.85, 0.75, 0.65);

        for(int i = 0; i < 360; i += 30)
        {
            float angle = i * 3.14159 / 180.0;

            glVertex2f(
                x + 4*s + cos(angle) * 0.8*s,
                y - 0.2*s + sin(angle) * 0.8*s
            );
        }
    glEnd();


    // Front wheel center
    glBegin(GL_POLYGON);
        glColor3f(0.85, 0.75, 0.65);

        for(int i = 0; i < 360; i += 30)
        {
            float angle = i * 3.14159 / 180.0;

            glVertex2f(
                x + 16*s + cos(angle) * 0.8*s,
                y - 0.2*s + sin(angle) * 0.8*s
            );
        }
    glEnd();
}


void drawWindow(float x1, float y1, float x2, float y2)
{
    glBegin(GL_QUADS);
        glColor3f(0.30, 0.30, 0.30);
        glVertex2f(x1, y1);
        glVertex2f(x1, y2);
        glVertex2f(x2, y2);
        glVertex2f(x2, y1);
    glEnd();

    glBegin(GL_LINES);
        glColor3f(1,1,1);
        glPointSize(40);
        glVertex2f(x1,(y1+y2)/2);
        glVertex2f(x2,(y1+y2)/2);

        glVertex2f((x1+x2)/2, y1);
        glVertex2f((x1+x2)/2, y2);
    glEnd();
}


void drawWindow2(float x1, float y1, float x2, float y2)
{

    glBegin(GL_QUADS);
        glColor3f(0.10, 0.10, 0.10);

        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();



    glBegin(GL_QUADS);
        glColor3f(0.65, 0.80, 0.85);

        glVertex2f(x1 + 0.8, y1 + 0.8);
        glVertex2f(x2 - 0.8, y1 + 0.8);
        glVertex2f(x2 - 0.8, y2 - 0.8);
        glVertex2f(x1 + 0.8, y2 - 0.8);
    glEnd();



    glBegin(GL_QUADS);
        glColor3f(0.10, 0.10, 0.10);

        glVertex2f((x1+x2)/2 - 0.4, y1);
        glVertex2f((x1+x2)/2 + 0.4, y1);
        glVertex2f((x1+x2)/2 + 0.4, y2);
        glVertex2f((x1+x2)/2 - 0.4, y2);
    glEnd();



    glBegin(GL_QUADS);
        glColor3f(0.10, 0.10, 0.10);

        glVertex2f(x1, (y1+y2)/2 - 0.4);
        glVertex2f(x2, (y1+y2)/2 - 0.4);
        glVertex2f(x2, (y1+y2)/2 + 0.4);
        glVertex2f(x1, (y1+y2)/2 + 0.4);
    glEnd();
}


void building(){

    //building1
    glBegin(GL_QUADS);
        glColor3f(0.75, 0.55, 0.35);
        glVertex2f(0, 96.6);
        glVertex2f(0, 143.8);
        glVertex2f(39.2, 143.8);
        glVertex2f(39.7, 94);

        glColor3f(0.45, 0.28, 0.15);
        glVertex2f(39.7, 94);
        glVertex2f(39.2, 143.8);
        glVertex2f(51.6, 136.2);
        glVertex2f(51.9, 93.2);
    glEnd();

    //building1 design
    glBegin(GL_QUADS);
        glColor3f(1, 1, 1);

        glVertex2f(39.6, 106.8);
        glVertex2f(39.6, 109.0);
        glVertex2f(0, 112.6);
        glVertex2f(0, 111.4);

        glVertex2f(39.4, 123.0);
        glVertex2f(39.4, 125.2);
        glVertex2f(0, 130.2);
        glVertex2f(0, 129.0);

    glEnd();


    //big attach building
    glBegin(GL_QUADS);

    glColor3f(0.800, 0.824, 0.843);
    glVertex2f(100, 90);
    glVertex2f(100, 160);
    glVertex2f(120, 160);
    glVertex2f(120, 88.6);


    glColor3f(0.914, 0.941, 0.969);
    glVertex2f(120, 88.6);
    glVertex2f(120, 180);
    glVertex2f(150, 180);
    glVertex2f(150, 86.6);


    glColor3f(0.800, 0.824, 0.843);
    glVertex2f(150, 86.6);
    glVertex2f(150, 180);
    glVertex2f(170, 160);
    glVertex2f(170, 85.2);


    glColor3f(0.914, 0.941, 0.969);
    glVertex2f(170, 85.2);
    glVertex2f(170, 140);
    glVertex2f(190, 140);
    glVertex2f(190, 84);


    glColor3f(0.914, 0.941, 0.969);
    glVertex2f(79.6, 91.2);
    glVertex2f(79.8, 152.2);
    glVertex2f(100, 151.4);
    glVertex2f(100, 90);

    glColor3f(0.914, 0.941, 0.969);
    glVertex2f(190, 84);
    glVertex2f(190, 180);
    glVertex2f(210, 180);
    glVertex2f(210, 82.6);


    glColor3f(0.800, 0.824, 0.843);
    glVertex2f(210, 82.6);
    glVertex2f(210, 180);
    glVertex2f(227.8, 170);
    glVertex2f(228, 81.4);


    glColor3f(0.914, 0.941, 0.969);
    glVertex2f(228, 81.4);
    glVertex2f(228, 188);
    glVertex2f(250, 191.8);
    glVertex2f(250, 80);
    glEnd();

    // WINDOWS
    // Building section 1
    for(int y = 100; y <= 146; y += 10)
    {
        drawWindow(82, y, 85, y + 6);
        drawWindow(87, y, 90, y + 6);
        drawWindow(92, y, 95, y + 6);
        drawWindow(97, y, 99, y + 6);
    }


    // Building section 2
    for(int y = 100; y <= 158; y += 10)
    {
        drawWindow2(102, y, 105, y + 6);
        drawWindow2(107, y, 110, y + 6);
        drawWindow2(112, y, 115, y + 6);
        drawWindow2(117, y, 119, y + 6);
    }


    // Building section 3: 120 - 150
    for(int y = 98; y <= 170; y += 11)
    {
        drawWindow(123, y, 127, y + 7);
        drawWindow(129, y, 133, y + 7);
        drawWindow(136, y, 140, y + 7);
        drawWindow(143, y, 147, y + 7);
    }


    // Building section 4
    for(int y = 88; y <= 155; y += 9)
    {
        drawWindow2(152, y, 156, y + 6);
        drawWindow2(157, y, 161, y + 6);
        drawWindow2(163, y, 166, y + 6);
        drawWindow2(167, y, 169, y + 6);
    }


    // Building section 5
    for(int y = 91; y <= 135; y += 10)
    {
        drawWindow(172, y, 176, y + 6);
        drawWindow(177, y, 181, y + 6);
        drawWindow(182, y, 186, y + 6);
        drawWindow(187, y, 189, y + 6);
    }


    // Building section 6
    for(int y = 90; y <= 175; y += 10)
    {
        drawWindow2(192, y, 196, y + 6);
        drawWindow2(197, y, 201, y + 6);
        drawWindow2(202, y, 206, y + 6);
        drawWindow2(207, y, 209, y + 6);
    }


    // Building section 7
    for(int y = 89; y <= 166; y += 10.9)
    {
        drawWindow(212, y, 216, y + 7);
        drawWindow(217, y, 220, y + 7);
        drawWindow(221, y, 224, y + 7);
        drawWindow(225, y, 227, y + 7);
    }


    // Building section 8
    for(int y = 88; y <= 176; y += 12)
    {
        drawWindow2(230, y, 234, y + 7);
        drawWindow2(235, y, 239, y + 7);
        drawWindow2(241, y, 245, y + 7);
        drawWindow2(246, y, 249, y + 7);
    }
}


void carvisi(){
    // Draw Car
    if(carVisible)
    {
        drawCar(car1X, 49, 1.4);

        drawCar(car8x, 45, 2.5);

        drawCar(car2X, 40, 2.5);

        drawCar(car3X, 49, 1.3);

        drawCar(car7x, 42, 2.4);

        drawCar(car4X, 70, 2.2);

        drawCar(car5X, 75, 2.9);

        drawCar(car6X, 73, 2.5);

        drawCar(car9x, 72, 2.8);
    }
}


void bussvisi(){
    if(bussVisible)
    {
        drawBus(buss, bussy, busss);
    }
}


void drawMan(float x, float y, float s) {
    const float PI = 3.14159265358979323846f;
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
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(5.0f, 0.0f);
        glVertex2f(9.6f, 0.0f);
        glVertex2f(9.6f, 2.0f);
        glVertex2f(5.0f, 2.0f);
        glVertex2f(10.4f, 0.0f);
        glVertex2f(15.0f, 0.0f);
        glVertex2f(15.0f, 2.0f);
        glVertex2f(10.4f, 2.0f);
    glEnd();

    glColor3f(0.96f, 0.77f, 0.62f);
    glBegin(GL_QUADS);
        //Hand
        glVertex2f(4.2f, 11.0f);
        glVertex2f(6.0f, 11.0f);
        glVertex2f(6.0f, 13.0f);
        glVertex2f(4.2f, 13.0f);
        glVertex2f(14.0f, 11.0f);
        glVertex2f(15.8f, 11.0f);
        glVertex2f(15.8f, 13.0f);
        glVertex2f(14.0f, 13.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(4.2f, 11.0f);
        glVertex2f(6.0f, 11.0f);
        glVertex2f(6.0f, 13.0f);
        glVertex2f(4.2f, 13.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(14.0f, 11.0f);
        glVertex2f(15.8f, 11.0f);
        glVertex2f(15.8f, 13.0f);
        glVertex2f(14.0f, 13.0f);
    glEnd();


    glColor3f(0.16f, 0.44f, 0.74f);
    glBegin(GL_QUADS);
        glVertex2f(4.2f, 13.0f);
        glVertex2f(6.0f, 13.0f);
        glVertex2f(6.0f, 22.5f);
        glVertex2f(4.2f, 22.5f);
        glVertex2f(14.0f, 13.0f);
        glVertex2f(15.8f, 13.0f);
        glVertex2f(15.8f, 22.5f);
        glVertex2f(14.0f, 22.5f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(4.2f, 13.0f);
        glVertex2f(6.0f, 13.0f);
        glVertex2f(6.0f, 22.5f);
        glVertex2f(4.2f, 22.5f);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(14.0f, 13.0f);
        glVertex2f(15.8f, 13.0f);
        glVertex2f(15.8f, 22.5f);
        glVertex2f(14.0f, 22.5f);
    glEnd();


    glColor3f(0.16f, 0.44f, 0.74f);
    glBegin(GL_QUADS);
        glVertex2f(5.9f, 10.0f);
        glVertex2f(14.1f, 10.0f);
        glVertex2f(14.1f, 22.0f);
        glVertex2f(5.9f, 22.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(5.9f, 10.0f);
        glVertex2f(14.1f, 10.0f);
        glVertex2f(14.1f, 22.0f);
        glVertex2f(5.9f, 22.0f);
    glEnd();


    glColor3f(0.16f, 0.44f, 0.74f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(10.0f, 21.0f);
        for (int i = 0; i <= segments; i++) {
            float a = PI * (float)i / (float)segments;
            glVertex2f(10.0f + 4.1f * cosf(a), 21.0f + 4.1f * sinf(a));
        }
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= segments; i++) {
            float a = PI * (float)i / (float)segments;
            glVertex2f(10.0f + 4.1f * cosf(a), 21.0f + 4.1f * sinf(a));
        }
    glEnd();

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
        // Increase animation progress
        manProgress += 0.01f;

        // Stop progress at 1
        if(manProgress >= 1.0f)
        {
            manProgress = 1.0f;
        }

        // Man 1
    man1X = 130.0f + (150.0f - 130.0f) * manProgress;
    man1Y = 20.0f + (48.0f - 20.0f) * manProgress;
    man1S = 1.3f + (0.5f - 1.3f) * manProgress;

    // Man 2
    man2X = 152.0f + (150.0f - 152.0f) * manProgress;
    man2Y = 19.0f + (48.0f - 19.0f) * manProgress;
    man2S = 1.4f + (0.5f - 1.4f) * manProgress;

    // Man 3
    man3X = 145.0f + (150.0f - 145.0f) * manProgress;
    man3Y = 22.0f + (48.0f - 22.0f) * manProgress;
    man3S = 1.4f + (0.5f - 1.4f) * manProgress;

    // Man 4
    man4X = 138.0f + (150.0f - 138.0f) * manProgress;
    man4Y = 21.0f + (48.0f - 21.0f) * manProgress;
    man4S = 1.25f + (0.5f - 1.25f) * manProgress;

        // When animation reaches the final position
        if(manProgress >= 1.0f)
        {
            // Set exact final position
            man1X = 150.0f;
            man1Y = 48.0f;
            man1S = 0.5f;

            man2X = 150.0f;
            man2Y = 48.0f;
            man2S = 0.5f;

            man3X = 150.0f;
            man3Y = 48.0f;
            man3S = 0.5f;

            man4X = 150.0f;
            man4Y = 48.0f;
            man4S = 0.5f;

            // Hide after reaching final position
            manMoving = false;
            manVisible = false;
        }

        glutPostRedisplay();
    }
}

void manvisi(){
    if(manVisible)
    {
        drawMan(man1X, man1Y, man1S);
        drawMan(man2X, man2Y, man2S);
        drawMan(man3X, man3Y, man3S);
        drawMan(man4X, man4Y, man4S);
    }
}



void drawCircle(float cx, float cy, float rad, int seg) {
    int i;
    glBegin(GL_POLYGON);
    for (i = 0; i < seg; i++) {
        float angle = 2.0f * 3.1416f * i / seg;
        glVertex2f(cx + rad * cos(angle), cy + rad * sin(angle));
    }
    glEnd();
}

void drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, y, 5.0f, 20);
    drawCircle(x + 6.0f, y + 2.0f, 6.5f, 20);
    drawCircle(x + 12.0f, y, 5.0f, 20);
}


// Grass
void drawGrass(float x, float y, float z)
{
    // Main grass color
    glColor3f(0.45, 0.75, 0.12);

    // Left long blade
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x - 1.2*z, y + 4.5*z);
        glVertex2f(x - 0.7*z, y + 4.2*z);
        glVertex2f(x + 0.2*z, y + 0.5*z);
    glEnd();

    // Left middle blade
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x - 2.0*z, y + 3.0*z);
        glVertex2f(x - 1.7*z, y + 3.3*z);
        glVertex2f(x + 0.1*z, y + 0.4*z);
    glEnd();

    // Left outer blade
    glBegin(GL_POLYGON);
        glVertex2f(x - 0.1*z, y);
        glVertex2f(x - 2.8*z, y + 2.0*z);
        glVertex2f(x - 2.5*z, y + 2.3*z);
        glVertex2f(x + 0.3*z, y + 0.3*z);
    glEnd();

    // Center tall blade
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + 0.3*z, y + 5.2*z);
        glVertex2f(x + 0.7*z, y + 5.5*z);
        glVertex2f(x + 1.0*z, y + 0.5*z);
    glEnd();

    // Right tall blade
    glBegin(GL_POLYGON);
        glVertex2f(x + 0.3*z, y);
        glVertex2f(x + 1.8*z, y + 4.8*z);
        glVertex2f(x + 2.0*z, y + 5.0*z);
        glVertex2f(x + 1.0*z, y + 0.4*z);
    glEnd();

    // Right middle blade
    glBegin(GL_POLYGON);
        glVertex2f(x + 0.5*z, y);
        glVertex2f(x + 2.7*z, y + 3.2*z);
        glVertex2f(x + 2.9*z, y + 3.4*z);
        glVertex2f(x + 1.0*z, y + 0.3*z);
    glEnd();

    // Right outer blade
    glBegin(GL_POLYGON);
        glVertex2f(x + 0.5*z, y);
        glVertex2f(x + 3.2*z, y + 2.0*z);
        glVertex2f(x + 3.4*z, y + 2.2*z);
        glVertex2f(x + 1.0*z, y + 0.2*z);
    glEnd();

    // Small front blades - darker green
    glColor3f(0.30, 0.65, 0.08);

    glBegin(GL_POLYGON);
        glVertex2f(x - 0.5*z, y);
        glVertex2f(x - 1.5*z, y + 1.8*z);
        glVertex2f(x - 1.2*z, y + 2.0*z);
        glVertex2f(x, y + 0.3*z);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(x + 0.2*z, y);
        glVertex2f(x - 0.3*z, y + 2.2*z);
        glVertex2f(x, y + 2.5*z);
        glVertex2f(x + 0.7*z, y + 0.3*z);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(x + 0.5*z, y);
        glVertex2f(x + 1.5*z, y + 2.0*z);
        glVertex2f(x + 1.8*z, y + 2.2*z);
        glVertex2f(x + 1.0*z, y + 0.2*z);
    glEnd();
}

void background2nd(){

    //sky
    glBegin(GL_QUADS);
        glColor3f(0.53, 0.81, 0.98);
        glVertex2f(0,130);
        glVertex2f(0,200);
        glVertex2f(250,200);
        glVertex2f(250,140);
    glEnd();
    // Road
    glBegin(GL_QUADS);
        glColor3f(0.20f, 0.20f, 0.20f);
        glVertex2f(250,40);
        glVertex2f(0,20);
        glVertex2f(0,96.6);
        glVertex2f(250,80);
    glEnd();


    //cloud
    drawCloud(130,190);
    drawCloud(145,190);
    drawCloud(110,180);
    drawCloud(170,180);
    drawCloud(90,160);
    drawCloud(80,190);
    drawCloud(200,185);
    drawCloud(50,165);
    drawCloud(220,180);


    //Sun
    glColor3f(1.00, 0.85, 0.10);
    drawCircle(20, 185, 8, 100);

    //front ground
    glBegin(GL_QUADS);
        glColor3f(0.20, 0.60, 0.10);
        glVertex2f(0, 0);
        glVertex2f(0, 20);
        glVertex2f(250, 40);
        glVertex2f(250, 0);
    glEnd();


    //grass
    drawGrass(190, 20, 1.2);
    drawGrass(195, 18, 1.1);
    drawGrass(197, 21, 1.3);
    drawGrass(187, 20, 1.2);

    drawGrass(210, 20, 1.2);
    drawGrass(215, 18, 1.1);
    drawGrass(217, 21, 1.3);
    drawGrass(207, 20, 1.2);

    drawGrass(230, 20, 1.2);
    drawGrass(235, 18, 1.1);
    drawGrass(237, 21, 1.3);
    drawGrass(227, 20, 1.2);




    for (int x = 0; x <= 250; x += 10)
    {
        drawGrass(x,     9, 1.2);
        drawGrass(x + 5,  7, 1.1);
        drawGrass(x + 7, 10, 1.3);
        drawGrass(x - 3,  9, 1.2);
    }
}


void display2nd(){
    glClear(GL_COLOR_BUFFER_BIT);

    //Road, ground, roadberiar
    background2nd();


    //All building and design
    building();


    //Big tree
    drawTree(67.5, 92, 2.2);

    // Tree 1
    drawTree(112.7, 89.0, 1.0);

    // Tree 2
    drawTree(125.3, 88.2, 0.80);

    // Tree 3
    drawTree(131.0, 87.8, 1.2);

    // Tree 4
    drawTree(140.9, 87.2, 0.6);

    // Tree 5
    drawTree(150, 86.6, 1.0);

    // Tree 6
    drawTree(170.1, 85.2, 1.5);

    //Tree 7
    drawTree(228, 81.04, 1.7);

    //Tree 8
    drawTree(201.7, 83.2, 1);


    //Draw Car
    carvisi();


    float z = 1.00;
    for(int i=250; i>3; i-=7){
        roadB(i, 60, z);
        z+=0.05;

        if(i<110){
            i-=3;
        }
    }


    // Draw Buss
    bussvisi();


    //Man visible
    manvisi();



    glFlush();
}


// Car movement function
void update(int value)
{
    if(carMoving && carVisible)
    {
        car1X -= 0.5;
        car2X -= 0.5;
        car3X -= 0.5;
        car7x -= 0.5;
        car8x -= 0.7;


        if(car1X < -12)
        {
            car1X = 260;
        }

        if(car2X < -14)
        {
            car2X = 280;
        }

        if(car3X < -17)
        {
            car3X = 300;
        }

        if(car7x < -20)
        {
            car3X = 310;
        }

        if(car8x < -23)
        {
            car3X = 325;
        }



        car4X += 0.5;
        car5X += 0.5;
        car6X += 0.5;
        car9x += 0.5;



        if(car4X > 250)
        {
            car4X = -25;
        }


        if(car5X > 250)
        {
            car5X = -35;
        }

        if(car6X > 250)
        {
            car6X = -45;
        }

        if(car9x < 250)
        {
            car3X = -55;
        }


        glutPostRedisplay();
    }

    glutTimerFunc(16, update, 0);
}


//Buss movement function
void updateB(int value)
{
    if(bussMoving && bussVisible)
    {
        buss -= 0.3;
        bussy -= 0.02469;
        busss += 0.002292;


        // Stop at target position
        if(buss <= bussTarget )
        {
            buss = bussTarget;
            bussy = bussTargety;
            busss = 4;
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


// Keyboard function
void keyboard(unsigned char key, int x, int y)
{
    if(key == 's' || key == 'S')
    {
        carVisible = true;
        carMoving = true;

        glutPostRedisplay();
    }


    if(key == 'e' || key == 'E')
    {
        carMoving = false;
        carVisible = false;

        glutPostRedisplay();
    }


    // Press B
    if(key == 'b' || key == 'B')
    {
        // Start bus from right side
        buss = 300;
        bussy = 60;
        busss = 2.5;


        bussTarget = 100;
        bussTargety = 44;
        bussTargets = 4;

        bussVisible = true;
        bussMoving = true;

        glutPostRedisplay();
    }


    // Press G
    if(key == 'g' || key == 'G')
    {
        // Start bus from position 100
        buss = bussTarget;
        bussy = bussTargety;
        busss = 4;

        bussTarget = -80;

        bussVisible = true;
        bussMoving = true;

        glutPostRedisplay();
    }


    //Press M
    if(key == 'm' || key == 'M')
    {
        // Reset Man 1
        man1X = 130.0f;
        man1Y = 20.0f;
        man1S = 1.3f;

        // Reset Man 2
        man2X = 152.0f;
        man2Y = 19.0f;
        man2S = 1.4f;

        // Reset Man 3
        man3X = 145.0f;
        man3Y = 22.0f;
        man3S = 1.4f;

        // Reset Man 4
        man4X = 138.0f;
        man4Y = 21.0f;
        man4S = 1.25f;

        // Reset animation
        manProgress = 0.0f;

        // Show and start movement
        manVisible = true;
        manMoving = true;

        glutPostRedisplay();
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 700);
    glutInitWindowPosition(50, 30);
    glutCreateWindow("Buss Journey scenario");

    init();

    glutDisplayFunc(display2nd);

    glutKeyboardFunc(keyboard);

    // Car timer
    glutTimerFunc(16, update, 0);

    // Bus timer
    glutTimerFunc(16, updateB, 0);

    //Man timer
    glutTimerFunc(16, updateMan, 0);

    glutMainLoop();

    return 0;
}
