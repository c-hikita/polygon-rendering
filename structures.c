/** 
 * @file structures.c
 * @brief Data structures for 3D graphics and rendering
 * This file defines the necessary data structures for representing and manipulating 
 * geometric objects, colors, and rendering settings in a 3D graphics application.
 */

/**
 * @struct Vector
 * @brief A 3D vector representation
 * This structure represents a point or direction in 3D space with x, y, and z components.
 */
typedef struct {
    double x, y, z; ///< The coordinates of the vector
} Vector;

/**
 * @struct Color1
 * @brief RGB color representation with values in the range [0, 1]
 * This structure represents a color with red, green, and blue components, 
 * where each component is a floating-point value between 0 and 1.
 */
typedef struct {
    double r, g, b; ///< The red, green, and blue components of the color
} Color1;

/**
 * @struct Color255
 * @brief RGB color representation with values in the range [0, 255]
 * This structure represents a color with red, green, and blue components, 
 * where each component is an integer value between 0 and 255.
 */
typedef struct {
    int r, g, b; ///< The red, green, and blue components of the color (range 0-255)
} Color255;

/**
 * @struct ColorPlot
 * @brief A structure to represent a point with associated color
 * This structure stores a 3D point and its corresponding color.
 */
typedef struct {
    Vector p;  ///< The point in 3D space
    Color255 c; ///< The color at that point
} ColorPlot;

/**
 * @struct NormalVectors
 * @brief A structure for storing normal vectors
 * This structure stores an array of 6 normal vectors, typically used for lighting 
 * and surface calculations in 3D models.
 */
typedef struct {
    Vector v[6]; ///< An array of 6 normal vectors
    int count; ///< The number of valid normal vectors
} NormalVectors;

/**
 * @struct Triangle3D
 * @brief A structure representing a 3D triangle
 * This structure defines a 3D triangle using its 3 vertices, their associated 
 * normal vectors, the color, material properties, and the type of the shape (cube, cylinder, or sphere).
 */
typedef struct {
    Vector p[3]; ///< The 3 vertices of the triangle
    Vector v[3]; ///< The normal vectors at each vertex
    Color255 o; ///< The original color of the triangle
    int n; ///< The material property index
    double k[3]; ///< Material constants [ambient, diffuse, specular]
    Vector g, ref; ///< Geometrical and reflection vectors
    int id; ///< Shape ID (1: cube, 2: cylinder, 3: sphere)
} Triangle3D;

/**
 * @struct Rendered
 * @brief A structure to store a rendered triangle
 * This structure holds the transformed vertices and color plots of a triangle after rendering.
 */
typedef struct {
    ColorPlot cp[3]; ///< An array of 3 color plots (one for each vertex of the triangle)
    Vector g; ///< The centroid of the rendered triangle
} Rendered;

/**
 * @struct Settings
 * @brief A structure for storing rendering settings
 * This structure holds the camera position, light source information, and other 
 * settings required for rendering, such as the focus distance and ambient light.
 */
typedef struct {
    Vector c, world_d, camera_d; ///< Camera position (C), target point (D), and camera direction
    int dist; ///< Focus distance (d)
    Vector world_i, camera_i; ///< Light source position (I) in world and camera coordinates
    Color1 icolor, a; ///< Light source color and ambient light
} Settings;

/**
 * @struct Transform
 * @brief A structure for storing transformation properties
 * This structure holds the translation, scaling, and rotation information for an object.
 */
typedef struct {
    Vector translate; ///< The translation vector
    int scale; ///< The scaling factor
    Vector rotate; ///< The rotation angles around x, y, and z axes
} Transform;

/**
 * @struct Cube
 * @brief A structure representing a cube
 * This structure defines a cube with its position, color, material properties, 
 * and number of divisions.
 */
typedef struct {
    Vector p1, p2, centroid; ///< Two corner points and the centroid of the cube
    Color255 o; ///< The color of the cube
    int n; ///< The material property index
    double k[3]; ///< Material constants [ambient, diffuse, specular]
    int num; ///< The number of subdivisions of the cube
} Cube;

/**
 * @struct Cylinder
 * @brief A structure representing a cylinder
 * This structure defines a cylinder with its position, radius, height, color, 
 * material properties, and the number of subdivisions.
 */
typedef struct {
    double r, h; ///< The radius and height of the cylinder
    Vector p, centroid; ///< The position and centroid of the cylinder
    Color255 o; ///< The color of the cylinder
    int n; ///< The material property index
    double k[3]; ///< Material constants [ambient, diffuse, specular]
    int div, num; ///< The number of subdivisions and parts of the cylinder
} Cylinder;

/**
 * @struct Sphere
 * @brief A structure representing a sphere
 * This structure defines a sphere with its position, radius, color, 
 * material properties, and the number of subdivisions.
 */
typedef struct {
    double r; ///< The radius of the sphere
    Vector p; ///< The position of the sphere
    Color255 o; ///< The color of the sphere
    int n; ///< The material property index
    double k[3]; ///< Material constants [ambient, diffuse, specular]
    int lat_div, long_div, num; ///< The latitude and longitude subdivisions and parts of the sphere
} Sphere;
