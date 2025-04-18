# 🖥️ Computer Graphics Projects

This repository contains a collection of OpenGL-based computer graphics projects developed for the **Computer Graphics and Visual Computing** course. Each project demonstrates fundamental to advanced rendering concepts using OpenGL, GLUT, and C++.

## 📄 Lab Overview

### Lab 1: Draws two intersecting lines.
![image](https://github.com/user-attachments/assets/8fa45408-6a52-4a2a-be67-a46515f1138e)

### Lab 2: Displays a hexagon made of colored triangles.
![image](https://github.com/user-attachments/assets/9123a81a-81ff-4648-84bb-98ec8be91eab)

### Lab 3: Renders a smiley face using immediate mode (glBegin/glEnd) with basic keyboard controls (WASD) and mouse clicks to change eye color.
![msrdc  Camasura_Lab3_(Ubuntu)  2025-04-18_15-53-30](https://github.com/user-attachments/assets/87a403fb-b368-4cc1-a9ca-a080d2080f09)

### Lab 4: Reimplements the smiley face using vertex arrays and glVertexPointer, improving performance and separating geometry data from logic. Maintains same interactivity as Lab 3 with added movement control (arrow keys).
![msrdc  Camasura_Lab4_(Ubuntu)  2025-04-18_15-55-47](https://github.com/user-attachments/assets/cd63eac9-1c0f-46a9-bcc8-72ac9193238e)

### Lab 5: Optimizes rendering further with Vertex Buffer Objects (VBOs) and Vertex Array Objects (VAOs). Keeps movement and mouse interactivity but introduces modular functions (initVBOs(), createVAO(), etc.) for better structure and scalability.
![msrdc  Camasura_Lab5_(Ubuntu)  2025-04-18_15-57-52](https://github.com/user-attachments/assets/b726c94a-c093-4da7-9a35-199251dc16c7)

### Lab 6: 	Renders a rotating octahedron illuminated by three colored spotlights (red, green, and blue), with interactive 3D camera controls. This program uses smooth camera movement, spotlight directionality, and real-time lighting effects to enhance visual realism.
#### Control Guide
Camera Movement (Smooth/Continuous):
- W / S – Move forward / backward
- A / D – Move left / right
- Q / E – Move down / up

Other Controls:
- ESC – Exit the program

Visual Features:
- Rotating Octahedron – Automatically spins horizontally
- Three Spotlights – Red, green, and blue lights with directional focus and realistic attenuation
- Smooth Camera Control – Movement is velocity-based for fluid transitions in 3D space

![msrdc  Camasura_Lab6_(Ubuntu)  2025-04-18_16-12-57](https://github.com/user-attachments/assets/fd19569c-08c5-4d73-b7b5-5f027c7f370b)


## 🎮 Final Project
Renders a dynamic 3D solar scene featuring Earth, Moon, background stars, and an Among Us character using OpenGL. Implements object transformations (translation, rotation, scaling), VBOs, and full-screen rendering. Designed for interactive visualization with animated motion, real-time controls, and a stylized space environment.
#### Control Guide
- `W/A/S/D` – Move the **Among Us** character  
- `Mouse Scroll` – Scale the **Earth** object  
- `Left Mouse Button` – Rotate the **Moon**  
- `ESC` – Exit the program  

#### In collaboration with Shawn Aaron Quirante
Video Demo: https://youtu.be/HNalhw2L8Jk

## 🛠️ Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/jayelcee/Computer-Graphics-Projects.git
cd Computer-Graphics-Projects
```

### 2. Install Dependencies

#### Linux (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install g++ freeglut3-dev libglew-dev
```

#### macOS

- Install Xcode Command Line Tools:
  ```bash
  xcode-select --install
  ```
- Or use Homebrew:
  ```bash
  brew install glew
  ```

#### Windows

- Install [FreeGLUT](http://freeglut.sourceforge.net/)
- Configure your compiler (e.g., MinGW or MSVC) to include FreeGLUT and GLEW headers and libraries.

## ⚙️ Compilation & Execution

1. From the root directory of the repository, compile any `.cpp` file. For example, to compile and run `CG_lab1.cpp`:

   ```bash
   g++ CG_lab1.cpp -o CG_lab1 -lGL -lGLU -lglut
   ./CG_lab1
   ./CG_lab2
   ./CG_lab3
   ./CG_lab4
   ```
   ```bash
   g++ CG_lab5.cpp -o CG_lab5 -lGL -lGLU -lglut -lGLEW
   ./CG_lab5
   ```

2. Replace `CG_lab1.cpp` with the filename of the project you want to run.

### 👉 Final Project:

```bash
g++ CG_project.cpp -o CG_project -lGL -lGLU -lglut -lGLEW
./CG_project
```


## 📜 License

This project is open-source and available under the [MIT License](LICENSE).
