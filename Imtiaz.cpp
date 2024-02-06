/*****************************************************************************
        FILE : submit.c (311170030 2023-2024 Assignment 1)
        NOTE : you have to implement functions in this file
*****************************************************************************/
/*****************************************************************************
        Student Information
        Student ID:2021521460116
        Student Name:Md Imtiaz Hossen Hawlader
*****************************************************************************/
#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

float squareAngle = 0.0f;
float triangleAngle = 0.0f;
float circleRadius = 0.2f;
float rectangleWidth = 0.4f;  // Width of the rectangle
float rectangleHeight = 0.2f; // Height of the rectangle
float hexPrismHeight = 0.4f;
float polygonSize = 0.2f;    // Size of the polygon
float pointSize = 5.0f;

int currentColor = 0; // 0: Red, 1: Green, 2: Blue, 3: Mixed, 4: White

GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat material_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat material_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat material_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat material_shininess[] = { 100.0f };

bool animationPaused = false;

void setColor(int color) {
    switch (color) {
    case 0:
        glColor3f(1.0f, 0.0f, 0.0f); // Red
        break;
    case 1:
        glColor3f(0.0f, 1.0f, 0.0f); // Green
        break;
    case 2:
        glColor3f(0.0f, 0.0f, 1.0f); // Blue
        break;
    case 3:
        glColor3f(1.0f, 0.5f, 0.0f); // Orange for polygon
        break;
    case 4:
        glColor3f(0.0f, 0.5f, 1.0f); // Light Blue for polygon
        break;
    case 5:
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow for ball 1
        break;
    case 6:
        glColor3f(1.0f, 0.0f, 1.0f); // Magenta for ball 2
        break;
    }
}

void drawPolygon(float size, int sides) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < sides; i++) {
        float angle = 2.0f * static_cast<float>(M_PI) * i / sides;
        glVertex2f(size * cos(angle), size * sin(angle));
    }
    glEnd();
}

void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
}

float squareScaleX = 1.0f;
float squareScaleY = 1.0f;
float triangleScaleX = 1.0f;
float triangleScaleY = 1.0f;
float circleScaleX = 1.0f;
float circleScaleY = 1.0f;
float rectangleScaleX = 1.0f;
float rectangleScaleY = 1.0f;
float polygonScaleX = 1.0f;
float polygonScaleY = 1.0f;

float animationDirection = 1.0f; // 1: Move right, -1: Move left
float animationSpeed = 0.005f;

float circleY = 0.0f;
float circleSpeedY = 0.01f;

float ball1Y = 0.0f;   // Y position of the first bouncing ball
float ball2Y = 0.0f;   // Y position of the second bouncing ball
float ball1SpeedY = 0.01f; // Vertical speed of the first bouncing ball
float ball2SpeedY = 0.0075f; // Vertical speed of the second bouncing ball
float middlePrismX = 0.0f; // X position of the middle prism
float middlePrismSpeedX = 0.01f; // Horizontal speed of the middle prism
bool middlePrismMovingRight = true;
void updateAnimation() {
    if (!animationPaused) {
        // Update the position of the primitives based on animationDirection
        if (animationDirection == 1.0f) {
            squareScaleX += animationSpeed;
            squareScaleY += animationSpeed;
            triangleScaleX += animationSpeed;
            triangleScaleY += animationSpeed;
            circleScaleX += animationSpeed;
            circleScaleY += animationSpeed;
            rectangleScaleX += animationSpeed;
            rectangleScaleY += animationSpeed;
            polygonScaleX += animationSpeed;
            polygonScaleY += animationSpeed;
        }
        else {
            squareScaleX -= animationSpeed;
            squareScaleY -= animationSpeed;
            triangleScaleX -= animationSpeed;
            triangleScaleY -= animationSpeed;
            circleScaleX -= animationSpeed;
            circleScaleY -= animationSpeed;
            rectangleScaleX -= animationSpeed;
            rectangleScaleY -= animationSpeed;
            polygonScaleX -= animationSpeed;
            polygonScaleY -= animationSpeed;
        }

        // Check for animation direction change
        if (squareScaleX >= 1.0f && animationDirection == 1.0f) {
            animationDirection = -1.0f; // Change direction to left
        }
        else if (squareScaleX <= 0.1f && animationDirection == -1.0f) {
            animationDirection = 1.0f; // Change direction to right
        }

        // Update the circle's vertical position for the bouncing animation
        circleY += circleSpeedY;
        if (circleY + circleRadius >= 1.0f || circleY - circleRadius <= -1.0f) {
            circleSpeedY = -circleSpeedY;
        }

        // Ensure the ball stays within the window boundaries
        if (circleY + circleRadius > 1.0f) {
            circleY = 1.0f - circleRadius;
        }
        else if (circleY - circleRadius < -1.0f) {
            circleY = -1.0f + circleRadius;
        }

        // Update the vertical position of the first bouncing ball
        ball1Y += ball1SpeedY;
        if (ball1Y + circleRadius >= 1.0f || ball1Y - circleRadius <= -1.0f) {
            ball1SpeedY = -ball1SpeedY;
        }

        // Update the vertical position of the second bouncing ball
        ball2Y += ball2SpeedY;
        if (ball2Y + circleRadius >= 1.0f || ball2Y - circleRadius <= -1.0f) {
            ball2SpeedY = -ball2SpeedY;
        }
    }
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    updateAnimation(); // Update the animation state

    // Draw a square with scaling
    glPushMatrix();
    glTranslatef(-0.5f, 0.5f, 0.0f);
    glRotatef(squareAngle, 0.0f, 0.0f, 1.0f);
    glScalef(squareScaleX, squareScaleY, 1.0f); // Apply scaling
    setColor(currentColor);
    glutSolidCube(0.2);
    glPopMatrix();

    // Draw a triangle with scaling
    glPushMatrix();
    glTranslatef(0.5f, 0.5f, 0.0f);
    glRotatef(triangleAngle, 0.0f, 0.0f, 1.0f);
    glScalef(triangleScaleX, triangleScaleY, 1.0f); // Apply scaling
    setColor(currentColor + 1); // Use the next color (Green)
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.2f);
    glVertex2f(-0.2f, -0.2f);
    glVertex2f(0.2f, -0.2f);
    glEnd();
    glPopMatrix();

    // Draw a circle with scaling
    glPushMatrix();
    glTranslatef(-0.5f, -0.5f, 0.0f); // Fixed position at the bottom-left corner aligned with the rectangle
    glScalef(circleScaleX, circleScaleY, 1.0f); // Apply scaling
    setColor(currentColor + 2); // Use the next color (Blue)
    glutSolidSphere(circleRadius, 100, 100);
    glPopMatrix();

    // Draw a rectangle with scaling
    glPushMatrix();
    glTranslatef(0.5f, -0.5f, 0.0f);
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glScalef(rectangleScaleX, rectangleScaleY, 1.0f); // Apply scaling
    setColor(currentColor + 3); // Use the next color (Mixed)
    glBegin(GL_POLYGON);
    glVertex2f(-rectangleWidth / 2, -rectangleHeight / 2);
    glVertex2f(rectangleWidth / 2, -rectangleHeight / 2);
    glVertex2f(rectangleWidth / 2, rectangleHeight / 2);
    glVertex2f(-rectangleWidth / 2, rectangleHeight / 2);
    glEnd();
    glPopMatrix();

    // Draw a polygon with scaling
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(polygonScaleX, polygonScaleY, 1.0f); // Apply scaling
    setColor(currentColor + 4); // Use the next color (White)
    drawPolygon(polygonSize, 6); // A hexagon
    glPopMatrix();
    // Update the X position of the middle prism for animation
    if (middlePrismMovingRight) {
        middlePrismX += middlePrismSpeedX;
        if (middlePrismX >= 0.4f) {
            middlePrismX = 0.4f;
            middlePrismMovingRight = false; // Change direction to left
        }
    }
    else {
        middlePrismX -= middlePrismSpeedX;
        if (middlePrismX <= -0.4f) {
            middlePrismX = -0.4f;
            middlePrismMovingRight = true; // Change direction to right
        }
    }

    // Draw the first bouncing ball with scaling
    glPushMatrix();
    glTranslatef(0.0f, ball1Y, 0.0f); // Adjust Y position for bouncing
    glScalef(circleScaleX, circleScaleY, 1.0f); // Apply scaling
    setColor(currentColor + 5); // Use a new color
    glutSolidSphere(circleRadius, 100, 100);
    glPopMatrix();

    // Draw the second bouncing ball with scaling
    glPushMatrix();
    glTranslatef(0.0f, ball2Y, 0.0f); // Adjust Y position for bouncing
    glScalef(circleScaleX, circleScaleY, 1.0f); // Apply scaling
    setColor(currentColor + 6); // Use another new color
    glutSolidSphere(circleRadius, 100, 100);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height) {
        gluOrtho2D(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f);
    }
    else {
        gluOrtho2D(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect);
    }
}

void timer(int value) {
    if (!animationPaused) {
        glutPostRedisplay();
        glutTimerFunc(1000 / 60, timer, 0); // 60 FPS
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: // ESC key
        exit(0);
        break;
    case 'q':
        squareAngle += 10.0f;
        break;
    case 'a':
        squareAngle -= 10.0f;
        break;
    case 'w':
        triangleAngle += 10.0f;
        break;
    case 's':
        triangleAngle -= 10.0f;
        break;
    case 'e':
        circleRadius += 0.02f;
        break;
    case 'd':
        circleRadius -= 0.02f;
        break;
    case 'r':
        rectangleWidth += 0.1f;
        break;
    case 'f':
        rectangleWidth -= 0.1f;
        if (rectangleWidth < 0.1f) rectangleWidth = 0.1f;
        break;
    case 't':
        polygonSize += 0.02f; // Increase the size of the polygon
        break;
    case 'g':
        polygonSize -= 0.02f; // Decrease the size of the polygon
        if (polygonSize < 0.02f) polygonSize = 0.02f;
        break;
    case '1':
        currentColor = 0; // Red
        break;
    case '2':
        currentColor = 1; // Green
        break;
    case '3':
        currentColor = 2; // Blue
        break;
    case '4':
        currentColor = 3; // Mixed
        break;
    case '5':
        currentColor = 4; // White
        break;
    case 'p':
        animationPaused = !animationPaused; // Toggle animation state
        if (!animationPaused) {
            glutTimerFunc(1000 / 60, timer, 0); // Restart the timer for animation if not paused
        }
        break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Scene");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0); // Start the timer for animation

    glutMainLoop();
    return 0;
}
