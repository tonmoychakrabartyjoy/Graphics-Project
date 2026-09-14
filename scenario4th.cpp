#include <GL/glut.h>
#include <math.h>

namespace Scene4 {

static float worldWidth = 400.0f;
static const float stageWidth = 400.0f;

static float busX = -150;
static float person1X = 170;
static float person2X = 190;
static float person3X = 210;
static float personY = 148;
static const float person1TargetX = 285;
static const float person2TargetX = 300;
static const float person3TargetX = 315;
static const float walkSpeed = 0.4f;

static float carAX = 500, carBX = 700, carCX = 900, carDX = 1100, carEX = 1300;
static const float carASpeed = 0.6f, carBSpeed = 0.45f, carCSpeed = 0.7f, carDSpeed = 0.5f, carESpeed = 0.65f;

static float planeX = -60;
static int planeActive = 1;

static int scene = 0;
static int passengerOut = 0;
static int passengersArrived = 0;

static const float ROAD_BOTTOM = 10.0f;
static const float ROAD_TOP = 108.0f;
static const float SIDEWALK_TOP = 122.0f;
static const float GRASS_TOP = 150.0f;
static const float BLD_BASE = 122.0f;
static const float BLD_TOP = 210.0f;
static const float ROOF_TOP = 222.0f;

static void drawCircle(float x, float y, float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float a = i * 3.14159f / 180.0f;
        glVertex2f(x + r * cos(a), y + r * sin(a));
    }
    glEnd();
}

static void drawCloud(float x, float y) {
    glColor3f(1, 1, 1);
    drawCircle(x, y, 7);
    drawCircle(x + 8, y + 3, 9);
    drawCircle(x + 17, y, 7);
}

static void drawSun(float x, float y) {
    glColor3f(1.0f, 0.85f, 0.2f);
    drawCircle(x, y, 16);
}

static void drawPlane(float x, float y) {
    glColor3f(0.85f, 0.85f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(x, y - 3);
        glVertex2f(x + 34, y - 3);
        glVertex2f(x + 34, y + 3);
        glVertex2f(x, y + 3);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(x + 34, y - 3);
        glVertex2f(x + 34, y + 3);
        glVertex2f(x + 44, y);
    glEnd();

    glColor3f(0.55f, 0.55f, 0.65f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x, y + 3);
        glVertex2f(x + 10, y + 3);
        glVertex2f(x + 4, y + 15);
    glEnd();

    glColor3f(0.7f, 0.7f, 0.8f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x + 14, y + 3);
        glVertex2f(x + 24, y + 3);
        glVertex2f(x + 18, y + 16);
        glVertex2f(x + 14, y - 3);
        glVertex2f(x + 24, y - 3);
        glVertex2f(x + 18, y - 16);
    glEnd();
}

static void drawTree(float x, float y) {
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

static void drawFlower(float x, float y, float r, float g, float b) {
    glColor3f(0.3f, 0.7f, 0.2f);
    glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x, y + 4);
    glEnd();
    glColor3f(r, g, b);
    drawCircle(x, y + 5, 2.0f);
}

static void drawRoad(float width) {
    glColor3f(0.15f, 0.15f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(0, ROAD_BOTTOM);
        glVertex2f(width, ROAD_BOTTOM);
        glVertex2f(width, ROAD_TOP);
        glVertex2f(0, ROAD_TOP);
    glEnd();

    glColor3f(0.65f, 0.65f, 0.65f);
    glBegin(GL_QUADS);
        glVertex2f(0, ROAD_TOP);
        glVertex2f(width, ROAD_TOP);
        glVertex2f(width, SIDEWALK_TOP);
        glVertex2f(0, SIDEWALK_TOP);
    glEnd();

    glColor3f(0.2f, 0.7f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(0, SIDEWALK_TOP);
        glVertex2f(width, SIDEWALK_TOP);
        glVertex2f(width, GRASS_TOP);
        glVertex2f(0, GRASS_TOP);
    glEnd();
}

static void drawRoadLines(float width) {
    float mid = (ROAD_BOTTOM + ROAD_TOP) / 2.0f;
    glColor3f(0.95f, 0.8f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(0, mid - 1.5f);
        glVertex2f(width, mid - 1.5f);
        glVertex2f(width, mid + 1.5f);
        glVertex2f(0, mid + 1.5f);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    for (float x = -80; x < width; x += 80) {
        glVertex2f(x + 20, ROAD_TOP - 15);
        glVertex2f(x + 60, ROAD_TOP - 15);
        glVertex2f(x + 60, ROAD_TOP - 12);
        glVertex2f(x + 20, ROAD_TOP - 12);
    }
    for (float x = -80; x < width; x += 80) {
        glVertex2f(x + 60, ROAD_BOTTOM + 12);
        glVertex2f(x + 100, ROAD_BOTTOM + 12);
        glVertex2f(x + 100, ROAD_BOTTOM + 14.5f);
        glVertex2f(x + 60, ROAD_BOTTOM + 14.5f);
    }
    glEnd();
}

static void drawBuilding() {
    glColor3f(0.75f, 0.75f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(20, BLD_BASE);
        glVertex2f(170, BLD_BASE);
        glVertex2f(170, BLD_TOP);
        glVertex2f(20, BLD_TOP);
    glEnd();

    glColor3f(0.1f, 0.3f, 0.5f);
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 5; col++) {
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

    glColor3f(0.4f, 0.4f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(15, BLD_TOP);
        glVertex2f(175, BLD_TOP);
        glVertex2f(175, ROOF_TOP);
        glVertex2f(15, ROOF_TOP);
    glEnd();
}

static void drawDestinationBuilding() {
    glColor3f(0.9f, 0.85f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(220, BLD_BASE);
        glVertex2f(390, BLD_BASE);
        glVertex2f(390, BLD_TOP);
        glVertex2f(220, BLD_TOP);
    glEnd();

    glColor3f(0.3f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(295, BLD_BASE);
        glVertex2f(325, BLD_BASE);
        glVertex2f(325, BLD_BASE + 34);
        glVertex2f(295, BLD_BASE + 34);
    glEnd();

    glColor3f(0.1f, 0.4f, 0.7f);
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 5; col++) {
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

    glColor3f(0.5f, 0.45f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(215, BLD_TOP);
        glVertex2f(395, BLD_TOP);
        glVertex2f(395, ROOF_TOP);
        glVertex2f(215, ROOF_TOP);
    glEnd();
}

static void drawCollegeBoard() {
    glColor3f(0.8f, 0.5f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(240, BLD_BASE + 86);
        glVertex2f(370, BLD_BASE + 86);
        glVertex2f(370, BLD_BASE + 100);
        glVertex2f(240, BLD_BASE + 100);
    glEnd();
}

static void drawText(float x, float y, const char* text) {
    glColor3f(0, 0, 0);
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]);
}

static void drawBusStop() {
    glColor3f(0.25f, 0.25f, 0.25f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(187, BLD_BASE);
        glVertex2f(187, 178);
    glEnd();
    glLineWidth(1.0f);

    glColor3f(1, 0.85f, 0);
    glBegin(GL_QUADS);
        glVertex2f(166, 178);
        glVertex2f(208, 178);
        glVertex2f(208, 192);
        glVertex2f(166, 192);
    glEnd();
    drawText(169, 182, "BUS STOP");
}

static void drawPerson(float x, float y) {
    glColor3f(1, 0.8f, 0.6f);
    drawCircle(x, y, 5.0f);

    glColor3f(0.15f, 0.4f, 0.85f);
    glBegin(GL_QUADS);
        glVertex2f(x - 5, y - 6);
        glVertex2f(x + 5, y - 6);
        glVertex2f(x + 5, y - 20);
        glVertex2f(x - 5, y - 20);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.25f);
    glBegin(GL_LINES);
        glVertex2f(x - 2, y - 20);
        glVertex2f(x - 4, y - 34);
        glVertex2f(x + 2, y - 20);
        glVertex2f(x + 4, y - 34);
    glEnd();
}

static void drawWheel(float x, float y, float r) {
    glColor3f(0, 0, 0);
    drawCircle(x, y, r);
}

static void drawBus(float x) {
    float y0 = 78, y1 = 108;
    glColor3f(0.0f, 0.35f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(x, y0);
        glVertex2f(x + 150, y0);
        glVertex2f(x + 150, y1);
        glVertex2f(x, y1);
    glEnd();

    glColor3f(0.6f, 0.85f, 1);
    for (int i = 0; i < 3; i++) {
        float wx = x + 10 + (i * 31);
        glBegin(GL_QUADS);
            glVertex2f(wx, y0 + 8);
            glVertex2f(wx + 22, y0 + 8);
            glVertex2f(wx + 22, y1 - 6);
            glVertex2f(wx, y1 - 6);
        glEnd();
    }

    glColor3f(0.55f, 0.8f, 0.95f);
    glBegin(GL_QUADS);
        glVertex2f(x + 100, y0 + 3);
        glVertex2f(x + 122, y0 + 3);
        glVertex2f(x + 122, y1 - 3);
        glVertex2f(x + 100, y1 - 3);
    glEnd();

    drawWheel(x + 38, y0 - 1, 7.5f);
    drawWheel(x + 118, y0 - 1, 7.5f);
}

static void drawCar(float x, float r, float g, float b) {
    float y = ROAD_BOTTOM + 14;
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + 50, y);
        glVertex2f(x + 50, y + 18);
        glVertex2f(x, y + 18);
    glEnd();

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

} // namespace Scene4

void initScene4() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void displayScene4() {
    using namespace Scene4;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 400, 0, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float offset = (worldWidth - stageWidth) / 2.0f;
    if (offset < 0) offset = 0;

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

    if (planeActive == 1) drawPlane(planeX, 288);

    glPushMatrix();
        glTranslatef(offset, 0, 0);
        drawBuilding();
        drawDestinationBuilding();
        drawCollegeBoard();
    glPopMatrix();

    drawRoad(worldWidth);
    drawRoadLines(worldWidth);

    for (float tx = 20; tx < offset - 12; tx += 26) {
        drawTree(tx, SIDEWALK_TOP + 1);
        drawFlower(tx + 15, SIDEWALK_TOP + 1, 0.9f, 0.15f, 0.2f);
    }
    for (float tx = offset + stageWidth + 15; tx < worldWidth - 12; tx += 26) {
        drawTree(tx, SIDEWALK_TOP + 1);
        drawFlower(tx + 15, SIDEWALK_TOP + 1, 0.9f, 0.4f, 0.7f);
    }

    glPushMatrix();
        glTranslatef(offset, 0, 0);
        drawTree(8, SIDEWALK_TOP + 1);
        drawFlower(180, SIDEWALK_TOP + 1, 1.0f, 0.3f, 0.3f);
        drawFlower(340, SIDEWALK_TOP + 1, 1.0f, 0.8f, 0.2f);
        drawBusStop();

        if (passengerOut == 1) {
            drawPerson(person1X, personY);
            drawPerson(person2X, personY);
            drawPerson(person3X, personY);
        }

        if (scene != 0) drawBus(busX);
    glPopMatrix();

    drawCar(carAX, 0.95f, 0.95f, 0.95f);
    drawCar(carBX, 0.55f, 0.55f, 0.55f);
    drawCar(carCX, 0.85f, 0.1f, 0.1f);
    drawCar(carDX, 0.1f, 0.35f, 0.7f);
    drawCar(carEX, 0.9f, 0.7f, 0.1f);
}

void updateScene4() {
    using namespace Scene4;
    carAX -= carASpeed; if (carAX < -50) carAX = worldWidth + 30;
    carBX -= carBSpeed; if (carBX < -50) carBX = worldWidth + 130;
    carCX -= carCSpeed; if (carCX < -50) carCX = worldWidth + 230;
    carDX -= carDSpeed; if (carDX < -50) carDX = worldWidth + 330;
    carEX -= carESpeed; if (carEX < -50) carEX = worldWidth + 430;

    if (planeActive == 1) {
        planeX += 0.15f;
        if (planeX > worldWidth + 50) planeActive = 0;
    }

    if (scene == 1) {
        busX += 0.5f;
        if (busX > 75) scene = 2;
    } else if (scene == 3) {
        int arrivedCount = 0;
        if (person1X < person1TargetX) person1X += walkSpeed; else arrivedCount++;
        if (person2X < person2TargetX) person2X += walkSpeed; else arrivedCount++;
        if (person3X < person3TargetX) person3X += walkSpeed; else arrivedCount++;
        if (arrivedCount == 3) {
            passengersArrived = 1;
            scene = 4;
        }
    } else if (scene == 5) {
        busX += 1.2f;
        if (busX > stageWidth + 200) {
            busX = -150;
            scene = 0;
        }
    }
}

void keyboardScene4(unsigned char key) {
    using namespace Scene4;
    if (key == 'w' || key == 'W') { if (scene == 0) scene = 1; }
    else if (key == 'e' || key == 'E') { if (scene == 2) { passengerOut = 1; scene = 3; } }
    else if (key == 'l' || key == 'L') { if (scene == 4) scene = 5; }
}
