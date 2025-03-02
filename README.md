# Polygon Rendering Software

## Description

This is a simple polygon rendering software that uses a Constructive Solid Geometry (CSG) model to create and display 3D shapes. The software generates images of 3D models based on user-defined parameters, allowing users to manipulate viewpoints, apply geometric transformations, and render the models as BMP images.

## Features

- **3D Model Creation**: Users define 3D shapes using a simplified CSG model.
- **Viewpoint Adjustment**: Change the camera position for different perspectives.
- **Geometric Transformations**:
  - Scaling
  - Translation
  - Rotation
- **Rendering**:
  - Converts CSG models into polygon models composed of triangles.
  - Uses Z-buffer method for hidden surface removal.
  - Applies Gouraud shading for smooth lighting effects.
- **Configuration via Files**:
  - `settings.txt`: Defines camera position, light source properties, etc.
  - `polygons.txt`: Defines shapes, positions, sizes, and colors.
- **BMP Image Output**: Renders the final 3D scene and saves it as `output.bmp`.

## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/c-hikita/polygon-rendering.git
   ```
2. Navigate to the project directory:
   ```sh
   cd polygon-rendering
   ```
3. Compile the program:
   ```sh
   cl main.c
   ```
   *(Ensure you have a C compiler installed, such as GCC.)*

## Usage

1. Edit `settings.txt` to configure the camera position and lighting properties.
2. Edit `polygons.txt` to define the 3D shapes to render.
3. Compile and run the program:
   ```sh
   main
   ```
4. The program will read `settings.txt` and `polygons.txt`, then display a menu in the console:
   - `0`: Exit
   - `1`: Render the model and save it as `output.bmp`
   - `2`: Change camera position
   - `3`: Scale a primitive
   - `4`: Move a primitive
   - `5`: Rotate a primitive
   - `6`: Display the menu again
5. Follow the prompts to manipulate and render the 3D model.
6. View the generated `output.bmp` file in an image viewer.

## Technical Details

- **Constructive Solid Geometry (CSG)**: Uses basic primitives (cube, cylinder, sphere) with union operations.
- **Polygon Model Conversion**: CSG models are converted into triangle meshes for rendering.
- **Rendering Pipeline**:
  - Perspective projection (left-hand system)
  - Hidden surface removal via Z-buffering
  - Smooth shading using Gouraud interpolation
- **Platform**: Windows (Command-line interface)

## Dependencies

- Standard C library (`math.h` for mathematical calculations)
- No external libraries required