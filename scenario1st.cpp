/*

#include <GL/glut.h>
#include <math.h>


#define WIN_W       800.0f
#define WIN_H       600.0f
#define BUS_WIDTH   190.0f
#define BUS_HEIGHT  65.0f
#define BUS_SPEED   2.0f
#define BUS_GAP     400.0f

float busOffset = 0.0f;


void setColor(float r, float g, float b) { glColor3f(r, g, b); }

void drawCircle(float cx, float cy, float r, int filled) {
    glBegin(filled ? GL_POLYGON : GL_LINE_LOOP);
    for (int i = 0; i < 360; i += 10) {
        float a = i * 3.14159f / 180.0f;
        glVertex2f(cx + r * cos(a), cy + r * sin(a));
    }
    glEnd();
}

void drawRect(float x, float y, float w, float h, int filled) {
    glBegin(filled ? GL_QUADS : GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}


void drawRotatedRect(float cx, float cy, float w, float h, float angleDeg, int filled) {
    glPushMatrix();
    glTranslatef(cx, cy, 0);
    glRotatef(angleDeg, 0, 0, 1);
    glBegin(filled ? GL_QUADS : GL_LINE_LOOP);
    glVertex2f(-w / 2, -h / 2);
    glVertex2f(w / 2, -h / 2);
    glVertex2f(w / 2, h / 2);
    glVertex2f(-w / 2, h / 2);
    glEnd();
    glPopMatrix();
}

void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawDashedLineH(float xStart, float xEnd, float y, float dashLen, float gapLen) {
    float x = xStart;
    while (x < xEnd) {
        float xe = x + dashLen;
        if (xe > xEnd) xe = xEnd;
        drawLine(x, y, xe, y);
        x += dashLen + gapLen;
    }
}


void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);
}



void drawSky() {
    setColor(0.55f, 0.78f, 0.95f);
    drawRect(0, 0, 800, 600, 1);
}


void drawSun() {
    setColor(1.0f, 0.85f, 0.2f);
    drawCircle(700, 520, 35, 1);
}


void drawCloud(float x, float y) {
    setColor(1, 1, 1);
    drawCircle(x, y, 18, 1);
    drawCircle(x + 20, y + 8, 22, 1);
    drawCircle(x + 45, y, 16, 1);
    drawCircle(x + 20, y - 6, 20, 1);
}



void drawWindow(float x, float y, float w, float h) {
    setColor(0.65f, 0.85f, 1.0f);
    drawRect(x, y, w, h, 1);
    setColor(0.15f, 0.15f, 0.15f);
    drawRect(x, y, w, h, 0);
    drawLine(x + w / 2, y, x + w / 2, y + h);
    drawLine(x, y + h / 2, x + w, y + h / 2);
}

void drawBuilding(float x, float y, float w, float h, int cols, int rows,
                   float r, float g, float b,
                   float accR, float accG, float accB,
                   int hasAntenna, int hasBalcony) {

    setColor(r, g, b);
    drawRect(x, y, w, h, 1);
    setColor(0, 0, 0);
    drawRect(x, y, w, h, 0);

    setColor(0.3f, 0.3f, 0.32f);
    drawRect(x - 4, y + h, w + 8, 8, 1);
    setColor(0, 0, 0);
    drawRect(x - 4, y + h, w + 8, 8, 0);

    if (hasAntenna) {
        drawLine(x + w / 2, y + h + 8, x + w / 2, y + h + 34);
        drawCircle(x + w / 2, y + h + 34, 2.5f, 1);
    }

    setColor(0.4f, 0.35f, 0.3f);
    drawRect(x - 2, y + h * 0.22f, w + 4, 5, 1);

    float colW = w / (cols * 2.0f);
    float rowH = h / (rows * 2.2f);
    for (int rIdx = 1; rIdx < rows; rIdx++) {
        for (int c = 0; c < cols; c++) {
            float wx = x + colW + c * (colW * 2);
            float wy = y + rowH * 1.2f + rIdx * (rowH * 1.6f);
            drawWindow(wx, wy, colW, rowH);

            if (hasBalcony && rIdx == rows - 1 && c == 0) {
                setColor(0.3f, 0.3f, 0.3f);
                drawRect(wx - 4, wy - 6, colW + 8, 4, 1);
                drawLine(wx - 4, wy - 6, wx - 4, wy);
                drawLine(wx + colW + 4, wy - 6, wx + colW + 4, wy);
            }
        }
    }

    setColor(0.4f, 0.25f, 0.15f);
    drawRect(x + w / 2 - 9, y, 18, 30, 1);
    setColor(0, 0, 0);
    drawRect(x + w / 2 - 9, y, 18, 30, 0);
    drawLine(x + w / 2, y, x + w / 2, y + 30);

    setColor(accR, accG, accB);
    drawRect(x + w / 2 - 16, y + 30, 32, 6, 1);
}



void drawSidewalk() {
    setColor(0.70f, 0.70f, 0.68f);
    drawRect(0, 90, 800, 28, 1);

    setColor(0.82f, 0.82f, 0.80f);
    drawRect(0, 118, 800, 22, 1);

    setColor(0.42f, 0.38f, 0.28f);
    drawRect(0, 140, 800, 10, 1);

    setColor(0.92f, 0.92f, 0.90f);
    drawRect(0, 88, 800, 3, 1);

    setColor(0.55f, 0.55f, 0.53f);
    drawLine(0, 118, 800, 118);
    drawLine(0, 140, 800, 140);

    setColor(0.65f, 0.65f, 0.63f);
    for (int x = 10; x < 800; x += 35)
        drawLine(x, 120, x, 138);
}


void drawTree(float x, float y) {
    setColor(0.42f, 0.26f, 0.1f);
    drawRect(x - 5, y, 10, 34, 1);
    setColor(0, 0, 0);
    drawRect(x - 5, y, 10, 34, 0);

    setColor(0.13f, 0.5f, 0.18f);
    drawCircle(x, y + 55, 22, 1);
    drawCircle(x - 18, y + 45, 18, 1);
    drawCircle(x + 18, y + 45, 18, 1);
    drawCircle(x, y + 74, 17, 1);
    drawCircle(x - 10, y + 68, 15, 1);
    drawCircle(x + 10, y + 68, 15, 1);
}



void drawBusStopSign(float x, float yBase) {
    setColor(0.25f, 0.25f, 0.25f);
    drawRect(x - 1.5f, yBase, 3, 26, 1);

    setColor(0.10f, 0.35f, 0.75f);
    drawRect(x - 16, yBase + 26, 32, 22, 1);
    setColor(1, 1, 1);
    drawRect(x - 16, yBase + 26, 32, 22, 0);

    setColor(1, 1, 1);
    drawText(x - 11, yBase + 40, "BUS");
    drawText(x - 14, yBase + 30, "STOP");
}

void drawPersonShapes(float x, float y, float r, float g, float b) {
    setColor(0.2f, 0.2f, 0.2f);
    drawRect(x - 4, y, 3, 15, 1);
    drawRect(x + 1, y, 3, 15, 1);

    setColor(r, g, b);
    drawRect(x - 5, y + 15, 10, 17, 1);

    drawRotatedRect(x - 8, y + 28, 13, 4, 25, 1);
    drawRotatedRect(x + 8, y + 28, 13, 4, -25, 1);

    setColor(0.9f, 0.75f, 0.6f);
    drawCircle(x, y + 39, 6, 1);
    setColor(0, 0, 0);
    drawCircle(x, y + 39, 6, 0);
}



void drawRoad() {
    setColor(0.22f, 0.22f, 0.24f);
    drawRect(0, 0, 800, 90, 1);

    setColor(1, 1, 1);
    drawDashedLineH(0, 800, 30, 25, 18);

    setColor(0.95f, 0.85f, 0.1f);
    drawLine(0, 60, 800, 60);
    drawLine(0, 63, 800, 63);

    setColor(1, 1, 1);
    for (int i = 0; i < 6; i++)
        drawRect(340 + i * 18, 5, 10, 80, 1);
}

void drawBusStopZoneMarking(float xCenter) {
    setColor(0.95f, 0.85f, 0.1f);
    drawDashedLineH(xCenter - 40, xCenter + 40, 87, 10, 6);
}



void drawBus(float x, float y, float w, float h, float r, float g, float b) {
    setColor(r, g, b);
    drawRect(x, y, w, h, 1);
    setColor(0, 0, 0);
    drawRect(x, y, w, h, 0);

    setColor(r * 0.65f, g * 0.65f, b * 0.65f);
    drawRect(x, y + h - 8, w, 8, 1);

    float doorW = w * 0.11f;
    float doorX = x + w * 0.06f;
    setColor(0.55f, 0.68f, 0.78f);
    drawRect(doorX, y, doorW, h * 0.78f, 1);
    setColor(0, 0, 0);
    drawRect(doorX, y, doorW, h * 0.78f, 0);
    drawLine(doorX + doorW / 2, y, doorX + doorW / 2, y + h * 0.78f);

    int nWin = 4;
    float winStartX = doorX + doorW + w * 0.05f;
    float winAreaW = (x + w) - winStartX - w * 0.05f;
    float winW = winAreaW / (nWin * 1.4f);
    float gap = (winAreaW - nWin * winW) / (nWin + 1);
    for (int i = 0; i < nWin; i++) {
        float wx = winStartX + gap + i * (winW + gap);
        setColor(0.7f, 0.9f, 1.0f);
        drawRect(wx, y + h * 0.5f, winW, h * 0.35f, 1);
        setColor(0, 0, 0);
        drawRect(wx, y + h * 0.5f, winW, h * 0.35f, 0);
    }

    setColor(0.1f, 0.1f, 0.1f);
    drawCircle(x + w * 0.20f, y, 12, 1);
    drawCircle(x + w * 0.80f, y, 12, 1);
    setColor(0.65f, 0.65f, 0.65f);
    drawCircle(x + w * 0.20f, y, 5, 1);
    drawCircle(x + w * 0.80f, y, 5, 1);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawSky();
    drawSun();
    drawCloud(120, 520);
    drawCloud(400, 560);
    drawCloud(620, 500);

    drawBuilding(160, 150, 90, 170, 2, 4, 0.85f, 0.75f, 0.6f, 0.8f, 0.2f, 0.2f, 1, 0);
    drawBuilding(260, 150, 75, 140, 2, 3, 0.65f, 0.75f, 0.85f, 0.9f, 0.6f, 0.1f, 0, 0);
    drawBuilding(345, 150, 95, 215, 3, 5, 0.8f, 0.55f, 0.5f, 0.2f, 0.5f, 0.8f, 1, 1);
    drawBuilding(450, 150, 85, 155, 2, 3, 0.75f, 0.8f, 0.7f, 0.8f, 0.2f, 0.2f, 0, 0);
    drawBuilding(545, 150, 105, 185, 3, 4, 0.9f, 0.85f, 0.7f, 0.2f, 0.5f, 0.8f, 0, 0);
    drawBuilding(660, 150, 80, 150, 2, 3, 0.7f, 0.65f, 0.8f, 0.9f, 0.6f, 0.1f, 0, 0);

    drawSidewalk();

    drawTree(120, 140);
    drawTree(235, 140);
    drawTree(330, 140);
    drawTree(435, 140);
    drawTree(530, 140);
    drawTree(630, 140);
    drawTree(710, 140);


    drawBusStopSign(170, 90);
    drawPersonShapes(200, 92, 0.2f, 0.3f, 0.8f);

    drawBusStopSign(470, 90);
    drawPersonShapes(500, 92, 0.8f, 0.3f, 0.2f);

    drawRoad();
    drawBusStopZoneMarking(170);
    drawBusStopZoneMarking(470);


    float bus1X = -BUS_WIDTH + busOffset;
    float bus2X = -BUS_WIDTH + fmodf(busOffset + BUS_GAP, WIN_W + BUS_WIDTH);
    drawBus(bus1X, 15, BUS_WIDTH, BUS_HEIGHT, 0.85f, 0.15f, 0.15f);
    drawBus(bus2X, 15, BUS_WIDTH, BUS_HEIGHT, 0.9f, 0.55f, 0.1f);

    glutSwapBuffers();
}


void animate(int value) {
    busOffset += BUS_SPEED;
    if (busOffset > WIN_W + BUS_WIDTH)
        busOffset -= (WIN_W + BUS_WIDTH);

    glutPostRedisplay();
    glutTimerFunc(16, animate, 0);
}


void init() {
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800, 0, 600);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("City Street Scene - Animated");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, animate, 0);
    glutMainLoop();
    return 0;
}
*/
