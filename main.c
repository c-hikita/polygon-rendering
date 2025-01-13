// main.c
// Chikako Hikita

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POLYGONS 2
#define MAX_TRIANGLES 3000
#define WIDTH 640
#define HEIGHT 480

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

	FILE* settingsFile = fopen("settings.txt", "r");
    FILE* polygonsFile = fopen("polygons.txt", "r");

    if (!settingsFile || !polygonsFile) {
        perror("Failed to open file");
        return 1;
    }

    readSettings(settingsFile, &screen);
	printSettings(&screen);
    fclose(settingsFile);

    readPolygons(polygonsFile, cubes, &cubeCount, cylinders, &cylinderCount, spheres, &sphereCount);
    fclose(polygonsFile);
	printPolygons(cubeCount, cubes, cylinderCount, cylinders, sphereCount, spheres);

	tf.translate.x = 0;	tf.translate.y = 0;	tf.translate.z = 0;
	tf.scale = 100;
	tf.rotate.x = 0;	tf.rotate.y = 0;	tf.rotate.z = 0;

	centroid.x = 0;	centroid.y = 0;	centroid.z = 0;
	for (int i = 0; i < cubeCount; i++) centroid = add(centroid, cubes[i].centroid);
	for (int i = 0; i < cylinderCount; i++) centroid = add(centroid, cylinders[i].centroid);
	for (int i = 0; i < sphereCount; i++) centroid = add(centroid, spheres[i].p);

	centroid = divide(centroid, cubeCount + cylinderCount + sphereCount);
	screen.world_d = centroid;

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
			
				tmp[0] = screen.world_d;
				tmp[1] = screen.world_i;
				world2Camera(tmp, screen, 2);
				screen.camera_d = tmp[0];
				screen.camera_i = tmp[1];

				triCount = 0;
				initializeTriangles(tri, MAX_TRIANGLES);

				for (int i = 0; i < cubeCount; i++) triCount += cube2triangle(tri, cubes[i], screen, tf, triCount);
				for (int i = 0; i < cylinderCount; i++) triCount += cylinder2triangle(tri, cylinders[i], screen, tf, triCount);
				for (int i = 0; i < sphereCount; i++) triCount += sphere2triangle(tri, spheres[i], screen, tf, triCount);

				drawPrimitive(triCount, tri, screen);
				bmpout("output.bmp", WIDTH, HEIGHT);

				break;
			case 2:
    			printf("Current camera position: (%.0lf, %.0lf, %.0lf)\n", screen.c.x, screen.c.y, screen.c.z);
				printf("Enter new camera position [x, y, z]> ");
				scanf("%lf, %lf, %lf", &screen.c.x, &screen.c.y, &screen.c.z);
				break;
			case 3:
			    printf("Current scale: %d%%\n", tf.scale);
				printf("Enter new scale >");
				scanf("%d", &tf.scale);
				break;
			case 4:
			    printf("Current translation values: (%.0lf, %.0lf, %.0lf)\n", tf.translate.x, tf.translate.y, tf.translate.z);
				printf("Enter new translation values [x, y, z]> ");
				scanf("%lf, %lf, %lf", &tf.translate.x, &tf.translate.y, &tf.translate.z);
				break;
			case 5:
			    printf("Current rotation angles: x: %.0lf° y: %.0lf° z: %.0lf°\n", tf.rotate.x, tf.rotate.y, tf.rotate.z);
				printf("Enter new translation values [x, y, z]> ");
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