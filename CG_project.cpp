/*
    [CS0045] Computer Graphics and Visual Computing
    [LONG QUIZ #2] and Project
    
    Camasura, Jasmine
    Quirante, Shawn Aaron

    Requirements Completed
    1. FullScreen Mode: The program starts in fullscreen mode using glutFullScreen().
    2. Different Objects with Different Colors: Multiple objects are drawn with distinct colors using glColor3f() and glColor4f().
    3. Use of at Least Three OpenGL Primitives: The code utilizes various OpenGL primitives such as GL_POLYGON, GL_TRIANGLE_FAN, GL_LINES, and GL_POINTS.
    4. Uses VertexArrays and VBOs: Vertex Buffer Objects (VBOs) are created and used for storing vertex data. Vertex arrays are enabled and used for 
       drawing with glEnableClientState(GL_VERTEX_ARRAY) and glVertexPointer().
    5. Transformation of Main Objects
       Earth (Scaling Object): This object is scaled using the mouse's scroll wheel in the updateScalingObject() function. 
                               The glScalef() function is used here to apply scaling transformations based on scroll wheel input.
       Moon (Rotation Object): This object is rotated upon mouse click, implemented in the drawRotatingObject() and rotateObjects() 
                               functions. The glRotatef() function is used to apply the rotation transformation. When the left mouse button 
                               is pressed and held, the moon starts rotating, and it stops when the button is released.
       AU Character (Movement Object): The Among Us character is moved using a timed interval, implemented in the updateMovingObject() function, 
                               where the glTranslatef() function is used to translate the object's position over time, creating the movement effect.
                               WASD keys are also implemented to play around the moving object (red au character).
    6. Additional Features (Objects that uses the functions or show an illusion of the following transformations)
       Translation | Movement | Positioning : Moon, Earth, Among Us Character, Stars, Sun
       Rotation : Moon, Among Us Character, Earth, Sun
       Scaling : Earth
*/

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <ctime>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

// Global Variables
GLuint rotatingObjectVBO, movingObjectVBO, constantlyMovingObjectVBO, scalingObjectVBO, starVBO;
GLfloat rotationAngle = 0.0f, rotationAngleSun = 0.0f, rotationAngleMovingObject = 0.0f, rotationAngleConstantlyMovingObject = 0.0f, rotationAngleScalingObject = 0.0f;
GLfloat translationX = 0.0f, translationcmX = 0.0f, scalingFactor = 2.5f, movingObjectX = 0.0f, movingObjectY = 0.0f;
bool isLeftMouseButtonDown = false, keyWPressed = false, keySPressed = false, keyAPressed = false, keyDPressed = false;
const GLfloat movementSpeed = 0.02f;
clock_t startTime, startcmTime;
const double movementDistance = 4.0, movementcmDistance = 3.8;
const int numberOfStars = 1000;
GLfloat starTranslationX = 0.0f, starTranslationY = 0.0f;
const GLfloat starSpeedX = 0.002f, starSpeedY = 0.002f;

// Function Prototypes 
void initRotatingObject(GLuint& vbo);
void initMovingObject(GLuint& vbo);
void initScalingObject(GLuint& vbo);
void initStars();
void initConstantlyMovingObject(GLuint& vbo);
void display();
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void reshape(int width, int height);
void updateIdleObjects();
void updatePosition(int value);

// Main Function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
    glutCreateWindow("Camasura - Quirante CG Project");
    glutFullScreen();
    glewInit();

    initRotatingObject(rotatingObjectVBO);
    initMovingObject(movingObjectVBO);
    initScalingObject(scalingObjectVBO);
    initStars();
    initConstantlyMovingObject(constantlyMovingObjectVBO);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutTimerFunc(0, updatePosition, 0);

    startTime = clock();
    startcmTime = clock();

    GLenum err = glewInit();
    if (err == GLEW_OK) {
        glutIdleFunc(updateIdleObjects);
        glutMainLoop();
    }

    return 0;
}

// Initialization Functions

void initRotatingObject(GLuint& vbo) {
    float yOffset = 0.75;
    GLfloat objectVertices[] = {
        -0.12f, 0.02f + yOffset, 0.0f,
        -0.08f, 0.08f + yOffset, 0.0f,
        -0.02f, 0.11f + yOffset, 0.0f,
         0.06f, 0.11f + yOffset, 0.0f,
         0.12f, 0.08f + yOffset, 0.0f,
         0.16f, 0.02f + yOffset, 0.0f,
         0.16f, -0.06f + yOffset, 0.0f,
         0.12f, -0.12f + yOffset, 0.0f,
         0.06f, -0.15f + yOffset, 0.0f,
         -0.02f, -0.15f + yOffset, 0.0f,
         -0.08f, -0.12f + yOffset, 0.0f,
         -0.12f, -0.06f + yOffset, 0.0f,
         -0.12f, 0.02f + yOffset, 0.0f,

         0.03f, -0.03f + yOffset, 0.0f,
         0.04f, 0.0f + yOffset, 0.0f,
         0.06f, 0.03f + yOffset, 0.0f,
         0.09f, 0.04f + yOffset, 0.0f,
         0.11f, 0.04f + yOffset, 0.0f,
         0.16f, 0.02f + yOffset, 0.0f,
         0.16f, -0.03f + yOffset, 0.0f,
         0.15f, -0.06f + yOffset, 0.0f,
         0.13f, -0.08f + yOffset, 0.0f,
         0.10f, -0.09f + yOffset, 0.0f,
         0.07f, -0.08f + yOffset, 0.0f,
         0.04f, -0.06f + yOffset, 0.0f,
         0.03f, -0.03f + yOffset, 0.0f,

         -0.04f, -0.05f + yOffset, 0.0f,
         -0.02f, -0.02f + yOffset, 0.0f,
         0.0f, 0.0f + yOffset, 0.0f,
         0.02f, 0.01f + yOffset, 0.0f,
         0.04f, 0.02f + yOffset, 0.0f,
         0.053f, 0.02f + yOffset, 0.0f,
         0.04f, 0.0f + yOffset, 0.0f,
         0.04f, 0.0f + yOffset, 0.0f,
         0.03f, -0.03f + yOffset, 0.0f,
         0.04f, -0.06f + yOffset, 0.0f,
         0.07f, -0.08f + yOffset, 0.0f,
         0.10f, -0.09f + yOffset, 0.0f,
         0.08f, -0.10f + yOffset, 0.0f,
         0.05f, -0.09f + yOffset, 0.0f,
         0.04f, -0.10f + yOffset, 0.0f,
         0.02f, -0.085f + yOffset, 0.0f,
         -0.01f, -0.08f + yOffset, 0.0f,
         -0.04f, -0.06f + yOffset, 0.0f,
         -0.04f, -0.05f + yOffset, 0.0f,

         -0.02f, -0.03f + yOffset, 0.0f,
         -0.01f, -0.02f + yOffset, 0.0f,
         0.0f, -0.02f + yOffset, 0.0f,
         0.02f, -0.015f + yOffset, 0.0f,
         0.04f, 0.0f + yOffset, 0.0f,
         0.03f, -0.03f + yOffset, 0.0f,
         0.04f, -0.06f + yOffset, 0.0f,
         0.07f, -0.08f + yOffset, 0.0f,
         0.03f, -0.07f + yOffset, 0.0f,
         0.0f, -0.06f + yOffset, 0.0f,
         -0.01f, -0.05f + yOffset, 0.0f,
         -0.02f, -0.03f + yOffset, 0.0f,

         0.01f, -0.03f + yOffset, 0.0f,
         0.033f, -0.02f + yOffset, 0.0f,
         0.03f, -0.03f + yOffset, 0.0f,
         0.04f, -0.06f + yOffset, 0.0f,
         0.03f, -0.06f + yOffset, 0.0f,
         0.02f, -0.05f + yOffset, 0.0f,
         0.01f, -0.03f + yOffset, 0.0f,

         -0.12f, 0.02f + yOffset, 0.0f,
         -0.08f, 0.08f + yOffset, 0.0f,
         -0.02f, 0.11f + yOffset, 0.0f,
         -0.025f, 0.07f + yOffset, 0.0f,
         -0.025f, 0.055f + yOffset, 0.0f,
         -0.02f, 0.055f + yOffset, 0.0f,
         -0.02f, 0.04f + yOffset, 0.0f,
         -0.04f, 0.04f + yOffset, 0.0f,
         -0.05f, 0.035f + yOffset, 0.0f,
         -0.08f, 0.02f + yOffset, 0.0f,
         -0.07f, -0.045f + yOffset, 0.0f,
         -0.07f, -0.06f + yOffset, 0.0f,
         -0.08f, -0.06f + yOffset, 0.0f,
         -0.11f, -0.04f + yOffset, 0.0f,
         -0.12f, -0.04f + yOffset, 0.0f,
         -0.12f, 0.02f + yOffset, 0.0f,

        -0.07f, -0.06f + yOffset, 0.0f,
        -0.07f, -0.045f + yOffset, 0.0f,
        -0.08f, 0.02f + yOffset, 0.0f,
        -0.05f, 0.035f + yOffset, 0.0f,
        -0.04f, 0.04f + yOffset, 0.0f,
        -0.04f, 0.04f + yOffset, 0.0f,
        -0.02f, 0.04f + yOffset, 0.0f,
        -0.02f, 0.055f + yOffset, 0.0f,
        -0.025f, 0.07f + yOffset, 0.0f,
        -0.02f, 0.11f + yOffset, 0.0f,
        -0.01f, 0.11f + yOffset, 0.0f,
        -0.015f, 0.07f + yOffset, 0.0f,
        -0.01f, 0.055f + yOffset, 0.0f,
        -0.01f, 0.04f + yOffset, 0.0f,
        -0.03f, 0.04f + yOffset, 0.0f,
        -0.03f, 0.04f + yOffset, 0.0f,
        -0.04f, 0.035f + yOffset, 0.0f,
        -0.07f, 0.02f + yOffset, 0.0f,
        -0.06f, -0.045f + yOffset, 0.0f,
        -0.06f, -0.06f + yOffset, 0.0f,
        -0.07f, -0.06f + yOffset, 0.0f
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(objectVertices), objectVertices, GL_STATIC_DRAW);
}

void initMovingObject(GLuint& vbo) {
    float xOffset = -0.05;
    GLfloat objectVertices[] = {
        -0.09f + xOffset, 0.11f, 0.0f,
        -0.07f + xOffset, -0.02f, 0.0f,
        -0.04f + xOffset, -0.06f, 0.0f,
        0.02f + xOffset, -0.08f, 0.0f,
        0.08f + xOffset, -0.06f, 0.0f,
        0.11f + xOffset, -0.03f, 0.0f,
        0.11f + xOffset, -0.15f, 0.0f,
        0.10f + xOffset, -0.17f, 0.0f,
        0.05f + xOffset, -0.17f, 0.0f,
        0.03f + xOffset, -0.15f, 0.0f,
        0.03f + xOffset, -0.11f, 0.0f,
        -0.01f + xOffset, -0.11f, 0.0f,
        -0.01f + xOffset, -0.15f, 0.0f,
        -0.02f + xOffset, -0.17f, 0.0f,
        -0.07f + xOffset, -0.17f, 0.0f,
        -0.09f + xOffset, -0.15f, 0.0f,
        -0.09f + xOffset, 0.11f, 0.0f,

        -0.09f + xOffset, 0.11f, 0.0f,
        -0.07f + xOffset, 0.14f, 0.0f,
        -0.04f + xOffset, 0.16f, 0.0f,
        0.01f + xOffset, 0.17f, 0.0f,
        0.08f + xOffset, 0.15f, 0.0f,
        0.11f + xOffset, 0.09f, 0.0f,
        0.11f + xOffset, -0.03f, 0.0f,
        0.08f + xOffset, -0.06f, 0.0f,
        0.02f + xOffset, -0.08f, 0.0f,
        -0.04f + xOffset, -0.06f, 0.0f,
        -0.07f + xOffset, -0.02f, 0.0f,
        -0.09f + xOffset, 0.11f, 0.0f,

        -0.13f + xOffset, 0.04f, 0.0f,
        -0.09f + xOffset, 0.04f, 0.0f,
        -0.09f + xOffset, -0.10f, 0.0f,
        -0.12f + xOffset, -0.10f, 0.0f,
        -0.13f + xOffset, -0.07f, 0.0f,
        -0.13f + xOffset, 0.04f, 0.0f,

        -0.13f + xOffset, 0.05f, 0.0f,
        -0.12f + xOffset, 0.07f, 0.0f,
        -0.09f + xOffset, 0.07f, 0.0f,
        -0.09f + xOffset, 0.04f, 0.0f,
        -0.13f + xOffset, 0.04f, 0.0f,
        -0.13f + xOffset, 0.05f, 0.0f,

        -0.02f + xOffset, 0.09f, 0.0f,
        0.0f + xOffset, 0.11f, 0.0f,
        0.10f + xOffset, 0.11f, 0.0f,
        0.12f + xOffset, 0.09f, 0.0f,
        0.12f + xOffset, 0.04f, 0.0f,
        0.10f + xOffset, 0.02f, 0.0f,
        0.0f + xOffset, 0.02f, 0.0f,
        -0.02f + xOffset, 0.04f, 0.0f,
        -0.02f + xOffset, 0.09f, 0.0f,

        0.05f + xOffset, 0.09f, 0.0f,
        0.06f + xOffset, 0.10f, 0.0f,
        0.09f + xOffset, 0.10f, 0.0f,
        0.10f + xOffset, 0.09f, 0.0f,
        0.10f + xOffset, 0.08f, 0.0f,
        0.09f + xOffset, 0.07f, 0.0f,
        0.06f + xOffset, 0.07f, 0.0f,
        0.05f + xOffset, 0.08f, 0.0f,
        0.05f + xOffset, 0.09f, 0.0f
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(objectVertices), objectVertices, GL_STATIC_DRAW);
}

void initScalingObject(GLuint& vbo) {
    const int numSegments = 50;  
    const float radius = 0.1f;   

    // Calculate vertices for a circle
    GLfloat objectVertices[numSegments * 3];
    for (int i = 0; i < numSegments; ++i) {
        float angle = 2.0f * M_PI * i / numSegments;
        objectVertices[i * 3] = radius * cos(angle);
        objectVertices[i * 3 + 1] = radius * sin(angle);
        objectVertices[i * 3 + 2] = 0.0f;
    }

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(objectVertices), objectVertices, GL_STATIC_DRAW);
}

void initStars() {
    GLfloat starVertices[numberOfStars * 4]; 
    srand(time(NULL)); 

    // Get the aspect ratio of the window
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    float aspectRatio = (float)width / (float)height;
	
    for (int i = 0; i < numberOfStars; ++i) {
        starVertices[i * 4] = ((float)rand() / RAND_MAX) * 2.0f * aspectRatio - aspectRatio; 
        starVertices[i * 4 + 1] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        starVertices[i * 4 + 2] = 0.0f; 
        starVertices[i * 4 + 3] = ((float)rand() / RAND_MAX) * 3.0f + 1.0f; 
    }

    glGenBuffers(1, &starVBO);
    glBindBuffer(GL_ARRAY_BUFFER, starVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(starVertices), starVertices, GL_STATIC_DRAW);
}

void initConstantlyMovingObject(GLuint& vbo) {
    GLfloat objectVertices[] = {
        0.09f, 0.11f, 0.0f,
		0.07f, -0.02f, 0.0f,
		0.04f, -0.06f, 0.0f,
		-0.02f, -0.08f, 0.0f,
		-0.08f, -0.06f, 0.0f,
		-0.11f, -0.03f, 0.0f,
		-0.11f, -0.15f, 0.0f,
		-0.10f, -0.17f, 0.0f,
		-0.05f, -0.17f, 0.0f,
		-0.03f, -0.15f, 0.0f,
		-0.03f, -0.11f, 0.0f,
		0.01f, -0.11f, 0.0f,
		0.01f, -0.15f, 0.0f,
		0.02f, -0.17f, 0.0f,
		0.07f, -0.17f, 0.0f,
		0.09f, -0.15f, 0.0f,
		0.09f, 0.11f, 0.0f,
        
		0.09f, 0.11f, 0.0f,
		0.07f, 0.14f, 0.0f,
		0.04f, 0.16f, 0.0f,
		-0.01f, 0.17f, 0.0f,
		-0.08f, 0.15f, 0.0f,
		-0.11f, 0.09f, 0.0f,
		-0.11f, -0.03f, 0.0f,
		-0.08f, -0.06f, 0.0f,
		-0.02f, -0.08f, 0.0f,
		0.04f, -0.06f, 0.0f,
		0.07f, -0.02f, 0.0f,
		0.09f, 0.11f, 0.0f,
		
		0.13f, 0.04f, 0.0f,
		0.09f, 0.04f, 0.0f,
		0.09f, -0.10f, 0.0f,
		0.12f, -0.10f, 0.0f,
		0.13f, -0.07f, 0.0f,
		0.13f, 0.04f, 0.0f,
		
		0.13f, 0.05f, 0.0f,
		0.12f, 0.07f, 0.0f,
		0.09f, 0.07f, 0.0f,
		0.09f, 0.04f, 0.0f,
		0.13f, 0.04f, 0.0f,
		0.13f, 0.05f, 0.0f,
		
		0.02f, 0.09f, 0.0f,
		-0.0f, 0.11f, 0.0f,
		-0.10f, 0.11f, 0.0f,
		-0.12f, 0.09f, 0.0f,
		-0.12f, 0.04f, 0.0f,
		-0.10f, 0.02f, 0.0f,
		-0.0f, 0.02f, 0.0f,
		0.02f, 0.04f, 0.0f,
		0.02f, 0.09f, 0.0f,
		
		-0.05f, 0.09f, 0.0f,
		-0.06f, 0.10f, 0.0f,
		-0.09f, 0.10f, 0.0f,
		-0.10f, 0.09f, 0.0f,
		-0.10f, 0.08f, 0.0f,
		-0.09f, 0.07f, 0.0f,
		-0.06f, 0.07f, 0.0f,
		-0.05f, 0.08f, 0.0f,
		-0.05f, 0.09f, 0.0f
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(objectVertices), objectVertices, GL_STATIC_DRAW);
}

// Drawing Functions

void drawRotatingObject(GLuint rotatingObjectVBO) {
    glPushMatrix();  
    glTranslatef(-0.50f, 0.08f, 0.0f); 

    glBindBuffer(GL_ARRAY_BUFFER, rotatingObjectVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f); 

    glColor3f(0.493f, 0.462f, 0.587f); 
    glDrawArrays(GL_POLYGON, 0, 13);

    glColor3f(0.0f, 0.0f, 0.0f); 
    glDrawArrays(GL_POLYGON, 13, 13);

    glColor3f(1.0f, 1.0f, 0.0f); 
    glDrawArrays(GL_POLYGON, 26, 19);

    glColor3f(1.0f, 0.5f, 0.0f); 
    glDrawArrays(GL_POLYGON, 45, 12);

    glColor3f(0.9f, 0.4f, 0.0f); 
    glDrawArrays(GL_POLYGON, 57, 7);

    glColor3f(0.827f, 0.827f, 0.827f); 
    glDrawArrays(GL_POLYGON, 64, 16);

    glColor3f(0.727f, 0.727f, 0.727f);
    glDrawArrays(GL_POLYGON, 80, 21);

    glPopMatrix();  

    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawMovingObject(GLuint objectVBO) {
    glPushMatrix();
    glTranslatef(-1.45f, 0.0f, 0.0f); 
    glBindBuffer(GL_ARRAY_BUFFER, objectVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    // Translate the object based on key presses
    glTranslatef(0.18f + movingObjectX, -0.45f + movingObjectY, 0.0f);
    glRotatef(rotationAngleMovingObject, 0.0f, 0.0f, 1.0f);

    // Draw the object
    glColor3f(0.75f, 0.0f, 0.0f);
    glDrawArrays(GL_POLYGON, 0, 17);

    glColor3f(1.0f, 0.0f, 0.0f);
    glDrawArrays(GL_POLYGON, 17, 12);

    glColor3f(0.0f, 0.9f, 0.9f);
    glDrawArrays(GL_POLYGON, 29, 6);

    glColor3f(0.0f, 1.0f, 1.0f);
    glDrawArrays(GL_POLYGON, 35, 6);

    glColor3f(0.529f, 0.808f, 0.922f);
    glDrawArrays(GL_POLYGON, 41, 9);

    glColor3f(1.0f, 1.0f, 1.0f);
    glDrawArrays(GL_POLYGON, 50, 9);

    glPopMatrix();  

    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawScalingObject(GLuint scalingObjectVBO) {
    glPushMatrix(); 
    glTranslatef(-0.50f, 0.08f, 0.0f); 

    // Rotate the scaling object
    glRotatef(rotationAngleScalingObject, 0.0f, 0.0f, 1.0f);

    glBindBuffer(GL_ARRAY_BUFFER, scalingObjectVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    // Scale the object
    glScalef(scalingFactor, scalingFactor, 1.0f); 

    glShadeModel(GL_SMOOTH);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor3f(0.1f, 0.15f, 0.6f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);

    int numVertices = 30; 
    for (int i = 0; i <= numVertices; i++) {
        float ratio = i / static_cast<float>(numVertices);
        // Calculate the gradient colors
        float red = 0.0f * (1 - ratio) + 0.2f * ratio;
        float green = 0.15f * (1 - ratio) + 0.3f * ratio;
        float blue = 0.6f * (1 - ratio) + 0.6f * ratio;
        // Set the color for the current vertex
        glColor3f(red, green, blue);
        // Calculate the vertex position
        float angle = static_cast<float>(i) * (2.0f * M_PI / numVertices);
        float x = 0.1f * cos(angle);
        float y = 0.1f * sin(angle);
        // Add the vertex to the fan
        glVertex2f(x, y);
    }
    glEnd();

    // Continent 1 
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.8f, 0.2f); glVertex2f(0.023, 0.025);
    glColor3f(0.4f, 0.9f, 0.2f); glVertex2f(0.043, 0.025);
    glColor3f(0.6f, 1.0f, 0.2f); glVertex2f(0.053, 0.04);
    glColor3f(0.8f, 1.0f, 0.1f); glVertex2f(0.068, 0.035);
    glColor3f(1.0f, 1.0f, 0.2f); glVertex2f(0.083, 0.045);
    glColor3f(1.0f, 1.0f, 0.2f); glVertex2f(0.098, 0.03);
    glColor3f(1.0f, 1.0f, 0.2f); glVertex2f(0.103, 0.015);
    glColor3f(1.0f, 1.0f, 0.2f); glVertex2f(0.098, -0.005);
    glColor3f(1.0f, 1.0f, 0.2f); glVertex2f(0.088, -0.01);
    glColor3f(0.8f, 1.0f, 0.1f); glVertex2f(0.083, -0.02);
    glColor3f(0.6f, 1.0f, 0.2f); glVertex2f(0.068, -0.03);
    glColor3f(0.4f, 0.9f, 0.2f); glVertex2f(0.048, -0.035);
    glColor3f(0.2f, 0.8f, 0.2f); glVertex2f(0.033, -0.025);
    glColor3f(0.4f, 0.9f, 0.2f); glVertex2f(0.018, -0.015);
    glColor3f(0.6f, 1.0f, 0.2f); glVertex2f(0.013, 0.0);
    glColor3f(0.8f, 1.0f, 0.1f); glVertex2f(0.018, 0.015);
    glEnd();

    // Continent 2
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(-0.06, -0.082);
    glColor3f(0.2f, 0.8f, 0.0f); glVertex2f(-0.04, -0.082);
    glColor3f(0.4f, 0.6f, 0.0f); glVertex2f(-0.03, -0.097);
    glColor3f(0.6f, 0.4f, 0.0f); glVertex2f(-0.025, -0.094);
    glColor3f(0.7f, 0.3f, 0.0f); glVertex2f(-0.015, -0.092);
    glColor3f(0.8f, 0.2f, 0.0f); glVertex2f(-0.008, -0.097);
    glColor3f(0.9f, 0.1f, 0.0f); glVertex2f(0.0, -0.102);
    glColor3f(1.0f, 0.5f, 0.0f); glVertex2f(0.008, -0.099);
    glColor3f(1.0f, 0.4f, 0.0f); glVertex2f(0.015, -0.087);
    glColor3f(0.9f, 0.1f, 0.0f); glVertex2f(0.02, -0.082);
    glColor3f(0.8f, 0.2f, 0.0f); glVertex2f(0.015, -0.052);
    glColor3f(0.7f, 0.3f, 0.0f); glVertex2f(0.005, -0.047);
    glColor3f(0.6f, 0.4f, 0.0f); glVertex2f(0.002, -0.044);
    glColor3f(0.5f, 0.5f, 0.0f); glVertex2f(0.0, -0.037);
    glColor3f(0.4f, 0.6f, 0.0f); glVertex2f(-0.005, -0.034);
    glColor3f(0.3f, 0.7f, 0.0f); glVertex2f(-0.015, -0.027);
    glColor3f(0.2f, 0.8f, 0.0f); glVertex2f(-0.025, -0.024);
    glColor3f(0.1f, 0.9f, 0.0f); glVertex2f(-0.035, -0.022);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(-0.045, -0.027);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(-0.05, -0.032);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(-0.055, -0.037);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(-0.065, -0.042);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(-0.07, -0.057);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(-0.07, -0.067);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(-0.065, -0.072);
    glEnd();

    // Continent 3
    float xOffset = -0.085;
    float yOffset = 0.08;
    float scaleFactor = 1.15;

    glBegin(GL_POLYGON);

    float startColor[3] = { 0.0f, 1.0f, 0.0f };
    float endColor[3] = { 1.0f, 0.5f, 0.0f };

    int totalVertices = 26;

    float vertices[26][2] = {
        {0.08, -0.06},
        {0.06, -0.06},
        {0.05, -0.075},
        {0.045, -0.072},
        {0.035, -0.07},
        {0.028, -0.075},
        {0.02, -0.08},
        {0.012, -0.077},
        {0.005, -0.065},
        {0.0, -0.06},
        {0.005, -0.03},
        {0.015, -0.025},
        {0.018, -0.022},
        {0.02, -0.015},
        {0.025, -0.012},
        {0.035, -0.005},
        {0.045, -0.002},
        {0.055, 0.0},
        {0.065, -0.005},
        {0.07, -0.01},
        {0.075, -0.015},
        {0.085, -0.02},
        {0.09, -0.035},
        {0.09, -0.045},
        {0.085, -0.05},
        {0.08, -0.06}
    };

    for (int i = 0; i < totalVertices; ++i) {
        float ratio = static_cast<float>(i) / (totalVertices - 1);
        float r = startColor[0] * (1 - ratio) + endColor[0] * ratio;
        float g = startColor[1] * (1 - ratio) + endColor[1] * ratio;
        float b = startColor[2] * (1 - ratio) + endColor[2] * ratio;

        glColor3f(r, g, b);
        glVertex2f((vertices[i][0] + xOffset) * scaleFactor, (vertices[i][1] + yOffset) * scaleFactor);
    }

    glEnd();

    glPopMatrix(); 

    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawStars() {
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = -1; i <= 1; ++i) {
        glPushMatrix(); 

        // Apply translation for each segment of the star field
        glTranslatef(starTranslationX + i * 2.0f, starTranslationY, 0.0f);

        glBindBuffer(GL_ARRAY_BUFFER, starVBO);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(GLfloat) * 4, 0);
        glPointSize(2.5f);
        glDrawArrays(GL_POINTS, 0, numberOfStars);
        glDisableClientState(GL_VERTEX_ARRAY);

        glPopMatrix(); 
    }
}

void drawSun() {
    glPushMatrix(); 

    // Translate to the position of the sun
    glTranslatef(1.55f, -0.95f, 0.0f); 
    glScalef(2.0f,2.0f,0.0f);

    // Rotate the sun around its center
    glRotatef(rotationAngleSun, 0.0f, 0.0f, -1.0f);

    int numSegments = 40; 
    float radius = 0.6f;   
    float lineWidth = 3.0f;

    glBegin(GL_TRIANGLE_FAN);

    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);

    for (int i = 0; i <= numSegments; i++) {
        float angle = 2.0f * M_PI * i / numSegments;
        if (i % 2 == 0) {
            glColor3f(1.0f, 0.5f, 0.0f);
        }
        else {
            glColor3f(1.0f, 1.0f, 0.0f);
        }
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();

    glLineWidth(lineWidth);

    glBegin(GL_LINES);
    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * M_PI * i / numSegments;
        float endRadius = radius + 0.1f; 

        if (i % 2 == 0) {
            glColor3f(1.0f, 0.5f, 0.0f); 
        }
        else {
            glColor3f(1.0f, 1.0f, 0.0f); 
        }

        glVertex2f(cos(angle) * radius, sin(angle) * radius);
        glVertex2f(cos(angle) * endRadius, sin(angle) * endRadius);
    }
    glEnd();

    glLineWidth(1.0f);

    glPopMatrix(); 
}

void drawConstantlyMovingObject(GLuint objectVBO) {
    glPushMatrix();

    glBindBuffer(GL_ARRAY_BUFFER, objectVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

        // Translate the object from left to right - Inverted in updateConstantlyMovingObject() function
        glTranslatef(-1.9f + translationcmX, 0.5f, 0.0f);
        glRotatef(rotationAngleConstantlyMovingObject, 0.0f, 0.0f, 1.0f); // Rotate the object
		glScalef(0.5f,0.5f,0.0f);
		
        glColor3f(0.50196f, 0.0f, 0.50196f);
        glDrawArrays(GL_POLYGON, 0, 17);

        glColor3f(0.60196f, 0.0f, 0.60196f);
        glDrawArrays(GL_POLYGON, 17, 12);

        glColor3f(0.0f, 0.9f, 0.9f);
        glDrawArrays(GL_POLYGON, 29, 6);

        glColor3f(0.0f, 1.0f, 1.0f);
        glDrawArrays(GL_POLYGON, 35, 6);

        glColor3f(0.529f, 0.808f, 0.922f);
        glDrawArrays(GL_POLYGON, 41, 9);

        glColor3f(1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_POLYGON, 50, 9);
    

    glPopMatrix(); 

    glDisableClientState(GL_VERTEX_ARRAY);
}

// Update Functions

void updateIdleObjects() {
    starTranslationX += starSpeedX;

    // Reset the translation to create a looping effect
    if (starTranslationX > 2.0f) starTranslationX -= 4.0f;

    // Update sun rotation
    const double sunRotationSpeed = 0.08; 
    rotationAngleSun += static_cast<GLfloat>(sunRotationSpeed);
    if (rotationAngleSun >= 360.0f) rotationAngleSun -= 360.0f;
    
    // Update constantly moving object
    clock_t currentTime = clock();
    double elapsedTime = (double)(currentTime - startcmTime) / CLOCKS_PER_SEC;

    const double movementSpeed = 0.1;
    translationcmX = static_cast<GLfloat>(movementcmDistance - std::fmod(elapsedTime * movementSpeed, movementcmDistance));

    const double rotationSpeed = -150.0;
    rotationAngleConstantlyMovingObject = static_cast<GLfloat>(rotationSpeed * elapsedTime);
	
    glutPostRedisplay();
}

void updateMovingObject() {
    // Update the translationX based on time elapsed
    clock_t currentTime = clock();
    double elapsedTime = (double)(currentTime - startTime) / CLOCKS_PER_SEC;

    const double movementSpeed = 0.1;
    translationX = static_cast<GLfloat>(std::fmod(elapsedTime * movementSpeed, movementDistance));

    // Update the rotationAngleMovingObject based on time elapsed
    const double rotationSpeed = -115.0; 
    rotationAngleMovingObject = static_cast<GLfloat>(std::fmod(elapsedTime * rotationSpeed, 360.0));

    // Update the rotation angle for the scaling object
    const double scalingObjectRotationSpeed = 15.0; 
    rotationAngleScalingObject = static_cast<GLfloat>(std::fmod(elapsedTime * scalingObjectRotationSpeed, 360.0));

    glutPostRedisplay();
}

void updateScalingObject(int button, int direction, int x, int y) {
    // Update scaling factor based on the scroll direction
    scalingFactor += direction * 0.1;

    // Clamp the scaling factor to a reasonable range
    scalingFactor = std::max(1.0f, std::min(scalingFactor, 3.7f));

    glutPostRedisplay();
}

void updatePosition(int value) {
    if (keyWPressed) movingObjectY += movementSpeed;
    if (keySPressed) movingObjectY -= movementSpeed;
    if (keyAPressed) movingObjectX -= movementSpeed;
    if (keyDPressed) movingObjectX += movementSpeed;

    glutPostRedisplay();
    glutTimerFunc(16, updatePosition, 0); // Update every 16 milliseconds (~60 FPS)
}

// GLUT Callback Functions

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
	updateIdleObjects(); // Update star positions, sun rotations, and constantly moving object positions
    drawStars();
    drawSun();
    drawRotatingObject(rotatingObjectVBO);
    drawScalingObject(scalingObjectVBO);
    drawConstantlyMovingObject(constantlyMovingObjectVBO);
    drawMovingObject(movingObjectVBO);  
    updateMovingObject();

    glutSwapBuffers();
}

void rotateObjects() {
    rotationAngle += 1.5f; //Speed of the rotating object 
    updateIdleObjects();
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            // Left mouse button is pressed, start rotating
            isLeftMouseButtonDown = true;
            glutIdleFunc(rotateObjects);
        }
        else if (state == GLUT_UP) {
            // Left mouse button is released, stop rotating
            isLeftMouseButtonDown = false;
            glutIdleFunc(NULL);
            glutIdleFunc(updateIdleObjects);
        }
    }
    else if (button == 3 || button == 4) {
        // Scroll wheel event, update scaling for the scaling object
        int direction = (button == 3) ? 1 : -1; // 1 for scroll up, -1 for scroll down
        updateScalingObject(button, direction, x, y);
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
    case 'W':
        keyWPressed = true;
        break;
    case 's':
    case 'S':
        keySPressed = true;
        break;
    case 'a':
    case 'A':
        keyAPressed = true;
        break;
    case 'd':
    case 'D':
        keyDPressed = true;
        break;
    case 27: // ASCII code for the "Esc" key
        exit(0);
        break;
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
    case 'W':
        keyWPressed = false;
        break;
    case 's':
    case 'S':
        keySPressed = false;
        break;
    case 'a':
    case 'A':
        keyAPressed = false;
        break;
    case 'd':
    case 'D':
        keyDPressed = false;
        break;
    }
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    if (width <= height) {
        // Maintain the aspect ratio when the width is less than or equal to height
        gluOrtho2D(-1.0f, 1.0f, -1.0f / aspectRatio, 1.0f / aspectRatio);
    }
    else {
        // Maintain the aspect ratio when the height is less than width
        gluOrtho2D(-1.0f * aspectRatio, 1.0f * aspectRatio, -1.0f, 1.0f);
    }

    glMatrixMode(GL_MODELVIEW);
}
