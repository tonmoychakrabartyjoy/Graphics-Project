/*
#include <windows.h>
#include <GL/glut.h>
#include <math.h>

// world width changes when window is resized (see reshape())
float worldWidth = 400.0f;
const float stageWidth = 400.0f;

float busX = -150;

// Passengers (three people who get down from the bus)
float person1X = 170;
float person2X = 190;
float person3X = 210;
float personY = 148;
const float person1TargetX = 285;
const float person2TargetX = 300;
const float person3TargetX = 315;
const float walkSpeed = 0.4f;

// Cars running on the opposite lane (opposite direction of the bus)
float carAX = 500, carBX = 700, carCX = 900, carDX = 1100, carEX = 1300;
const float carASpeed = 0.6f, carBSpeed = 0.45f, carCSpeed = 0.7f, carDSpeed = 0.5f, carESpeed = 0.65f;

// Plane, flies across the sky ONE TIME only
float planeX = -60;
int planeActive = 1;      // 1 = still flying, 0 = gone for good

// scene: 0=bus hidden, 1=bus entering, 2=bus stopped (waiting for E),
// 3=doors open / passengers sliding, 4=passengers arrived (waiting to leave),
// 5=bus leaving
int scene = 0;
int passengerOut = 0;
int passengersArrived = 0;

void drawText(float x, float y, const char* text);


// ---------- helper shape (this is the circle i have to remember) ----------
// used again and again for sun, clouds, heads, wheels

void drawCircle(float x, float y, float r)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10)
    {
        float a = i * 3.14159f / 180.0f;
        glVertex2f(x + r * cos(a), y + r * sin(a));
    }
    glEnd();
}


// ---------- sky ----------

void drawCloud(float x, float y)
{
    // This is the cloud i have to remember
    glColor3f(1, 1, 1);
    drawCircle(x, y, 7);
    drawCircle(x + 8, y + 3, 9);
    drawCircle(x + 17, y, 7);
}

void drawSun(float x, float y)
{
    // This is the sun i have to remember - kept plain, just a circle
    glColor3f(1.0f, 0.85f, 0.2f);
    drawCircle(x, y, 16);
}

void drawPlane(float x, float y)
{
    // This is the plane i have to remember - fuselage + nose + tail fin + wings

    // fuselage (the long body)
    glColor3f(0.85f, 0.85f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(x, y - 3);
    glVertex2f(x + 34, y - 3);
    glVertex2f(x + 34, y + 3);
    glVertex2f(x, y + 3);
    glEnd();

    // nose cone (pointed front of the plane)
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 34, y - 3);
    glVertex2f(x + 34, y + 3);
    glVertex2f(x + 44, y);
    glEnd();

    // tail fin (sticks up at the back)
    glColor3f(0.55f, 0.55f, 0.65f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y + 3);
    glVertex2f(x + 10, y + 3);
    glVertex2f(x + 4, y + 15);
    glEnd();

    // main wings (top and bottom, forming a wide diamond in the middle)
    glColor3f(0.7f, 0.7f, 0.8f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 14, y + 3);
    glVertex2f(x + 24, y + 3);
    glVertex2f(x + 18, y + 16);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 14, y - 3);
    glVertex2f(x + 24, y - 3);
    glVertex2f(x + 18, y - 16);
    glEnd();
}


// ---------- trees / flowers ----------

void drawTree(float x, float y)
{
    // This is the tree i have to remember
    glColor3f(0.42f, 0.26f, 0.12f);
    glBegin(GL_QUADS);
    glVertex2f(x - 2, y);
    glVertex2f(x + 2, y);
    glVertex2f(x + 2, y + 14);
    glVertex2f(x - 2, y + 14);
    glEnd();

    glColor3f(0.13f, 0.55f, 0.2f);
    drawCircle(x, y + 20, 10);
}

void drawFlower(float x, float y, float r, float g, float b)
{
    // This is the flower i have to remember - just a stem and one dot
    glColor3f(0.3f, 0.7f, 0.2f);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y + 4);
    glEnd();

    glColor3f(r, g, b);
    drawCircle(x, y + 5, 2.0f);
}


// ---------- ground (road, sidewalk, grass) ----------

const float ROAD_BOTTOM = 10.0f;
const float ROAD_TOP = 108.0f;
const float SIDEWALK_TOP = 122.0f;
const float GRASS_TOP = 150.0f;

void drawRoad(float width)
{
    // This is the road i have to remember
    glColor3f(0.15f, 0.15f, 0.15f);
    glBegin(GL_QUADS);
    glVertex2f(0, ROAD_BOTTOM);
    glVertex2f(width, ROAD_BOTTOM);
    glVertex2f(width, ROAD_TOP);
    glVertex2f(0, ROAD_TOP);
    glEnd();

    // This is the sidewalk i have to remember
    glColor3f(0.65f, 0.65f, 0.65f);
    glBegin(GL_QUADS);
    glVertex2f(0, ROAD_TOP);
    glVertex2f(width, ROAD_TOP);
    glVertex2f(width, SIDEWALK_TOP);
    glVertex2f(0, SIDEWALK_TOP);
    glEnd();

    // This is the grass i have to remember
    glColor3f(0.2f, 0.7f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(0, SIDEWALK_TOP);
    glVertex2f(width, SIDEWALK_TOP);
    glVertex2f(width, GRASS_TOP);
    glVertex2f(0, GRASS_TOP);
    glEnd();
}

void drawRoadLines(float width)
{
    // This is the middle road line i have to remember
    float mid = (ROAD_BOTTOM + ROAD_TOP) / 2.0f;
    glColor3f(0.95f, 0.8f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(0, mid - 1.5f);
    glVertex2f(width, mid - 1.5f);
    glVertex2f(width, mid + 1.5f);
    glVertex2f(0, mid + 1.5f);
    glEnd();

    // dashed lane markings, upper lane (bus) and lower lane (cars)
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    for (float x = -80; x < width; x += 80)
    {
        glVertex2f(x + 20, ROAD_TOP - 15);
        glVertex2f(x + 60, ROAD_TOP - 15);
        glVertex2f(x + 60, ROAD_TOP - 12);
        glVertex2f(x + 20, ROAD_TOP - 12);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (float x = -80; x < width; x += 80)
    {
        glVertex2f(x + 60, ROAD_BOTTOM + 12);
        glVertex2f(x + 100, ROAD_BOTTOM + 12);
        glVertex2f(x + 100, ROAD_BOTTOM + 14.5f);
        glVertex2f(x + 60, ROAD_BOTTOM + 14.5f);
    }
    glEnd();
}


// ---------- buildings ----------

const float BLD_BASE = 122.0f;
const float BLD_TOP = 210.0f;
const float ROOF_TOP = 222.0f;

void drawBuilding()
{
    // This is the first building i have to remember
    glColor3f(0.75f, 0.75f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(20, BLD_BASE);
    glVertex2f(170, BLD_BASE);
    glVertex2f(170, BLD_TOP);
    glVertex2f(20, BLD_TOP);
    glEnd();

    // windows, simple grid, same color for all of them
    glColor3f(0.1f, 0.3f, 0.5f);
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            float wx = 30 + col * 27;
            float wy = BLD_BASE + 15 + row * 20;
            glBegin(GL_QUADS);
            glVertex2f(wx, wy);
            glVertex2f(wx + 12, wy);
            glVertex2f(wx + 12, wy + 9);
            glVertex2f(wx, wy + 9);
            glEnd();
        }
    }

    // roof
    glColor3f(0.4f, 0.4f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(15, BLD_TOP);
    glVertex2f(175, BLD_TOP);
    glVertex2f(175, ROOF_TOP);
    glVertex2f(15, ROOF_TOP);
    glEnd();
}

void drawDestinationBuilding()
{
    // This is the college building i have to remember
    glColor3f(0.9f, 0.85f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(220, BLD_BASE);
    glVertex2f(390, BLD_BASE);
    glVertex2f(390, BLD_TOP);
    glVertex2f(220, BLD_TOP);
    glEnd();

    // college door
    glColor3f(0.3f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(295, BLD_BASE);
    glVertex2f(325, BLD_BASE);
    glVertex2f(325, BLD_BASE + 34);
    glVertex2f(295, BLD_BASE + 34);
    glEnd();

    // college windows
    glColor3f(0.1f, 0.4f, 0.7f);
    for (int row = 0; row < 2; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            float x = 239 + col * 30;
            float y = BLD_BASE + 44 + row * 20;
            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + 12, y);
            glVertex2f(x + 12, y + 9);
            glVertex2f(x, y + 9);
            glEnd();
        }
    }

    // roof
    glColor3f(0.5f, 0.45f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(215, BLD_TOP);
    glVertex2f(395, BLD_TOP);
    glVertex2f(395, ROOF_TOP);
    glVertex2f(215, ROOF_TOP);
    glEnd();
}

void drawCollegeBoard()
{
    // This is the college name board i have to remember
    glColor3f(0.8f, 0.5f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(240, BLD_BASE + 86);
    glVertex2f(370, BLD_BASE + 86);
    glVertex2f(370, BLD_BASE + 100);
    glVertex2f(240, BLD_BASE + 100);
    glEnd();
}


// ---------- bus stop (plain pole + sign, no bench, no roof) ----------

void drawBusStop()
{
    // This is the bus stop pole i have to remember
    glColor3f(0.25f, 0.25f, 0.25f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(187, BLD_BASE);
    glVertex2f(187, 178);
    glEnd();
    glLineWidth(1.0f);

    // sign board on top of the pole
    glColor3f(1, 0.85f, 0);
    glBegin(GL_QUADS);
    glVertex2f(166, 178);
    glVertex2f(208, 178);
    glVertex2f(208, 192);
    glVertex2f(166, 192);
    glEnd();
    drawText(169, 182, "BUS STOP");
}


// ---------- people (plain circle head + rectangle body + line legs) ----------

void drawPerson(float x, float y)
{
    // This is the person i have to remember
    glColor3f(1, 0.8f, 0.6f);
    drawCircle(x, y, 5.0f);           // head

    glColor3f(0.15f, 0.4f, 0.85f);
    glBegin(GL_QUADS);                 // body
    glVertex2f(x - 5, y - 6);
    glVertex2f(x + 5, y - 6);
    glVertex2f(x + 5, y - 20);
    glVertex2f(x - 5, y - 20);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.25f);
    glBegin(GL_LINES);                 // two legs
    glVertex2f(x - 2, y - 20);
    glVertex2f(x - 4, y - 34);
    glVertex2f(x + 2, y - 20);
    glVertex2f(x + 4, y - 34);
    glEnd();
}


// ---------- vehicles ----------

void drawWheel(float x, float y, float r)
{
    glColor3f(0, 0, 0);
    drawCircle(x, y, r);
}

void drawBus(float x)
{
    // This is the bus i have to remember
    float y0 = 78, y1 = 108;
    glColor3f(0.0f, 0.35f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(x, y0);
    glVertex2f(x + 150, y0);
    glVertex2f(x + 150, y1);
    glVertex2f(x, y1);
    glEnd();

    // windows
    glColor3f(0.6f, 0.85f, 1);
    for (int i = 0; i < 3; i++)
    {
        float wx = x + 10 + (i * 31);
        glBegin(GL_QUADS);
        glVertex2f(wx, y0 + 8);
        glVertex2f(wx + 22, y0 + 8);
        glVertex2f(wx + 22, y1 - 6);
        glVertex2f(wx, y1 - 6);
        glEnd();
    }

    // door
    glColor3f(0.55f, 0.8f, 0.95f);
    glBegin(GL_QUADS);
    glVertex2f(x + 100, y0 + 3);
    glVertex2f(x + 122, y0 + 3);
    glVertex2f(x + 122, y1 - 3);
    glVertex2f(x + 100, y1 - 3);
    glEnd();

    // wheels
    drawWheel(x + 38, y0 - 1, 7.5f);
    drawWheel(x + 118, y0 - 1, 7.5f);
}

void drawCar(float x, float r, float g, float b)
{
    // This is the car i have to remember
    float y = ROAD_BOTTOM + 14;

    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 50, y);
    glVertex2f(x + 50, y + 18);
    glVertex2f(x, y + 18);
    glEnd();

    // windshield
    glColor3f(0.6f, 0.85f, 1);
    glBegin(GL_QUADS);
    glVertex2f(x + 14, y + 18);
    glVertex2f(x + 35, y + 18);
    glVertex2f(x + 30, y + 28);
    glVertex2f(x + 19, y + 28);
    glEnd();

    drawWheel(x + 12, y - 2, 6.0f);
    drawWheel(x + 38, y - 2, 6.0f);
}


// ---------- text ----------

void drawText(float x, float y, const char* text)
{
    glColor3f(0, 0, 0);
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]);
}


// ---------- main display (draws everything, every frame) ----------

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float offset = (worldWidth - stageWidth) / 2.0f;
    if (offset < 0) offset = 0;

    // sky - spans the entire visible width
    glColor3f(0.5f, 0.8f, 1);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(worldWidth, 0);
    glVertex2f(worldWidth, 300);
    glVertex2f(0, 300);
    glEnd();

    drawSun(worldWidth - 45, 265);
    drawCloud(offset * 0.25f, 280);
    drawCloud(offset * 0.7f, 262);
    drawCloud(worldWidth - offset * 0.25f - 22, 278);
    drawCloud(worldWidth - offset * 0.7f - 22, 260);
    drawCloud(worldWidth * 0.42f, 271);
    drawCloud(worldWidth * 0.58f, 255);

    // plane only draws while it is still flying (one-shot, see timer())
    if (planeActive == 1)
        drawPlane(planeX, 288);

    // ---- the hand-placed "stage" (buildings), centered on screen ----
    glPushMatrix();
    glTranslatef(offset, 0, 0);
    drawBuilding();
    drawDestinationBuilding();
    drawCollegeBoard();
    glPopMatrix();

    // road/sidewalk/grass - spans the entire visible width
    drawRoad(worldWidth);
    drawRoadLines(worldWidth);

    // trees + flowers filling the open space on both sides
    for (float tx = 20; tx < offset - 12; tx += 26)
    {
        drawTree(tx, SIDEWALK_TOP + 1);
        drawFlower(tx + 15, SIDEWALK_TOP + 1, 0.9f, 0.15f, 0.2f);
    }
    for (float tx = offset + stageWidth + 15; tx < worldWidth - 12; tx += 26)
    {
        drawTree(tx, SIDEWALK_TOP + 1);
        drawFlower(tx + 15, SIDEWALK_TOP + 1, 0.9f, 0.4f, 0.7f);
    }

    glPushMatrix();
    glTranslatef(offset, 0, 0);
    drawTree(8, SIDEWALK_TOP + 1);
    drawFlower(180, SIDEWALK_TOP + 1, 1.0f, 0.3f, 0.3f);
    drawFlower(340, SIDEWALK_TOP + 1, 1.0f, 0.8f, 0.2f);

    drawBusStop();

    if (passengerOut == 1)
    {
        drawPerson(person1X, personY);
        drawPerson(person2X, personY);
        drawPerson(person3X, personY);
    }

    // bus is only drawn once "W" has been pressed (scene != 0)
    if (scene != 0)
        drawBus(busX);

    glPopMatrix();

    // traffic - always spans the full visible road, keeps looping
    drawCar(carAX, 0.95f, 0.95f, 0.95f);
    drawCar(carBX, 0.55f, 0.55f, 0.55f);
    drawCar(carCX, 0.85f, 0.1f, 0.1f);
    drawCar(carDX, 0.1f, 0.35f, 0.7f);
    drawCar(carEX, 0.9f, 0.7f, 0.1f);

    glFlush();
}


// ---------- keyboard controls ----------
// W = bus enters, E = passengers get off, L = bus leaves

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'w' || key == 'W')
    {
        if (scene == 0)               // only start if bus is currently hidden
            scene = 1;
    }
    else if (key == 'e' || key == 'E')
    {
        if (scene == 2)                // only works once the bus has stopped
        {
            passengerOut = 1;          // doors open, people become visible
            scene = 3;                 // start sliding them to the right
        }
    }
    else if (key == 'l' || key == 'L')
    {
        if (scene == 4)                // only works once passengers have arrived
            scene = 5;                 // bus starts leaving
    }
}


// ---------- timer function (moves everything, one small step at a time) ----------

void timer(int value)
{
    carAX -= carASpeed;
    if (carAX < -50) carAX = worldWidth + 30;

    carBX -= carBSpeed;
    if (carBX < -50) carBX = worldWidth + 130;

    carCX -= carCSpeed;
    if (carCX < -50) carCX = worldWidth + 230;

    carDX -= carDSpeed;
    if (carDX < -50) carDX = worldWidth + 330;

    carEX -= carESpeed;
    if (carEX < -50) carEX = worldWidth + 430;

    // plane flies across ONE TIME only, then stops for good
    if (planeActive == 1)
    {
        planeX += 0.15f;
        if (planeX > worldWidth + 50)
            planeActive = 0;           // gone - never comes back
    }

    // ---- the bus story, now driven by keyboard presses ----
    if (scene == 1)
    {
        busX += 0.5f;                  // bus entering
        if (busX > 75) scene = 2;      // reaches its stopping position, then waits for "E"
    }
    else if (scene == 3)
    {
        int arrivedCount = 0;
        if (person1X < person1TargetX) person1X += walkSpeed; else arrivedCount++;
        if (person2X < person2TargetX) person2X += walkSpeed; else arrivedCount++;
        if (person3X < person3TargetX) person3X += walkSpeed; else arrivedCount++;

        if (arrivedCount == 3)
        {
            passengersArrived = 1;
            scene = 4;                 // now waits for "L" to make the bus leave
        }
    }
    else if (scene == 5)
    {
        busX += 1.2f;                  // bus leaving
        if (busX > stageWidth + 200)
        {
            // bus is gone - hide it again, but passengers stay exactly where they are
            busX = -150;
            scene = 0;
        }
    }
    // scene == 0, 2 and 4 are idle states - nothing moves until a key is pressed

    glutPostRedisplay();
    glutTimerFunc(20, timer, 0);
}


// ---------- window resize (keeps the drawing filling the window) ----------

void reshape(int width, int height)
{
    if (height == 0) height = 1;

    float aspect = (float)width / (float)height;
    worldWidth = 300.0f * aspect;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, worldWidth, 0, 300);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}




void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 400, 0, 300);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 700);
    glutInitWindowPosition(50, 30);
    glutCreateWindow("Bus Stop Scene - OpenGL");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(20, timer, 0);

    glutMainLoop();
    return 0;
}
*/
