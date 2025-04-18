# Computer Graphics Projects

This repository contains various computer graphics projects created for the Computer Graphics and Visual Computing course. Each project demonstrates different OpenGL concepts and techniques.

## Project Content
CG_lab1: Draws two intersecting lines.
CG_lab2: Displays a hexagon made of colored triangles.
CG_lab3: Renders a smiley face with basic keyboard and mouse interactions.
CG_lab4: Implements the smiley face using vertex arrays.
CG_lab5: Uses VBOs and VAOs to render the smiley face.
CG_lab6: Displays an octahedron with spotlights and camera controls.

### Final Project
CG_project: Combines multiple objects with transformations (translation, rotation, scaling) and advanced features like VBOs, vertex arrays, and animations.
Project Controls
- W/A/S/D: Move the "Among Us" character.
- Mouse Scroll: Scale the Earth object.
- Left Mouse Button: Rotate the moon.
- ESC: Exit the program.

## How to Run

### Prerequisites

1. Install OpenGL and GLUT:
   - On Ubuntu/Debian:
     ```sh
     sudo apt-get install freeglut3-dev
     ```
   - On Windows:
     - Install [FreeGLUT](http://freeglut.sourceforge.net/) and configure your compiler to include the necessary libraries.
   - On macOS:
     - Install OpenGL and GLUT using Xcode or Homebrew.

2. Install a C++ compiler (e.g., [g++](http://_vscodecontentref_/9)).

### Compilation and Execution

1. Navigate to the project directory:
   ```sh
   cd /path/to/Computer-Graphics-Projects
2. Compile the desired project file. For example, to compile CG_lab1.cpp:
   ```sh
   g++ CG_lab1.cpp -o CG_lab1 -lGL -lGLU -lglut
3. Run the compiled program:
   ```sh
   ./CG_lab1
4. Repeat the above steps for other .cpp files by replacing CG_lab1.cpp with the desired file name.

### Running the Final Project
To run the final project (CG_project.cpp), use the following commands:
```sh
g++ CG_project.cpp -o CG_project -lGL -lGLU -lglut -lGLEW
./CG_project
