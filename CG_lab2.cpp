#include <GL/glut.h>

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void drawHexagon() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    
    // Triangle 1
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex2f(0.0, 0.0);
    glVertex2f(0.5, 0.8);
    glVertex2f(1.0, 0.0);

    // Triangle 2
    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex2f(0.0, 0.0);
    glVertex2f(1.0, 0.0);
    glVertex2f(0.5, -0.8);

    // Triangle 3
    glColor3f(0.0, 0.0, 1.0); // Blue
    glVertex2f(0.0, 0.0);
    glVertex2f(0.5, -0.8);
    glVertex2f(-0.5, -0.8);

    // Triangle 4
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glVertex2f(0.0, 0.0);
    glVertex2f(-0.5, -0.8);
    glVertex2f(-1.0, 0.0);

    // Triangle 5
    glColor3f(1.0, 0.0, 1.0); // Magenta
    glVertex2f(0.0, 0.0);
    glVertex2f(-1.0, 0.0);
    glVertex2f(-0.5, 0.8);

    // Triangle 6
    glColor3f(0.0, 1.0, 1.0); // Cyan
    glVertex2f(0.0, 0.0);
    glVertex2f(-0.5, 0.8);
    glVertex2f(0.5, 0.8);

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(350, 350);
    glutCreateWindow("Camasura_Lab2");
    init();
    glutDisplayFunc(drawHexagon);
    glutMainLoop();
    return 0;
}


