#include <GL/glut.h>
#include <cmath>

namespace Scene3 {

static const float PI = 3.14159265f;

/* ---------- scene layout (y bands, bottom to top) ---------- */
static const int GRASS_Y0          = 0;
static const int GRASS_Y1          = 120;
static const int SIDEWALK_FRONT_Y0 = 120;
static const int SIDEWALK_FRONT_Y1 = 150;
static const int ROAD_Y0           = 150;
static const int ROAD_Y1           = 300;
static const int SIDEWALK_BACK_Y0  = 300;
static const int SIDEWALK_BACK_Y1  = 330;
static const int SKY_Y0            = 330;
static const int SKY_Y1            = 650;

static const int CROSS_X0 = 460;   /* zebra crossing left edge  */
static const int CROSS_X1 = 560;   /* zebra crossing right edge */

/* Traffic light x-position */
static const int LIGHT_X = CROSS_X1 + 50;

static const int   BUS_WIDTH  = 220;
static const int   BUS_HEIGHT = 80;
static const float BUS_SPEED  = 1.6f;
static const int   STOP_LINE  = CROSS_X0 - 15;   /* buses hold here on red */

static const float PED_SPEED = 2.0f;
static const int   PED1_X    = CROSS_X0 + 30;
static const int   PED2_X    = CROSS_X0 + 70;

static const int   NUM_CLOUDS   = 3;
static const float CLOUD_SPEED  = 0.25f;

/* ---------- animation state ---------- */
enum { GREEN = 0, YELLOW, RED };
enum { BUS_APPROACHING = 0, BUS_STOPPING, PEDESTRIAN_CROSSING, BUS_DEPARTURE, SCENE_DONE };

static int phase = BUS_APPROACHING;   /* automatic state machine */
static int light = YELLOW;            /* light is YELLOW from the start */

static float pedY = SIDEWALK_FRONT_Y1;

static float bus1X = -260.0f;
static float bus2X = -700.0f;

static float cloudX[NUM_CLOUDS] = { 100, 400, 700 };
static float cloudY[NUM_CLOUDS] = { 600, 580, 610 };

/* -----------------------------------------------------------------
   Basic Shape Helpers
   ----------------------------------------------------------------- */
static void rect(float x, float y, float w, float h, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

static void circle(float cx, float cy, float radius, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= 30; i++) {
            float a = 2.0f * PI * i / 30;
            glVertex2f(cx + radius * cosf(a), cy + radius * sinf(a));
        }
    glEnd();
}

static void triangle(float x1, float y1, float x2, float y2, float x3, float y3,
              float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    glEnd();
}

/* -----------------------------------------------------------------
   Static Scenery
   ----------------------------------------------------------------- */
static void drawBackground()
{
    rect(0, SKY_Y0, 900, SKY_Y1 - SKY_Y0, 0.65f, 0.82f, 0.93f);
    rect(0, GRASS_Y0, 900, GRASS_Y1 - GRASS_Y0, 0.55f, 0.72f, 0.40f);
}

static void drawSun()
{
    float cx = 820, cy = 580;

    triangle(cx - 60, cy, cx - 35, cy + 15, cx - 35, cy - 15, 1, 0.8f, 0.1f);
    triangle(cx + 60, cy, cx + 35, cy + 15, cx + 35, cy - 15, 1, 0.8f, 0.1f);
    triangle(cx, cy + 60, cx - 15, cy + 35, cx + 15, cy + 35, 1, 0.8f, 0.1f);
    triangle(cx, cy - 60, cx - 15, cy - 35, cx + 15, cy - 35, 1, 0.8f, 0.1f);
    triangle(cx - 45, cy + 45, cx - 20, cy + 35, cx - 35, cy + 20, 1, 0.8f, 0.1f);
    triangle(cx + 45, cy + 45, cx + 20, cy + 35, cx + 35, cy + 20, 1, 0.8f, 0.1f);
    triangle(cx - 45, cy - 45, cx - 20, cy - 35, cx - 35, cy - 20, 1, 0.8f, 0.1f);
    triangle(cx + 45, cy - 45, cx + 20, cy - 35, cx + 35, cy - 20, 1, 0.8f, 0.1f);

    circle(cx, cy, 40, 1.0f, 0.82f, 0.15f);
}

static void drawSidewalks()
{
    rect(0, SIDEWALK_FRONT_Y0, 900, SIDEWALK_FRONT_Y1 - SIDEWALK_FRONT_Y0, 0.78f, 0.78f, 0.76f);
    rect(0, SIDEWALK_BACK_Y0,  900, SIDEWALK_BACK_Y1 - SIDEWALK_BACK_Y0,  0.78f, 0.78f, 0.76f);
}

static void drawRoad()
{
    rect(0, ROAD_Y0, 900, ROAD_Y1 - ROAD_Y0, 0.40f, 0.40f, 0.42f);
    for (int i = 0; i < 8; i++) {
        float sx = 20 + i * 110;
        if (sx + 45 < CROSS_X0 - 5 || sx > CROSS_X1 + 5)
            rect(sx, 220, 45, 8, 1, 1, 1);
    }
}

static void drawZebraCrossing()
{
    float gap = (ROAD_Y1 - ROAD_Y0) / 6.0f;
    for (int i = 0; i < 6; i++)
        rect(CROSS_X0, ROAD_Y0 + i * gap + gap * 0.15f, CROSS_X1 - CROSS_X0, gap * 0.7f, 1, 1, 1);
}

/* -----------------------------------------------------------------
   Movable Objects
   ----------------------------------------------------------------- */
static void drawBuilding()
{
    rect(0, 0, 200, 200, 0.93f, 0.72f, 0.42f);        /* body */

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            float wx = 20 + col * 60;
            float wy = 20 + row * 55;

            rect(wx - 3, wy - 3, 31, 31, 0.40f, 0.30f, 0.20f);  /* dark window frame */
            rect(wx, wy, 25, 25, 0.70f, 0.82f, 0.90f);          /* glass pane        */
            rect(wx + 11, wy, 3, 25, 0.40f, 0.30f, 0.20f);      /* vertical divider  */
            rect(wx, wy + 11, 25, 3, 0.40f, 0.30f, 0.20f);      /* horizontal divider*/
        }
    }

    rect(220, 0, 25, 40, 0.45f, 0.3f, 0.18f);          /* tree trunk   */
    circle(232, 80, 45, 0.2f, 0.45f, 0.22f);           /* tree canopy  */
}

static void drawCloud()
{
    circle(-25, 0, 18, 1, 1, 1);
    circle(  0, 10, 24, 1, 1, 1);
    circle( 25, 0, 18, 1, 1, 1);
}

static void drawTrafficLight()
{
    rect(-4, 0, 8, 90, 0.7f, 0.7f, 0.7f);           /* pole */
    rect(-22, 70, 44, 95, 0.22f, 0.22f, 0.22f);     /* box  */

    if (light == RED)
        circle(0, 145, 10, 0.90f, 0.12f, 0.12f);
    else
        circle(0, 145, 10, 0.35f, 0.18f, 0.18f);

    if (light == YELLOW)
        circle(0, 118, 10, 1.00f, 0.85f, 0.10f);
    else
        circle(0, 118, 10, 0.35f, 0.30f, 0.15f);

    if (light == GREEN)
        circle(0, 91, 10, 0.15f, 0.75f, 0.20f);
    else
        circle(0, 91, 10, 0.18f, 0.32f, 0.20f);
}

static void drawPerson(float r, float g, float b)
{
    circle(0, 55, 8, 1.0f, 0.85f, 0.7f);                       /* head  */
    triangle(-10, 20, 10, 20, 0, 47, r, g, b);                 /* shirt */

    glColor3f(0, 0, 0);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2f(0, 20);  glVertex2f(-8, 0);      /* left leg  */
        glVertex2f(0, 20);  glVertex2f( 8, 0);      /* right leg */
        glVertex2f(-10, 38); glVertex2f(-16, 20);   /* left arm  */
        glVertex2f( 10, 38); glVertex2f( 16, 20);   /* right arm */
    glEnd();
}

static void drawBus(float r, float g, float b)
{
    rect(0, 0, BUS_WIDTH, BUS_HEIGHT, r, g, b);
    for (int i = 0; i < 4; i++)
        rect(20 + i * 50, 35, 30, 28, 0.72f, 0.85f, 0.92f);
    circle(40, 0, 18, 0.1f, 0.1f, 0.1f);
    circle(180, 0, 18, 0.1f, 0.1f, 0.1f);
}

static void moveBus(float* x)
{
    if (phase == BUS_APPROACHING) {
        *x += BUS_SPEED;
    }
    else if (phase == BUS_STOPPING) {
        if (*x + BUS_WIDTH < STOP_LINE) {
            *x += BUS_SPEED;
            if (*x + BUS_WIDTH > STOP_LINE) *x = STOP_LINE - BUS_WIDTH; // snap to the line
        }
    }
    else if (phase == BUS_DEPARTURE) {
        *x += BUS_SPEED;
    }
}

} // namespace Scene3

// ==========================================
// SCENE 3: EXPOSED LIFECYCLE FUNCTIONS
// ==========================================

void initScene3()
{
    using namespace Scene3;
    glClearColor(1.0, 1.0, 1.0, 1.0);
    phase = BUS_APPROACHING;
    light = YELLOW;
    pedY = SIDEWALK_FRONT_Y1;
    bus1X = -260.0f;
    bus2X = -700.0f;
}

void displayScene3()
{
    using namespace Scene3;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 900, 0, 650);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawBackground();
    drawSun();

    for (int i = 0; i < NUM_CLOUDS; i++) {
        glPushMatrix();
            glTranslatef(cloudX[i], cloudY[i], 0);
            drawCloud();
        glPopMatrix();
    }

    /* Three buildings: left, middle, right */
    glPushMatrix(); glTranslatef(40,  SIDEWALK_BACK_Y1, 0); drawBuilding(); glPopMatrix();
    glPushMatrix(); glTranslatef(330, SIDEWALK_BACK_Y1, 0); drawBuilding(); glPopMatrix();
    glPushMatrix(); glTranslatef(650, SIDEWALK_BACK_Y1, 0); drawBuilding(); glPopMatrix();

    drawSidewalks();
    drawRoad();
    drawZebraCrossing();

    glPushMatrix();
        glTranslatef(LIGHT_X, SIDEWALK_BACK_Y1, 0);
        drawTrafficLight();
    glPopMatrix();

    glPushMatrix(); glTranslatef(PED1_X, pedY, 0); drawPerson(0.75f, 0.10f, 0.10f); glPopMatrix();
    glPushMatrix(); glTranslatef(PED2_X, pedY, 0); drawPerson(0.15f, 0.25f, 0.65f); glPopMatrix();

    glPushMatrix(); glTranslatef(bus1X, ROAD_Y0 + 20, 0); drawBus(0.95f, 0.80f, 0.35f); glPopMatrix();
    glPushMatrix(); glTranslatef(bus2X, ROAD_Y0 + 20, 0); drawBus(0.62f, 0.42f, 0.72f); glPopMatrix();
}

void updateScene3()
{
    using namespace Scene3;

    moveBus(&bus1X);
    moveBus(&bus2X);

    if (phase == BUS_APPROACHING) {
        light = YELLOW;
        if (bus1X + BUS_WIDTH >= STOP_LINE - 6 || bus2X + BUS_WIDTH >= STOP_LINE - 6) {
            phase = BUS_STOPPING;
            light = RED;
        }
    }
    else if (phase == BUS_STOPPING) {
        light = RED;
        if (bus1X + BUS_WIDTH >= STOP_LINE && bus2X + BUS_WIDTH >= STOP_LINE) {
            phase = PEDESTRIAN_CROSSING;
        }
    }
    else if (phase == PEDESTRIAN_CROSSING) {
        light = RED;

        pedY += PED_SPEED;
        if (pedY >= SIDEWALK_BACK_Y0) {
            pedY = SIDEWALK_BACK_Y0;
            phase = BUS_DEPARTURE;
            light = GREEN;
        }
    }
    else if (phase == BUS_DEPARTURE) {
        light = GREEN;
        if (bus1X > 950 && bus2X > 950) {
            phase = SCENE_DONE;
        }
    }

    for (int i = 0; i < NUM_CLOUDS; i++) {
        cloudX[i] += CLOUD_SPEED;
        if (cloudX[i] > 950) cloudX[i] = -100;
    }
}

void keyboardScene3(unsigned char key)
{
    // Auto-synchronized sequence: no key presses required
}
