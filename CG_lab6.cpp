/*  Jasmine Camasura - CS0045 (TN32)
    OpenGL program displaying an octahedron with spotlights and camera controls. */

#include <GL/glut.h>
#include <cmath>

// Camera parameters
GLfloat cameraPosition[] = { 0.0, 0.0, 5.0 };
GLfloat cameraRotation[] = { 0.0, 0.0, 0.0 };
GLfloat rotationSpeed = 2.0;

// Spotlight parameters
GLfloat spotlightPositions[3][4] = { {1.0, 1.0, 1.0, 1.0}, {-1.0, -1.0, 1.0, 1.0}, {1.0, -1.0, -1.0, 1.0} };
GLfloat spotlightDirections[3][3] = { {-1.0, -1.0, -1.0}, {1.0, 1.0, -1.0}, {-1.0, 1.0, 1.0} };
GLfloat spotlightColors[3][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} }; // Red, Green, Blue
GLfloat spotlightIntensity = 1.0;
GLfloat spotlightRadius = 30.0;

// Material color (light gray)
GLfloat materialColor[] = { 0.8, 0.8, 0.8, 1.0 };

// Ambient light (slightly darker shade)
GLfloat ambientColor[] = { 0.7, 0.7, 0.7, 1.0 };

// Smoother camera movement variables
GLfloat cameraSpeed = 0.1;
GLfloat cameraVelocity[] = { 0.0, 0.0, 0.0 };

// Window size
int windowWidth = 800;
int windowHeight = 600;

// Octahedron rotation variables
GLfloat octahedronRotationSpeed = 1.0;

// Function prototypes
void init();
void reshape(int w, int h);
void display();
void updateCamera();
void keyboard(unsigned char key, int x, int y);
void releaseKey(unsigned char key, int x, int y);
void idle();

int main(int argc, char** argv) {
    // Initialize GLUT and create the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Camasura_Lab6");

    // Register callback functions
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(releaseKey);
    glutIdleFunc(idle);

    // Initialize OpenGL settings
    init();

    // Enter the GLUT main loop
    glutMainLoop();

    return 0;
}

// Initialize OpenGL settings
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set material color
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);

    // Set ambient light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    // Initialize spotlights
    for (int i = 0; i < 3; ++i) {
        glEnable(GL_LIGHT1 + i);
        glLightfv(GL_LIGHT1 + i, GL_POSITION, spotlightPositions[i]);
        glLightfv(GL_LIGHT1 + i, GL_SPOT_DIRECTION, spotlightDirections[i]);
        glLightfv(GL_LIGHT1 + i, GL_DIFFUSE, spotlightColors[i]);
        glLightf(GL_LIGHT1 + i, GL_SPOT_CUTOFF, 45.0);
        glLightf(GL_LIGHT1 + i, GL_SPOT_EXPONENT, 2.0);
        glLightf(GL_LIGHT1 + i, GL_CONSTANT_ATTENUATION, 1.0);
        glLightf(GL_LIGHT1 + i, GL_LINEAR_ATTENUATION, 0.05);
        glLightf(GL_LIGHT1 + i, GL_QUADRATIC_ATTENUATION, 0.001);
    }
}

// Handle window resizing
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Display callback function
void display() {
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the camera
    glLoadIdentity();
    gluLookAt(cameraPosition[0], cameraPosition[1], cameraPosition[2],
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);

    // Apply rotation to the camera
    glRotatef(cameraRotation[0], 1.0, 0.0, 0.0);
    glRotatef(cameraRotation[1], 0.0, 1.0, 0.0);
    glRotatef(cameraRotation[2], 0.0, 0.0, 1.0);

    // Render the octahedron
    glutSolidOctahedron();

    // Swap the front and back buffers
    glutSwapBuffers();
}

// Update camera position based on user input
void updateCamera() {
    for (int i = 0; i < 3; ++i) {
        cameraPosition[i] += cameraVelocity[i];
    }
}

// Handle keyboard input for camera movement
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        cameraVelocity[2] = -cameraSpeed;
        break;
    case 's':
        cameraVelocity[2] = cameraSpeed;
        break;
    case 'a':
        cameraVelocity[0] = -cameraSpeed;
        break;
    case 'd':
        cameraVelocity[0] = cameraSpeed;
        break;
    case 'q':
        cameraVelocity[1] = -cameraSpeed;
        break;
    case 'e':
        cameraVelocity[1] = cameraSpeed;
        break;
    case 27: // Escape key
        exit(0);
        break;
    }

    // Trigger a display update
    glutPostRedisplay();
}

// Handle key release events to stop camera movement
void releaseKey(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
    case 's':
        // Stop forward/backward movement
        cameraVelocity[2] = 0.0;
        break;
    case 'a':
    case 'd':
        // Stop left/right movement
        cameraVelocity[0] = 0.0;
        break;
    case 'q':
    case 'e':
        // Stop up/down movement
        cameraVelocity[1] = 0.0;
        break;
    }

    // Trigger a display update
    glutPostRedisplay();
}

// Idle callback function for continuous rotation
void idle() {
    // Continuous horizontal rotation of the octahedron
    cameraRotation[1] += octahedronRotationSpeed;

    // Update camera position
    updateCamera();

    // Trigger a display update
    glutPostRedisplay();
}
