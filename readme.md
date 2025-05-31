# Bouncing Shapes

A simple C++ application that displays animated shapes bouncing around a window. Shapes are loaded from a configuration file and bounce off window boundaries.

**Note**: This project was created as an assignment for the COMP4300 course by Dave Churchill: https://www.youtube.com/@DaveChurchill

## Features

- Configurable window size and shapes via text file
- Support for circles and rectangles
- Customizable colors, positions, and speeds
- Text labels on each shape
- Smooth 60 FPS animation

## Requirements

- Visual Studio 2019 or later
- SFML library
- vcpkg package manager

## Building with Visual Studio and vcpkg

1. **Install vcpkg** (if not already installed):
   ```bash
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   ./bootstrap-vcpkg.bat
   ```

2. **Install SFML**:
   ```bash
   ./vcpkg install sfml:x64-windows
   ```

3. **Integrate vcpkg with Visual Studio**:
   ```bash
   ./vcpkg integrate install
   ```

4. **Build the project**:
   - Open Visual Studio
   - Create a new C++ Console Application project
   - Add the source code to your project
   - Make sure your project is set to x64 configuration
   - Build and run

## Usage

1. Create a `config.txt` file in your project directory with the following format:

```
Window 800 600
Font arial.ttf 24 255 255 255
Circle MyCircle 100 100 2 1 255 0 0 50
Rectangle MyRect 200 200 -1 2 0 255 0 100 75
```

2. Place a font file (e.g., `arial.ttf`) in your project directory
3. Run the executable

## Config File Format

- `Window width height` - Set window dimensions
- `Font filename size r g b` - Set font file, size, and color (RGB)
- `Circle name x y speed_x speed_y r g b radius` - Create a circle
- `Rectangle name x y speed_x speed_y r g b width height` - Create a rectangle

## Controls

- Close the window to exit the application