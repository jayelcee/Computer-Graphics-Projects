#include <GL/glut.h>
#include <cstdlib>

// setting up initial colors and positions
float faceColor[3] = {0.17f, 0.26f, 0.39f}; 
float leftEyeColor[3] = {1.0f, 1.0f, 1.0f}; 
float rightEyeColor[3] = {1.0f, 1.0f, 1.0f}; 
float facePosition[2] = {0.0f, 0.0f}; 

void display(){
glClear(GL_COLOR_BUFFER_BIT);

// draw face
glColor3fv(faceColor);
glBegin(GL_POLYGON);
glVertex2f(-0.5 + facePosition[0], -0.5 + facePosition[1]);
glVertex2f(-0.5 + facePosition[0], 0.5 + facePosition[1]);
glVertex2f(0.5 + facePosition[0], 0.5 + facePosition[1]);
glVertex2f(0.5 + facePosition[0], -0.5 + facePosition[1]);
glEnd();

// draw left eye
glColor3fv(leftEyeColor);
glBegin(GL_POLYGON);
glVertex2f(-0.3 + facePosition[0], 0.1 + facePosition[1]);
glVertex2f(-0.3 + facePosition[0], 0.2 + facePosition[1]);
glVertex2f(-0.2 + facePosition[0], 0.2 + facePosition[1]);
glVertex2f(-0.2 + facePosition[0], 0.1 + facePosition[1]);
glEnd();

// draw right eye
glColor3fv(rightEyeColor);
glBegin(GL_POLYGON);
glVertex2f(0.3 + facePosition[0], 0.1 + facePosition[1]);
glVertex2f(0.3 + facePosition[0], 0.2 + facePosition[1]);
glVertex2f(0.2 + facePosition[0], 0.2 + facePosition[1]);
glVertex2f(0.2 + facePosition[0], 0.1 + facePosition[1]);
glEnd();

// draw smile
glColor3f(0.0f, 0.0f, 0.0f); 
glLineWidth(4);
glBegin(GL_LINES);
glVertex2f(-0.2 + facePosition[0], -0.15 + facePosition[1]);
glVertex2f(0.2 + facePosition[0], -0.15 + facePosition[1]);
glEnd();

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
	case 27: // ESC
	exit(0);
	break;
	case 'W':
	case 'w':
	facePosition[1] += 0.05f;
	break;
}
glutPostRedisplay();
}

void onMouseClick(int button, int state, int x, int y) {
if(state == GLUT_DOWN) {
if(button == GLUT_LEFT_BUTTON) {
// change left eye color
leftEyeColor[0] = rand() / (float)RAND_MAX;
leftEyeColor[1] = rand() / (float)RAND_MAX;
leftEyeColor[2] = rand() / (float)RAND_MAX;
} else if(button == GLUT_RIGHT_BUTTON) {
// change right eye color
rightEyeColor[0] = rand() / (float)RAND_MAX;
rightEyeColor[1] = rand() / (float)RAND_MAX;
rightEyeColor[2] = rand() / (float)RAND_MAX;
}
glutPostRedisplay();
}
}

int main(int argc, char** argv){
glutInit(&argc, argv);
glutCreateWindow("Camasura_Lab3");
glutDisplayFunc(display);
glutKeyboardFunc(onKeyPress);
glutMouseFunc(onMouseClick);
glutMainLoop();
return 0;
}
