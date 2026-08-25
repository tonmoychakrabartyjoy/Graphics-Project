#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;


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


float buss = 280;
float bussy = 60;
float busss = 2.5;


bool bussMoving = false;
bool bussVisible = false;

float bussTarget = 100;
float bussTargety = 44;
float bussTargets = 3.8;


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
    glBegin(GL_POLYGON);
        glColor3f(0.95, 0.20, 0.05);

        glVertex2f(x - 0.0 * z, y + 0.0 * z);
        glVertex2f(x - 0.0 * z, y + 2.0 * z);
        glVertex2f(x - 1.0 * z, y + 3.2 * z);
        glVertex2f(x - 2.0 * z, y + 3.2 * z);
        glVertex2f(x - 3.0 * z, y + 2.0 * z);
        glVertex2f(x - 3.0 * z, y + 0.0 * z);
    glEnd();
}


void drawCar(float x, float y, float s)
{

    glBegin(GL_QUADS);
        glColor3f(0.05, 0.25, 0.55);

        glVertex2f(x,          y);
        glVertex2f(x + 10*s,   y);
        glVertex2f(x + 10*s,   y + 3*s);
        glVertex2f(x,          y + 3*s);
    glEnd();


    glBegin(GL_POLYGON);
        glColor3f(0.10, 0.50, 0.85);

        glVertex2f(x + 2*s, y + 3*s);
        glVertex2f(x + 3*s, y + 5*s);
        glVertex2f(x + 7*s, y + 5*s);
        glVertex2f(x + 8*s, y + 3*s);
    glEnd();



    glBegin(GL_QUADS);
        glColor3f(0.15, 0.25, 0.35);

        glVertex2f(x + 5.1*s, y + 3.2*s);
        glVertex2f(x + 7*s,   y + 3.2*s);
        glVertex2f(x + 6.6*s, y + 4.5*s);
        glVertex2f(x + 5.1*s, y + 4.5*s);
    glEnd();


    glBegin(GL_QUADS);
        glColor3f(0.15, 0.25, 0.35);

        glVertex2f(x + 3*s,   y + 3.2*s);
        glVertex2f(x + 4.9*s, y + 3.2*s);
        glVertex2f(x + 4.9*s, y + 4.5*s);
        glVertex2f(x + 3.4*s, y + 4.5*s);
    glEnd();


    glBegin(GL_QUADS);
        glColor3f(0.15, 0.25, 0.35);

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

        drawCar(car8x, 45, 1.9);

        drawCar(car2X, 40, 1.5);

        drawCar(car3X, 49, 1.3);

        drawCar(car7x, 42, 1.6);

        drawCar(car4X, 70, 2.2);

        drawCar(car5X, 75, 1.9);

        drawCar(car6X, 73, 2);

        drawCar(car9x, 72, 1.8);
    }
}


void bussvisi(){
    if(bussVisible)
    {
        drawBus(buss, bussy, busss);
    }
}


void background(){
    // Road
    glBegin(GL_QUADS);
        glColor3f(0.20f, 0.20f, 0.20f);
        glVertex2f(250,40);
        glVertex2f(0,23.2);
        glVertex2f(0,96.6);
        glVertex2f(250,80);
    glEnd();


    float z = 1.00;
    for(int i=250; i>3; i-=7){
        roadB(i, 60, z);
        z+=0.05;

        if(i<110){
            i-=3;
        }
    }




    //front ground
    glBegin(GL_QUADS);
        glColor3f(0.20, 0.60, 0.10);
        glVertex2f(0, 0);
        glVertex2f(0, 23.2);
        glVertex2f(250, 40);
        glVertex2f(250, 0);
    glEnd();
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    //Road, ground, roadberiar
    background();


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


    // Draw Buss
    bussvisi();


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
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 700);
    glutInitWindowPosition(50, 30);
    glutCreateWindow("Buss get in scenario");

    init();

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);

    // Car timer
    glutTimerFunc(16, update, 0);

    // Bus timer
    glutTimerFunc(16, updateB, 0);

    glutMainLoop();

    return 0;
}
