/* =================================================================
   PROJECT : Animated 2D City Scene using OpenGL + GLUT  (SIMPLIFIED)
   CHANGES FROM THE ORIGINAL VERSION
   -----------------------------------------------------------------
   1) Every moving/repeated object (buildings, clouds, the traffic
      light, pedestrians, buses) is now drawn ONCE around the local
      origin (0,0). glPushMatrix() + glTranslatef() + glPopMatrix()
      slides that whole drawing to wherever it needs to be. This
      means the shape functions no longer add "+x" / "+baseY" to
      every single vertex - much shorter and much easier to read.
   2) The traffic light was standing on the GRASS/FRONT-sidewalk
      side of the road. It has been moved to the BACK-sidewalk side
      (the buildings' side) - the opposite side of the road.
   3) Fewer buildings (2), a plain 3-circle cartoon cloud instead of
      a trig-driven cloud shape, fewer sun rays, and no separate
      "busApproachingStopLine / busIsStopped" helper functions -
      the same checks are done inline with simple if-conditions.

   The animation logic is unchanged:
     buses drive -> a bus nears the crossing -> light turns RED and
     all buses stop -> once every bus is stopped, two pedestrians
     cross -> once they reach the far sidewalk -> light turns GREEN
     and buses move again. Clouds drift the whole time, always.

   COMPILE (Linux):  gcc city_scene_simple.c -o city_scene -lGL -lGLU -lglut -lm
   ================================================================= */

#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265f

/* ---------- scene layout (y bands, bottom to top) ---------- */
#define GRASS_Y0            0
#define GRASS_Y1            120
#define SIDEWALK_FRONT_Y0   120
#define SIDEWALK_FRONT_Y1   150
#define ROAD_Y0             150
#define ROAD_Y1             300
#define SIDEWALK_BACK_Y0    300
#define SIDEWALK_BACK_Y1    330
#define SKY_Y0              330
#define SKY_Y1              650

#define CROSS_X0            460     /* zebra crossing left edge  */
#define CROSS_X1            560     /* zebra crossing right edge */

/* Traffic light x-position. It now sits past the RIGHT edge of the
   crossing but is translated to SIDEWALK_BACK_Y1 in display(), so
   it stands on the far/back side of the road instead of the front. */
#define LIGHT_X             (CROSS_X1 + 50)

#define BUS_WIDTH           220
#define BUS_HEIGHT          80
#define BUS_SPEED           1.6f
#define STOP_LINE           (CROSS_X0 - 15)   /* buses hold here on red */

#define PED_SPEED           2.0f
#define PED1_X              (CROSS_X0 + 30)
#define PED2_X              (CROSS_X0 + 70)

#define NUM_CLOUDS          3
#define CLOUD_SPEED         0.25f

/* ---------- animation state ---------- */
enum { GREEN = 0, RED };
enum { BUSES_MOVING = 0, BUSES_STOPPING, PEOPLE_CROSSING };

int   phase = BUSES_MOVING;
int   light = GREEN;

float pedY   = SIDEWALK_BACK_Y0;   /* pedestrians' feet height, animates */
int   pedDir = -1;                  /* -1 = walking toward front, +1 = back */

float bus1X = -260.0f;
float bus2X = -700.0f;

float cloudX[NUM_CLOUDS] = { 100, 400, 700 };
float cloudY[NUM_CLOUDS] = { 600, 580, 610 };

/* -----------------------------------------------------------------
   STEP 1: three basic shape helpers - everything else is built
   from just these.
   ----------------------------------------------------------------- */
void rect(float x, float y, float w, float h, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

void circle(float cx, float cy, float radius, float r, float g, float b)
{
    int i;
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (i = 0; i <= 30; i++) {
            float a = 2.0f * PI * i / 30;
            glVertex2f(cx + radius * cosf(a), cy + radius * sinf(a));
        }
    glEnd();
}

void triangle(float x1, float y1, float x2, float y2, float x3, float y3,
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
   STEP 2a: static scenery - drawn once, straight in world
   coordinates, because it never moves.
   ----------------------------------------------------------------- */
void drawBackground(void)
{
    rect(0, SKY_Y0, 900, SKY_Y1 - SKY_Y0, 0.65f, 0.82f, 0.93f);
    rect(0, GRASS_Y0, 900, GRASS_Y1 - GRASS_Y0, 0.55f, 0.72f, 0.40f);
}

void drawSun(void)
{
    circle(820, 580, 40, 1.0f, 0.82f, 0.15f);
    triangle(760, 580, 785, 595, 785, 565, 1, 0.8f, 0.1f);   /* left ray   */
    triangle(880, 580, 855, 595, 855, 565, 1, 0.8f, 0.1f);   /* right ray  */
    triangle(820, 640, 805, 615, 835, 615, 1, 0.8f, 0.1f);   /* top ray    */
    triangle(820, 520, 805, 545, 835, 545, 1, 0.8f, 0.1f);   /* bottom ray */
}

void drawSidewalks(void)
{
    rect(0, SIDEWALK_FRONT_Y0, 900, SIDEWALK_FRONT_Y1 - SIDEWALK_FRONT_Y0, 0.78f, 0.78f, 0.76f);
    rect(0, SIDEWALK_BACK_Y0,  900, SIDEWALK_BACK_Y1 - SIDEWALK_BACK_Y0,  0.78f, 0.78f, 0.76f);
}

void drawRoad(void)
{
    int i;
    rect(0, ROAD_Y0, 900, ROAD_Y1 - ROAD_Y0, 0.40f, 0.40f, 0.42f);
    for (i = 0; i < 8; i++) {
        float sx = 20 + i * 110;
        if (sx + 45 < CROSS_X0 - 5 || sx > CROSS_X1 + 5)
            rect(sx, 220, 45, 8, 1, 1, 1);
    }
}

void drawZebraCrossing(void)
{
    int i;
    float gap = (ROAD_Y1 - ROAD_Y0) / 6.0f;
    for (i = 0; i < 6; i++)
        rect(CROSS_X0, ROAD_Y0 + i * gap + gap * 0.15f, CROSS_X1 - CROSS_X0, gap * 0.7f, 1, 1, 1);
}

/* -----------------------------------------------------------------
   STEP 2b: movable objects. Each one is drawn as if it lived at the
   ORIGIN (0,0). display() calls glTranslatef() first, so the whole
   shape appears wherever we want, with no per-vertex "+x" math here.
   ----------------------------------------------------------------- */

/* Building: bottom-left corner is local (0,0). */
void drawBuilding(void)
{
    int row, col;
    rect(0, 0, 200, 200, 0.93f, 0.72f, 0.42f);        /* body   */
    for (row = 0; row < 2; row++)
        for (col = 0; col < 2; col++)
            rect(30 + col * 90, 30 + row * 90, 40, 40, 0.7f, 0.82f, 0.9f); /* windows */

    rect(220, 0, 25, 40, 0.45f, 0.3f, 0.18f);          /* tree trunk   */
    circle(232, 80, 45, 0.2f, 0.45f, 0.22f);           /* tree canopy  */
}

/* Cloud: a simple 3-circle puff centered on local (0,0). No trig
   needed - just three overlapping circles. */
void drawCloud(void)
{
    circle(-25, 0, 18, 1, 1, 1);
    circle(  0, 10, 24, 1, 1, 1);
    circle( 25, 0, 18, 1, 1, 1);
}

/* Traffic light: pole base is local (0,0). Caller translates this to
   (LIGHT_X, SIDEWALK_BACK_Y1) - the BACK side of the road, which is
   the opposite side from where the light used to stand. */
void drawTrafficLight(void)
{
    rect(-5, 0, 10, 140, 0.7f, 0.7f, 0.7f);        /* pole */
    rect(-35, 100, 70, 110, 0.22f, 0.22f, 0.22f);  /* box  */

    if (light == RED)
        circle(0, 175, 16, 0.90f, 0.12f, 0.12f);
    else
        circle(0, 175, 16, 0.35f, 0.18f, 0.18f);

    if (light == GREEN)
        circle(0, 135, 16, 0.15f, 0.75f, 0.20f);
    else
        circle(0, 135, 16, 0.18f, 0.32f, 0.20f);
}

/* Pedestrian: feet are at local (0,0). */
void drawPerson(float r, float g, float b)
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

/* Bus: bottom-left corner is local (0,0). */
void drawBus(float r, float g, float b)
{
    int i;
    rect(0, 0, BUS_WIDTH, BUS_HEIGHT, r, g, b);
    for (i = 0; i < 4; i++)
        rect(20 + i * 50, 35, 30, 28, 0.72f, 0.85f, 0.92f);
    circle(40, 0, 18, 0.1f, 0.1f, 0.1f);
    circle(180, 0, 18, 0.1f, 0.1f, 0.1f);
}

/* -----------------------------------------------------------------
   STEP 3: animation - advance the state machine, then move buses,
   pedestrians and clouds.
   ----------------------------------------------------------------- */
void moveBus(float *x)
{
    if (phase == BUSES_MOVING) {
        *x += BUS_SPEED;
        if (*x > 950) *x = -BUS_WIDTH - 100.0f;    /* wrap around off-screen */
    } else if (*x + BUS_WIDTH < STOP_LINE) {
        *x += BUS_SPEED;
        if (*x + BUS_WIDTH > STOP_LINE) *x = STOP_LINE - BUS_WIDTH; /* snap to the line */
    }
    /* else: bus already reached the line - stays put */
}

void update(int value)
{
    int i;

    moveBus(&bus1X);
    moveBus(&bus2X);

    if (phase == BUSES_MOVING) {
        light = GREEN;
        /* event: a bus is close enough to the stop line -> go red */
        if (bus1X + BUS_WIDTH >= STOP_LINE - 6 || bus2X + BUS_WIDTH >= STOP_LINE - 6) {
            phase = BUSES_STOPPING;
            light = RED;
        }
    }
    else if (phase == BUSES_STOPPING) {
        /* event: BOTH buses have fully stopped -> let people cross */
        if (bus1X + BUS_WIDTH >= STOP_LINE && bus2X + BUS_WIDTH >= STOP_LINE)
            phase = PEOPLE_CROSSING;
    }
    else { /* PEOPLE_CROSSING */
        pedY += pedDir * PED_SPEED;
        if (pedY < SIDEWALK_FRONT_Y1) pedY = SIDEWALK_FRONT_Y1;
        if (pedY > SIDEWALK_BACK_Y0)  pedY = SIDEWALK_BACK_Y0;

        /* event: pedestrians reached the far sidewalk -> go green */
        if ((pedDir < 0 && pedY <= SIDEWALK_FRONT_Y1) ||
            (pedDir > 0 && pedY >= SIDEWALK_BACK_Y0)) {
            pedDir = -pedDir;           /* cross back next time */
            phase  = BUSES_MOVING;
            light  = GREEN;
        }
    }

    for (i = 0; i < NUM_CLOUDS; i++) {
        cloudX[i] += CLOUD_SPEED;
        if (cloudX[i] > 950) cloudX[i] = -100;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);   /* ~60 fps */
}

/* -----------------------------------------------------------------
   STEP 4: draw one frame, back to front. Every moving object is
   positioned with glPushMatrix()/glTranslatef()/glPopMatrix().
   ----------------------------------------------------------------- */
void display(void)
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();
    drawSun();

    for (i = 0; i < NUM_CLOUDS; i++) {
        glPushMatrix();
            glTranslatef(cloudX[i], cloudY[i], 0);
            drawCloud();
        glPopMatrix();
    }

    glPushMatrix(); glTranslatef(40,  SIDEWALK_BACK_Y1, 0); drawBuilding(); glPopMatrix();
    glPushMatrix(); glTranslatef(650, SIDEWALK_BACK_Y1, 0); drawBuilding(); glPopMatrix();

    drawSidewalks();
    drawRoad();
    drawZebraCrossing();

    /* traffic light now on the BACK side of the road (opposite side
       from the original version, which stood near the grass/front) */
    glPushMatrix();
        glTranslatef(LIGHT_X, SIDEWALK_BACK_Y1, 0);
        drawTrafficLight();
    glPopMatrix();

    glPushMatrix(); glTranslatef(PED1_X, pedY, 0); drawPerson(0.75f, 0.10f, 0.10f); glPopMatrix();
    glPushMatrix(); glTranslatef(PED2_X, pedY, 0); drawPerson(0.15f, 0.25f, 0.65f); glPopMatrix();

    glPushMatrix(); glTranslatef(bus1X, ROAD_Y0 + 20, 0); drawBus(0.95f, 0.80f, 0.35f); glPopMatrix();
    glPushMatrix(); glTranslatef(bus2X, ROAD_Y0 + 20, 0); drawBus(0.62f, 0.42f, 0.72f); glPopMatrix();

    glutSwapBuffers();
}

/* -----------------------------------------------------------------
   STEP 5 + 6: init and main
   ----------------------------------------------------------------- */
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, 900, 0, 650);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 650);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D City Scene - Simplified");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);
    glutMainLoop();

    return 0;
}
