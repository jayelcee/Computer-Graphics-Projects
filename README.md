# 🖥️ Computer Graphics Projects

This repository contains a collection of OpenGL-based computer graphics projects developed for the **Computer Graphics and Visual Computing** course. Each project demonstrates fundamental to advanced rendering concepts using OpenGL, GLUT, and C++.

## 📄 Project List

| File            | Description |
|------------------|-------------|
| `CG_lab1.cpp`    | Draws two intersecting lines. |
| `CG_lab2.cpp`    | Displays a hexagon made of colored triangles. |
| `CG_lab3.cpp`    | Renders a smiley face with basic keyboard and mouse interactions. |
| `CG_lab4.cpp`    | Implements the smiley face using vertex arrays. |
| `CG_lab5.cpp`    | Uses VBOs and VAOs to render the smiley face. |
| `CG_lab6.cpp`    | Displays an octahedron with spotlights and camera controls. |
| `CG_project.cpp` | **Final Project**: Combines multiple objects with transformations (translation, rotation, scaling), VBOs, vertex arrays, and animations. |

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

1. From the root directory of the repository, compile any `.cpp` file. For example, to compile and run `CG_lab1.cpp`:

   ```bash
   g++ CG_lab1.cpp -o CG_lab1 -lGL -lGLU -lglut
   ./CG_lab1
   ```

2. Replace `CG_lab1.cpp` with the filename of the project you want to run.

### 👉 Final Project:

```bash
g++ CG_project.cpp -o CG_project -lGL -lGLU -lglut -lGLEW
./CG_project
```

## 📸 Preview

### Lab 1
![image](https://github.com/user-attachments/assets/8fa45408-6a52-4a2a-be67-a46515f1138e)

### Lab 2
![image](https://github.com/user-attachments/assets/9123a81a-81ff-4648-84bb-98ec8be91eab)

### Lab 3
![image](https://github.com/user-attachments/assets/e88c00e0-10dd-4e36-9230-34c0af9f5181)

### Lab 4
![msrdc  Camasura_Lab4_(Ubuntu)  2025-04-18_15-42-54](https://github.com/user-attachments/assets/44dddfe2-a58d-4ac8-8da0-34a055f952a9)




## 📜 License

This project is open-source and available under the [MIT License](LICENSE).
