# 2D Graphics Editor

A lightweight, terminal-based 2D Graphics Editor written in C. This project uses a character-based canvas (80x25) to render geometric shapes using standard computer graphics algorithms.

## 🚀 Features

- **Dynamic Canvas**: A real-time 80x25 character grid for drawing.
- **Geometric Shapes**:
  - **Lines**: Implemented using Bresenham's Line Algorithm.
  - **Rectangles**: Defined by two corner points.
  - **Circles**: Implemented using the Midpoint Circle Algorithm.
  - **Triangles**: Defined by three vertices.
- **Manipulation Tools**:
  - Add new objects.
  - Delete existing objects by index.
  - Modify object coordinates and parameters.
- **Interactive Menu**: Easy-to-use terminal interface for all operations.

## 🛠️ Algorithms Used

- **Bresenham's Line Algorithm**: For efficient line drawing.
- **Midpoint Circle Algorithm**: For smooth circle rasterization.

## 📁 Project Structure

```text
Acp.project/
├── main.c           # Core application logic and algorithms
├── .gitignore       # Git ignore rules
├── test_input.txt   # Sample input for testing
└── README.md        # Project documentation
```

## ⚙️ Installation & Running

### Prerequisites
- A C compiler (e.g., GCC, Clang, or MSVC).

### Compilation
Compile the project using your preferred C compiler:

```bash
gcc main.c -o graphics_editor -lm
```

### Usage
Run the generated executable:

```bash
./graphics_editor
```

## 🎮 Interface Preview

```text
--- 2D Graphics Editor ---
1. Add Object
2. Delete Object
3. Modify Object
4. Display Picture
5. Exit
Choice: 
```

## 📝 License
This project is open-source and available for educational purposes.
