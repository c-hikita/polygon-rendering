#include <stdio.h>   // Standard input/output library
#include <process.h> // Process control functions (platform-dependent)
#include <math.h>    // Math functions (e.g., trigonometric functions, power, sqrt)

#define PI 3.14159265 // Define the value of Pi with high precision

/* BMP file-related data types */
typedef unsigned short WORD;  // Defines a 16-bit unsigned integer
typedef unsigned int DWORD;   // Defines a 32-bit unsigned integer

/* Bitmap Data Definitions */
#define Y_SIZE 1024 // Image height in pixels
#define X_SIZE 1024 // Image width in pixels

// 3D array to store pixel data (RGB values) for a 1024x1024 image
unsigned char Pixel[Y_SIZE][X_SIZE][3];
