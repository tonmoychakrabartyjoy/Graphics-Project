/*#include <GL/glut.h>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

const float PI = 3.14f;

float fanAngle = 0.0f;
float fanSpeed = 180.0f;
bool fanOn = true;

float waveTime = 0.0f;
bool waving = true;

bool blinkEnabled = true;
bool textVisible = true;
float blinkTimer = 0.0f;

int lastUpdateTime = 0;

void setColor(float r, float g, float b)
{
    glColor3f(r, g, b);
}

void drawLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

void drawQuad(
    float x1, float y1,
    float x2, float y2,
    float x3, float y3,
    float x4, float y4)
{
    glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glVertex2f(x4, y4);
    glEnd();
}

void drawCircle(float cx, float cy, float r, int segments = 60)
{
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * PI * i / segments;
        float x = r * cos(theta);
        float y = r * sin(theta);
        glVertex2f(cx + x, cy + y);
    }

    glEnd();
}

void drawFilledCircle(float cx, float cy, float r, int segments = 60)
{
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);

        for (int i = 0; i <= segments; i++)
        {
            float theta = 2.0f * PI * i / segments;

            glVertex2f(
                cx + r * cos(theta),
                cy + r * sin(theta)
            );
        }
    glEnd();
}

void drawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);

    for (int i = 0; i < strlen(text); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}


void drawRoom()
{
    glLineWidth(2.0f);

    setColor(
        248.0f / 255.0f,
        249.0f / 255.0f,
        250.0f / 255.0f
    );

    glBegin(GL_QUADS);
        glVertex2f(3.0f, 59.0f);
        glVertex2f(96.0f, 59.0f);
        glVertex2f(81.0f, 52.0f);
        glVertex2f(20.0f, 52.0f);
    glEnd();

    setColor(
        240.0f / 255.0f,
        235.0f / 255.0f,
        225.0f / 255.0f
    );

    glBegin(GL_QUADS);
        glVertex2f(3.0f, 59.0f);
        glVertex2f(20.0f, 52.0f);
        glVertex2f(20.0f, 14.0f);
        glVertex2f(3.0f, 2.0f);
    glEnd();

    setColor(
        70.0f / 255.0f,
        130.0f / 255.0f,
        180.0f / 255.0f
    );

    glBegin(GL_QUADS);
        glVertex2f(20.0f, 52.0f);
        glVertex2f(81.0f, 52.0f);
        glVertex2f(81.0f, 14.0f);
        glVertex2f(20.0f, 14.0f);
    glEnd();

    setColor(
        70.0f / 255.0f,
        130.0f / 255.0f,
        180.0f / 255.0f
    );

    glBegin(GL_QUADS);
        glVertex2f(96.0f, 59.0f);
        glVertex2f(81.0f, 52.0f);
        glVertex2f(81.0f, 14.0f);
        glVertex2f(96.0f, 2.0f);
    glEnd();

    setColor(
        101.0f / 255.0f,
        67.0f / 255.0f,
        33.0f / 255.0f
    );

    glBegin(GL_QUADS);
        glVertex2f(3.0f, 2.0f);
        glVertex2f(20.0f, 14.0f);
        glVertex2f(81.0f, 14.0f);
        glVertex2f(96.0f, 2.0f);
    glEnd();


    setColor(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_LOOP);
        glVertex2f(3.0f, 59.0f);
        glVertex2f(96.0f, 59.0f);
        glVertex2f(96.0f, 2.0f);
        glVertex2f(3.0f, 2.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(20.0f, 52.0f);
        glVertex2f(81.0f, 52.0f);
        glVertex2f(81.0f, 14.0f);
        glVertex2f(20.0f, 14.0f);
    glEnd();

    drawLine(3.0f, 59.0f, 20.0f, 52.0f);
    drawLine(96.0f, 59.0f, 81.0f, 52.0f);
    drawLine(3.0f, 2.0f, 20.0f, 14.0f);
    drawLine(96.0f, 2.0f, 81.0f, 14.0f);
}

void drawTable()
{

    setColor(
        139.0f / 255.0f,
        69.0f / 255.0f,
        19.0f / 255.0f
    );

    glBegin(GL_QUADS);
        glVertex2f(14.5f, 14.8f);
        glVertex2f(35.5f, 16.3f);
        glVertex2f(38.2f, 13.8f);
        glVertex2f(16.5f, 11.7f);
    glEnd();

    setColor(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINE_LOOP);
        glVertex2f(14.5f, 14.8f);
        glVertex2f(35.5f, 16.3f);
        glVertex2f(38.2f, 13.8f);
        glVertex2f(16.5f, 11.7f);
    glEnd();

    setColor(
        40.0f / 255.0f,
        40.0f / 255.0f,
        40.0f / 255.0f
    );

    glBegin(GL_QUADS);
        glVertex2f(17.4f, 11.8f);
        glVertex2f(18.8f, 11.9f);
        glVertex2f(16.7f, 4.0f);
        glVertex2f(15.4f, 4.0f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(35.0f, 13.5f);
        glVertex2f(36.4f, 13.7f);
        glVertex2f(34.5f, 5.0f);
        glVertex2f(33.2f, 5.0f);
    glEnd();

    setColor(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINE_LOOP);
        glVertex2f(17.4f, 11.8f);
        glVertex2f(18.8f, 11.9f);
        glVertex2f(16.7f, 4.0f);
        glVertex2f(15.4f, 4.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(35.0f, 13.5f);
        glVertex2f(36.4f, 13.7f);
        glVertex2f(34.5f, 5.0f);
        glVertex2f(33.2f, 5.0f);
    glEnd();

    glLineWidth(2.0f);

    drawLine(16.0f, 7.0f, 34.0f, 7.0f);
    drawLine(16.0f, 6.7f, 34.0f, 6.7f);
}

void drawPerson()
{
    setColor(0.95f, 0.80f, 0.65f);
    drawFilledCircle(44.3f, 26.5f, 4.2f);

    setColor(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);

    drawCircle(44.3f, 26.5f, 4.2f);

    setColor(0.3f, 0.55f, 0.85f);

    glBegin(GL_QUADS);
        glVertex2f(41.7f, 21.8f);
        glVertex2f(46.9f, 21.5f);
        glVertex2f(47.2f, 14.2f);
        glVertex2f(41.7f, 14.5f);
    glEnd();

    setColor(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_LOOP);
        glVertex2f(41.7f, 21.8f);
        glVertex2f(46.9f, 21.5f);
        glVertex2f(47.2f, 14.2f);
        glVertex2f(41.7f, 14.5f);
    glEnd();

    glLineWidth(3.0f);

    drawLine(41.8f, 20.5f, 38.7f, 16.5f);

    drawLine(46.8f, 20.5f, 49.0f, 22.7f);

    float waveAngle = 0.0f;

    if (waving)
    {
        waveAngle = 30.0f * sin(waveTime * 5.0f);
    }

    glPushMatrix();

    glTranslatef(49.0f, 22.7f, 0.0f);

    glRotatef(waveAngle, 0.0f, 0.0f, 1.0f);

    drawLine(0.0f, 0.0f, 1.0f, 4.0f);

    setColor(0.95f, 0.80f, 0.65f);

    drawFilledCircle(1.0f, 4.0f, 0.40f, 20);

    glPopMatrix();

    setColor(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);

    drawLine(43.0f, 14.3f, 42.0f, 6.0f);
    drawLine(45.8f, 14.3f, 47.0f, 6.0f);

    drawLine(42.0f, 6.0f, 40.5f, 5.7f);
    drawLine(47.0f, 6.0f, 48.5f, 5.7f);
}


void drawDoor()
{

    setColor(
        139.0f / 255.0f,
        69.0f / 255.0f,
        19.0f / 255.0f
    );

    glBegin(GL_QUADS);
        glVertex2f(68.0f, 34.0f);
        glVertex2f(79.0f, 34.0f);
        glVertex2f(79.0f, 17.0f);
        glVertex2f(68.0f, 17.0f);
    glEnd();

    setColor(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINE_LOOP);
        glVertex2f(68.0f, 34.0f);
        glVertex2f(79.0f, 34.0f);
        glVertex2f(79.0f, 17.0f);
        glVertex2f(68.0f, 17.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(70.0f, 32.0f);
        glVertex2f(77.0f, 32.0f);
        glVertex2f(77.0f, 19.0f);
        glVertex2f(70.0f, 19.0f);
    glEnd();

    drawFilledCircle(75.5f, 25.0f, 0.45f, 20);
}

void drawClock()
{
    float cx = 72.6f;
    float cy = 42.6f;
    float radius = 5.5f;

    setColor(0.95f, 0.95f, 0.85f);

    drawFilledCircle(cx, cy, radius);

    setColor(
        184.0f / 255.0f,
        115.0f / 255.0f,
        51.0f / 255.0f
    );

    glLineWidth(2.0f);

    drawCircle(cx, cy, radius);

    setColor(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < 12; i++)
    {
        float angle = i * PI / 6.0f;

        float x1 = cx + (radius - 0.5f) * sin(angle);
        float y1 = cy + (radius - 0.5f) * cos(angle);

        float x2 = cx + (radius - 1.1f) * sin(angle);
        float y2 = cy + (radius - 1.1f) * cos(angle);

        drawLine(x1, y1, x2, y2);
    }

    time_t currentTime = time(NULL);
    tm* localTime = localtime(&currentTime);

    int hour = localTime->tm_hour % 12;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;

    float secondAngle =
        second * 6.0f * PI / 180.0f;

    float minuteAngle =
        (minute * 6.0f + second * 0.1f)
        * PI / 180.0f;

    float hourAngle =
        (hour * 30.0f + minute * 0.5f)
        * PI / 180.0f;

    setColor(0.0f, 0.0f, 0.0f);
    glLineWidth(4.0f);

    drawLine(
        cx,
        cy,
        cx + 2.4f * sin(hourAngle),
        cy + 2.4f * cos(hourAngle)
    );

    glLineWidth(3.0f);

    drawLine(
        cx,
        cy,
        cx + 3.5f * sin(minuteAngle),
        cy + 3.5f * cos(minuteAngle)
    );

    setColor(1.0f, 0.0f, 0.0f);
    glLineWidth(1.5f);

    drawLine(
        cx,
        cy,
        cx + 4.2f * sin(secondAngle),
        cy + 4.2f * cos(secondAngle)
    );

    setColor(0.0f, 0.0f, 0.0f);

    drawFilledCircle(cx, cy, 0.4f, 20);
}

void drawDiamondFanBlades()
{
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(-5.2f, 2.3f);
        glVertex2f(-7.7f, 0.0f);
        glVertex2f(-5.2f, -2.3f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(5.2f, 2.3f);
        glVertex2f(7.7f, 0.0f);
        glVertex2f(5.2f, -2.3f);
    glEnd();
}

void drawFan()
{
    float fanX = 51.2f;
    float fanY = 46.7f;

    setColor(
        40.0f / 255.0f,
        40.0f / 255.0f,
        40.0f / 255.0f
    );

    glLineWidth(2.0f);

    drawLine(51.0f, 59.0f, 51.0f, 47.0f);
    drawLine(51.5f, 59.0f, 51.5f, 47.0f);

    glPushMatrix();

    glTranslatef(fanX, fanY, 0.0f);

    glRotatef(
        -fanAngle,
        0.0f,
        0.0f,
        1.0f
    );

    setColor(
        40.0f / 255.0f,
        40.0f / 255.0f,
        40.0f / 255.0f
    );

    drawDiamondFanBlades();

    drawFilledCircle(
        0.0f,
        0.0f,
        1.0f,
        30
    );

    glPopMatrix();
}

void drawThankYou()
{
    if (!blinkEnabled)
    {
        setColor(0.1f, 0.1f, 0.1f);

        drawText(
            28.0f,
            35.5f,
            "THANK YOU"
        );

        return;
    }

    if (textVisible)
    {
        setColor(1.0f, 0.0f, 0.0f);
    }
    else
    {
        setColor(1.0f, 1.0f, 1.0f);
    }

    drawText(
        28.0f,
        35.5f,
        "THANK YOU"
    );
}

void drawWallDecoration()
{
    setColor(0.0f, 0.0f, 0.0f);

    glLineWidth(1.5f);

    glBegin(GL_LINE_STRIP);
        glVertex2f(57.0f, 37.0f);
        glVertex2f(59.0f, 38.5f);
        glVertex2f(61.0f, 38.0f);
        glVertex2f(63.0f, 39.5f);
    glEnd();
}

void drawFloorDetails()
{
    setColor(0.3f, 0.3f, 0.3f);

    glLineWidth(1.0f);

    drawLine(
        20.0f,
        14.0f,
        3.0f,
        2.0f
    );

    drawLine(
        81.0f,
        14.0f,
        96.0f,
        2.0f
    );
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    drawRoom();
    drawFloorDetails();
    drawTable();
    drawPerson();
    drawDoor();
    drawClock();
    drawFan();
    drawThankYou();
    drawWallDecoration();

    glutSwapBuffers();
}

void update(int value)
{
    int currentTime =
        glutGet(GLUT_ELAPSED_TIME);

    float deltaTime =
        (currentTime - lastUpdateTime) / 1000.0f;

    lastUpdateTime = currentTime;

    if (fanOn)
    {
        fanAngle +=
            fanSpeed * deltaTime;

        if (fanAngle >= 360.0f)
        {
            fanAngle -= 360.0f;
        }
    }

    if (waving)
    {
        waveTime += deltaTime;
    }

    if (blinkEnabled)
    {
        blinkTimer += deltaTime;

        if (blinkTimer >= 0.5f)
        {
            textVisible = !textVisible;
            blinkTimer = 0.0f;
        }
    }
    else
    {
        textVisible = true;
    }

    glutPostRedisplay();

    glutTimerFunc(
        16,
        update,
        0
    );
}


void keyboard(
    unsigned char key,
    int x,
    int y)
{
    switch (key)
    {
        case 'f':
        case 'F':
            fanOn = !fanOn;
            break;

        case '+':
            fanSpeed += 60.0f;

            if (fanSpeed > 720.0f)
            {
                fanSpeed = 720.0f;
            }

            break;

        case '-':
            fanSpeed -= 60.0f;

            if (fanSpeed < 30.0f)
            {
                fanSpeed = 30.0f;
            }

            break;

        case 'w':
        case 'W':
            waving = !waving;
            break;

        case 'b':
        case 'B':
            blinkEnabled = !blinkEnabled;
            textVisible = true;
            break;

        case 'r':
        case 'R':
            fanAngle = 0.0f;
            fanSpeed = 180.0f;
            fanOn = true;

            waving = true;
            waveTime = 0.0f;

            blinkEnabled = true;
            textVisible = true;
            blinkTimer = 0.0f;

            break;

        case 27:
            exit(0);
            break;
    }

    glutPostRedisplay();
}

void init()
{

    glClearColor(
        248.0f / 255.0f,
        249.0f / 255.0f,
        250.0f / 255.0f,
        1.0f
    );

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(
        0.0,
        100.0,
        0.0,
        60.0
    );

    glMatrixMode(GL_MODELVIEW);
}

void reshape(int width, int height)
{
    glViewport(
        0,
        0,
        width,
        height
    );

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(
        0.0,
        100.0,
        0.0,
        60.0
    );

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(
        &argc,
        argv
    );

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB
    );

    glutInitWindowSize(
        1000,
        600
    );

    glutInitWindowPosition(
        100,
        100
    );

    glutCreateWindow(
        "Computer Graphics - Animated Thank You Room"
    );

    init();

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);

    lastUpdateTime =
        glutGet(GLUT_ELAPSED_TIME);

    glutTimerFunc(
        16,
        update,
        0
    );

    glutMainLoop();

    return 0;
}
*/
