# 🖥️ Computer Graphics Projects

This repository contains a collection of OpenGL-based computer graphics projects developed for the **Computer Graphics and Visual Computing** course. Each project demonstrates fundamental to advanced rendering concepts using OpenGL, GLUT, and C++.

## 📁 Projects Overview

| Folder       | Description |
|--------------|-------------|
| `CG_lab1`    | Draws two intersecting lines. |
| `CG_lab2`    | Displays a hexagon made of colored triangles. |
| `CG_lab3`    | Renders a smiley face with basic keyboard and mouse interactions. |
| `CG_lab4`    | Implements the smiley face using vertex arrays. |
| `CG_lab5`    | Uses VBOs and VAOs to render the smiley face. |
| `CG_lab6`    | Displays an octahedron with spotlights and camera controls. |
| `CG_project` | **Final Project**: Combines multiple objects with transformations (translation, rotation, scaling), advanced features like VBOs, vertex arrays, and basic animation. |

## 🎮 Final Project Controls

- `W/A/S/D` – Move the **Among Us** character  
- `Mouse Scroll` – Scale the **Earth** object  
- `Left Mouse Button` – Rotate the **Moon**  
- `ESC` – Exit the program  

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

1. Navigate to the project folder (e.g., `CG_lab1`):
   ```bash
   cd CG_lab1
   ```

2. Compile the file:
   ```bash
   g++ CG_lab1.cpp -o CG_lab1 -lGL -lGLU -lglut
   ```

3. Run the executable:
   ```bash
   ./CG_lab1
   ```

### 👉 For the Final Project:

```bash
cd CG_project
g++ CG_project.cpp -o CG_project -lGL -lGLU -lglut -lGLEW
./CG_project
```

## 📸 Final Project Preview


## 📜 License

This project is open-source and available under the [MIT License](LICENSE).
