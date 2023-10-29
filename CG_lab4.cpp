#include <GL/glut.h>
#include <cstdlib>

// setting up initial colors and positions
float faceColor[3] = {0.17f, 0.26f, 0.39f};
float leftEyeColor[3] = {1.0f, 1.0f, 1.0f};
float rightEyeColor[3] = {1.0f, 1.0f, 1.0f};
float facePosition[2] = {0.0f, 0.0f};

// define vertex arrays for the face, eyes, and smile
float faceVertices[8];
float leftEyeVertices[8];
float rightEyeVertices[8];
float smileVertices[4];

void updateVertices() {
    // face
    faceVertices[0] = -0.5 + facePosition[0]; faceVertices[1] = -0.5 + facePosition[1];
    faceVertices[2] = -0.5 + facePosition[0]; faceVertices[3] =  0.5 + facePosition[1];
    faceVertices[4] =  0.5 + facePosition[0]; faceVertices[5] =  0.5 + facePosition[1];
    faceVertices[6] =  0.5 + facePosition[0]; faceVertices[7] = -0.5 + facePosition[1];

    // left eye
    leftEyeVertices[0] = -0.3 + facePosition[0]; leftEyeVertices[1] = 0.1 + facePosition[1];
    leftEyeVertices[2] = -0.3 + facePosition[0]; leftEyeVertices[3] = 0.2 + facePosition[1];
    leftEyeVertices[4] = -0.2 + facePosition[0]; leftEyeVertices[5] = 0.2 + facePosition[1];
    leftEyeVertices[6] = -0.2 + facePosition[0]; leftEyeVertices[7] = 0.1 + facePosition[1];

    // right eye
    rightEyeVertices[0] = 0.3 + facePosition[0]; rightEyeVertices[1] = 0.1 + facePosition[1];
    rightEyeVertices[2] = 0.3 + facePosition[0]; rightEyeVertices[3] = 0.2 + facePosition[1];
    rightEyeVertices[4] = 0.2 + facePosition[0]; rightEyeVertices[5] = 0.2 + facePosition[1];
    rightEyeVertices[6] = 0.2 + facePosition[0]; rightEyeVertices[7] = 0.1 + facePosition[1];

    // smile
    smileVertices[0] = -0.2 + facePosition[0]; smileVertices[1] = -0.15 + facePosition[1];
    smileVertices[2] =  0.2 + facePosition[0]; smileVertices[3] = -0.15 + facePosition[1];
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    updateVertices();

    // draw face using vertex array
    glColor3fv(faceColor);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, faceVertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    // draw left eye using vertex array
    glColor3fv(leftEyeColor);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, leftEyeVertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    // draw right eye using vertex array
    glColor3fv(rightEyeColor);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, rightEyeVertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    // draw smile using vertex array
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(4);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, smileVertices);
    glDrawArrays(GL_LINES, 0, 2);
    glDisableClientState(GL_VERTEX_ARRAY);

    glFlush();
}

void onKeyPress(unsigned char key, int x, int y) {
    switch (key) {
        case 'A':
        case 'a':
            facePosition[0] -= 0.05f;
            break;
        case 'S':
        case 's':
            facePosition[1] -= 0.05f;
            break;
        case 'D':
        case 'd':
            facePosition[0] += 0.05f;
            break;
        case 27: // esc
            exit(0);
            break;
        case 'W':
        case 'w':
            facePosition[1] += 0.05f;
            break;
    }
    glutPostRedisplay();
}

void onSpecialKeyPress(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            facePosition[0] -= 0.05f;
            break;
        case GLUT_KEY_DOWN:
            facePosition[1] -= 0.05f;
            break;
        case GLUT_KEY_RIGHT:
            facePosition[0] += 0.05f;
            break;
        case GLUT_KEY_UP:
            facePosition[1] += 0.05f;
            break;
    }
    glutPostRedisplay();
}

void onMouseClick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            // change left eye color
            leftEyeColor[0] = rand() / (float)RAND_MAX;
            leftEyeColor[1] = rand() / (float)RAND_MAX;
            leftEyeColor[2] = rand() / (float)RAND_MAX;
        } else if (button == GLUT_RIGHT_BUTTON) {
            // change right eye color
            rightEyeColor[0] = rand() / (float)RAND_MAX;
            rightEyeColor[1] = rand() / (float)RAND_MAX;
            rightEyeColor[2] = rand() / (float)RAND_MAX;
        }
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Camasura_Lab4");
    glutDisplayFunc(display);
    glutKeyboardFunc(onKeyPress);
    glutSpecialFunc(onSpecialKeyPress); // added for arrow keys
    glutMouseFunc(onMouseClick);
    glutMainLoop();
    return 0;
}
