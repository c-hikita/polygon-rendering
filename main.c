/**
 * @file main.c
 * @brief Main entry point for the Polygon Rendering Software.
 *
 * This program reads polygon data from files, applies transformations,
 * and renders 3D objects using polygon-to-triangle conversion and
 * a Z-buffer-based rendering approach. The user can modify camera
 * settings, scale, translation, and rotation via a menu system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POLYGONS 2
#define MAX_TRIANGLES 3000
#define WIDTH 640
#define HEIGHT 480
#define SIZE 4

double ZBuffer[HEIGHT][WIDTH];

#include "cg.h"
#include "writeBmp.c"
#include "structures.c"
#include "readFiles.c"
#include "calcVector.c"
#include "rotate.c"
#include "world2Camera.c"
#include "polygon2Triangle.c"
#include "renderTriangle.c"
#include "paintTriangle.c"
#include "drawPrimitive.c"

/**
 * @brief Main function for initializing and running the rendering program.
 *
 * This function loads settings and polygon data, initializes transformations,
 * computes centroids, and provides a user interface for rendering and modifying
 * the scene. The rendering process involves:
 * 1. Reading settings and polygon data.
 * 2. Computing transformations.
 * 3. Converting polygons to triangles.
 * 4. Rendering the triangles.
 * 5. Allowing user interaction through a menu.
 *
 * @return 0 on successful execution, 1 if file loading fails.
 */
int main() {
    Settings screen;
    Cube cubes[MAX_POLYGONS];
    Cylinder cylinders[MAX_POLYGONS];
    Sphere spheres[MAX_POLYGONS];
    Transform tf;
    Triangle3D tri[MAX_TRIANGLES];
    int triCount, cubeCount = 0, cylinderCount = 0, sphereCount = 0;
    int menu, quit;
    double step;
    Vector centroid, tmp[2];

    printf("***Polygon Rendering Software***\n");

    // Open settings and polygon files
    FILE* settingsFile = fopen("settings.txt", "r");
    FILE* polygonsFile = fopen("polygons.txt", "r");

    if (!settingsFile || !polygonsFile) {
        perror("Failed to open file");
        return 1;
    }

    // Read settings and polygon data
    readSettings(settingsFile, &screen);
    printSettings(&screen);
    fclose(settingsFile);

    readPolygons(polygonsFile, cubes, &cubeCount, cylinders, &cylinderCount, spheres, &sphereCount);
    fclose(polygonsFile);
    printPolygons(cubeCount, cubes, cylinderCount, cylinders, sphereCount, spheres);

    // Initialize transformation parameters
    tf.translate.x = 0; tf.translate.y = 0; tf.translate.z = 0;
    tf.scale = 100;
    tf.rotate.x = 0; tf.rotate.y = 0; tf.rotate.z = 0;

    // Compute centroid of all polygons
    centroid.x = centroid.y = centroid.z = 0;
    for (int i = 0; i < cubeCount; i++) centroid = add(centroid, cubes[i].centroid);
    for (int i = 0; i < cylinderCount; i++) centroid = add(centroid, cylinders[i].centroid);
    for (int i = 0; i < sphereCount; i++) centroid = add(centroid, spheres[i].p);
    centroid = divide(centroid, cubeCount + cylinderCount + sphereCount);
    screen.world_d = centroid;

    // Display menu options
    printf("\nMenu\n");
    printf("0: Quit\n");
    printf("1: Start painting\n");
    printf("2: Update camera position\n");
    printf("3: Update scale\n");
    printf("4: Update translation values\n");
    printf("5: Update rotation values\n");
    printf("6: Show menu\n");

    quit = 0;
    while (1) {
        printf("\n> ");
        scanf("%d", &menu);
        printf("\n");

        switch (menu) {
            case 0:
                quit = 1;
                break;
            case 1:
                printf("Painting...\n");
                background();

                // Transform world to camera coordinates
                tmp[0] = screen.world_d;
                tmp[1] = screen.world_i;
                world2Camera(tmp, screen, 2);
                screen.camera_d = tmp[0];
                screen.camera_i = tmp[1];

                // Initialize and generate triangles
                triCount = 0;
                initializeTriangles(tri, MAX_TRIANGLES);
                for (int i = 0; i < cubeCount; i++) triCount += cube2triangle(tri, cubes[i], screen, tf, triCount);
                for (int i = 0; i < cylinderCount; i++) triCount += cylinder2triangle(tri, cylinders[i], screen, tf, triCount);
                for (int i = 0; i < sphereCount; i++) triCount += sphere2triangle(tri, spheres[i], screen, tf, triCount);

                // Render and output image
                drawPrimitive(triCount, tri, screen);
                bmpout("output.bmp", WIDTH, HEIGHT);
                break;
            case 2:
                printf("Enter new camera position [x, y, z]> ");
                scanf("%lf, %lf, %lf", &screen.c.x, &screen.c.y, &screen.c.z);
                break;
            case 3:
                printf("Enter new scale [%%]>");
                scanf("%d", &tf.scale);
                break;
            case 4:
                printf("Enter new translation values [x, y, z]> ");
                scanf("%lf, %lf, %lf", &tf.translate.x, &tf.translate.y, &tf.translate.z);
                break;
            case 5:
                printf("Enter new rotation values in degrees[x, y, z]> ");
                scanf("%lf, %lf, %lf", &tf.rotate.x, &tf.rotate.y, &tf.rotate.z);
                break;
            case 6:
                printf("\nMenu\n");
                printf("0: Quit\n");
                printf("1: Start painting\n");
                printf("2: Update camera position\n");
                printf("3: Update scale\n");
                printf("4: Update translation values\n");
                printf("5: Update rotation values\n");
                printf("6: Show menu\n");
                break;
            default:
                printf("Invalid input. Please try again.\n");
                break;
        }

        if (quit == 1) {
            printf("\nExiting program...\n");
            break;
        }
    }

    return 0;
}
