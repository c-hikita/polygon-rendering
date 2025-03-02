/** 
 * @file readFiles.c
 * @brief Functions to read settings and geometric objects from a file, and print out the settings and polygons.
 * 
 * This file includes functions to parse settings such as camera position, ambient light, and various geometric 
 * objects (Cube, Cylinder, Sphere). It also contains utility functions for string searching and printing the 
 * current settings and objects in a human-readable format.
 */

#include <stdio.h>
#include <string.h>

/**
 * @brief Checks if a substring is contained within a string.
 * 
 * This function searches for a specific substring within a line of text. If the substring is found at the beginning
 * of any part of the line, it returns 1, otherwise returns 0.
 *
 * @param line The line of text to be searched.
 * @param substring The substring to search for within the line.
 * @return 1 if substring is found in the line, otherwise 0.
 */
int containsSubstring(const char* line, const char* substring) {
    int sub_len = 0;
    while (substring[sub_len] != '\0') {
        sub_len++;
    }

    while (*line) {
        if (strncmp(line, substring, sub_len) == 0) {
            return 1; 
        }
        line++;
    }
    return 0; 
}

/**
 * @brief Reads settings from a file and stores them in a Settings structure.
 * 
 * This function reads various camera settings, distance, light properties, and other parameters from the provided 
 * file and stores them in the provided Settings structure.
 *
 * @param file The file to read settings from.
 * @param screen Pointer to the Settings structure to store the read values.
 */
void readSettings(FILE* file, Settings* screen) {
    fscanf(file, "camera = (%lf, %lf, %lf)\n", &screen->c.x, &screen->c.y, &screen->c.z);
    fscanf(file, "distance = %d\n", &screen->dist);
    fscanf(file, "ambience = (%lf, %lf, %lf)\n", &screen->a.r, &screen->a.g, &screen->a.b);
    fscanf(file, "iplot = (%lf, %lf, %lf)\n", &screen->world_i.x, &screen->world_i.y, &screen->world_i.z);
    fscanf(file, "icolor = (%lf, %lf, %lf)\n", &screen->icolor.r, &screen->icolor.g, &screen->icolor.b);
}

/**
 * @brief Reads polygon data from a file and stores them in the respective arrays.
 * 
 * This function reads polygon data (Cube, Cylinder, Sphere) from the file, detecting the type of each polygon 
 * and reading the respective properties (like color, size, and position). The data is stored in the appropriate 
 * arrays, and the counts for each polygon type are updated.
 *
 * @param file The file to read polygon data from.
 * @param cubes Array to store Cube objects.
 * @param cubeCount Pointer to store the current number of cubes.
 * @param cylinders Array to store Cylinder objects.
 * @param cylinderCount Pointer to store the current number of cylinders.
 * @param spheres Array to store Sphere objects.
 * @param sphereCount Pointer to store the current number of spheres.
 */
void readPolygons(FILE* file, Cube cubes[MAX_POLYGONS], int* cubeCount, Cylinder cylinders[MAX_POLYGONS], int* cylinderCount, Sphere spheres[MAX_POLYGONS], int* sphereCount) {
    char line[256];
    char currentPolygonType = 0; // 1: Cube, 2: Cylinder, 3: Sphere

    *cubeCount = 0;
    *cylinderCount = 0;
    *sphereCount = 0;

    while (fgets(line, sizeof(line), file)) {
        if (containsSubstring(line, "# Cube")) {
            currentPolygonType = 1;
        } else if (containsSubstring(line, "# Cylinder")) {
            currentPolygonType = 2;
        } else if (containsSubstring(line, "# Sphere")) {
            currentPolygonType = 3;
        }

        // Read cube data
        if (currentPolygonType == 1) {
            fscanf(file, "point1 = (%lf, %lf, %lf)\n", &cubes[*cubeCount].p1.x, &cubes[*cubeCount].p1.y, &cubes[*cubeCount].p1.z);
            fscanf(file, "point2 = (%lf, %lf, %lf)\n", &cubes[*cubeCount].p2.x, &cubes[*cubeCount].p2.y, &cubes[*cubeCount].p2.z);
            fscanf(file, "color = (%d, %d, %d)\n", &cubes[*cubeCount].o.r, &cubes[*cubeCount].o.g, &cubes[*cubeCount].o.b);
            fscanf(file, "n = %d\n", &cubes[*cubeCount].n);
            fscanf(file, "Ka = %lf\n", &cubes[*cubeCount].k[0]);
            fscanf(file, "Kd = %lf\n", &cubes[*cubeCount].k[1]);
            fscanf(file, "Ks = %lf\n", &cubes[*cubeCount].k[2]);

            cubes[*cubeCount].num = 12;
            cubes[*cubeCount].centroid.x = (cubes[*cubeCount].p1.x + cubes[*cubeCount].p2.x) / 2;
            cubes[*cubeCount].centroid.y = (cubes[*cubeCount].p1.y + cubes[*cubeCount].p2.y) / 2;
            cubes[*cubeCount].centroid.z = (cubes[*cubeCount].p1.z + cubes[*cubeCount].p2.z) / 2;

            (*cubeCount)++;
        }

        // Read cylinder data
        if (currentPolygonType == 2) {
            fscanf(file, "radius = %lf\n", &cylinders[*cylinderCount].r);
            fscanf(file, "height = %lf\n", &cylinders[*cylinderCount].h);
            fscanf(file, "position = (%lf, %lf, %lf)\n", &cylinders[*cylinderCount].p.x, &cylinders[*cylinderCount].p.y, &cylinders[*cylinderCount].p.z);
            fscanf(file, "color = (%d, %d, %d)\n", &cylinders[*cylinderCount].o.r, &cylinders[*cylinderCount].o.g, &cylinders[*cylinderCount].o.b);
            fscanf(file, "n = %d\n", &cylinders[*cylinderCount].n);
            fscanf(file, "Ka = %lf\n", &cylinders[*cylinderCount].k[0]);
            fscanf(file, "Kd = %lf\n", &cylinders[*cylinderCount].k[1]);
            fscanf(file, "Ks = %lf\n", &cylinders[*cylinderCount].k[2]);

            cylinders[*cylinderCount].div = 24;
            cylinders[*cylinderCount].num = 4 * cylinders[*cylinderCount].div;

            cylinders[*cylinderCount].centroid = cylinders[*cylinderCount].p;
            cylinders[*cylinderCount].centroid.z += cylinders[*cylinderCount].h / 2;
            
            (*cylinderCount)++;
        }

        // Read sphere data
        if (currentPolygonType == 3) {
            fscanf(file, "radius = %lf\n", &spheres[*sphereCount].r);
            fscanf(file, "position = (%lf, %lf, %lf)\n", &spheres[*sphereCount].p.x, &spheres[*sphereCount].p.y, &spheres[*sphereCount].p.z);
            fscanf(file, "color = (%d, %d, %d)\n", &spheres[*sphereCount].o.r, &spheres[*sphereCount].o.g, &spheres[*sphereCount].o.b);
            fscanf(file, "n = %d\n", &spheres[*sphereCount].n);
            fscanf(file, "Ka = %lf\n", &spheres[*sphereCount].k[0]);
            fscanf(file, "Kd = %lf\n", &spheres[*sphereCount].k[1]);
            fscanf(file, "Ks = %lf\n", &spheres[*sphereCount].k[2]);

            spheres[*sphereCount].lat_div = 20;
            spheres[*sphereCount].long_div = 20;
            (*sphereCount)++;
        }
    }
}

/**
 * @brief Prints the current settings stored in the Settings structure.
 * 
 * This function prints the current camera position, distance, ambient light color, and other relevant settings 
 * stored in the Settings structure.
 *
 * @param screen Pointer to the Settings structure to print values from.
 */
void printSettings(Settings* screen) {
    printf("\nCurrent Settings:\n");
    printf("Camera position: (%.0lf, %.0lf, %.0lf)\n", screen->c.x, screen->c.y, screen->c.z);
    printf("Distance: %d\n", screen->dist);
    printf("Ambient color: (%.2lf, %.2lf, %.2lf)\n", screen->a.r, screen->a.g, screen->a.b);
    printf("I position: (%.0lf, %.0lf, %.0lf)\n", screen->world_i.x, screen->world_i.y, screen->world_i.z);
    printf("I color: (%.2lf, %.2lf, %.2lf)\n", screen->icolor.r, screen->icolor.g, screen->icolor.b);
}

/**
 * @brief Prints the details of all the polygons stored.
 * 
 * This function prints detailed information about all the polygons (Cube, Cylinder, Sphere) stored in their
 * respective arrays, including properties like position, color, and material parameters.
 *
 * @param cubeCount The number of cubes in the system.
 * @param cubes Array of Cube objects.
 * @param cylinderCount The number of cylinders in the system.
 * @param cylinders Array of Cylinder objects.
 * @param sphereCount The number of spheres in the system.
 * @param spheres Array of Sphere objects.
 */
void printPolygons(int cubeCount, Cube cubes[MAX_POLYGONS], int cylinderCount, Cylinder cylinders[MAX_POLYGONS], int sphereCount, Sphere spheres[MAX_POLYGONS]) {
    printf("\nCurrent Primitive:\n");
    for (int i = 0; i < cubeCount; i++) {
        printf("\nCube %d:\n", i + 1);
        printf("p1: (%.0lf, %.0lf, %.0lf) p2: (%.0lf, %.0lf, %.0lf)\n", cubes[i].p1.x, cubes[i].p1.y, cubes[i].p1.z, cubes[i].p2.x, cubes[i].p2.y, cubes[i].p2.z);
        printf("Color: (%d, %d, %d)\n", cubes[i].o.r, cubes[i].o.g, cubes[i].o.b);
        printf("n: %d Ka: %.2lf Kd: %.2lf Ks: %.2lf\n", cubes[i].n, cubes[i].k[0], cubes[i].k[1], cubes[i].k[2]);
    }

    for (int i = 0; i < cylinderCount; i++) {
        printf("\nCylinder %d:\n", i + 1);
        printf("Radius: %.2lf Height: %.2lf Position: (%.0lf, %.0lf, %.0lf)\n", cylinders[i].r, cylinders[i].h, cylinders[i].p.x, cylinders[i].p.y, cylinders[i].p.z);
        printf("Color: (%d, %d, %d)\n", cylinders[i].o.r, cylinders[i].o.g, cylinders[i].o.b);
        printf("n: %d Ka: %.2lf Kd: %.2lf Ks: %.2lf\nDiv: %d\n", cylinders[i].n, cylinders[i].k[0], cylinders[i].k[1], cylinders[i].k[2], cylinders[i].div);
    }

    for (int i = 0; i < sphereCount; i++) {
        printf("\nSphere %d:\n", i + 1);
        printf("Radius: %.2lf Position: (%.0lf, %.0lf, %.0lf)\n", spheres[i].r, spheres[i].p.x, spheres[i].p.y, spheres[i].p.z);
        printf("Color: (%d, %d, %d)\n", spheres[i].o.r, spheres[i].o.g, spheres[i].o.b);
        printf("n: %d Ka: %.2lf Kd: %.2lf Ks: %.2lf\nLatDiv: %d LongDiv: %d\n", spheres[i].n, spheres[i].k[0], spheres[i].k[1], spheres[i].k[2], spheres[i].lat_div, spheres[i].long_div);
    }
}

/**
 * @brief Prints the current transformation values.
 * 
 * This function prints the current transformation parameters such as translation, scale, and rotation stored 
 * in the Transform structure.
 *
 * @param tf The Transform structure containing the current transformation values.
 */
void printTransform(Transform tf) {
    printf("\nCurrent Transformation Values:\n");
    printf("Translation: (%.0f, %.0f, %.0f)\n", tf.translate.x, tf.translate.y, tf.translate.z);
    printf("Scale: %d%%\n", tf.scale);
    printf("Rotation: (%.0f, %.0f, %.0f)\n", tf.rotate.x, tf.rotate.y, tf.rotate.z);
}
