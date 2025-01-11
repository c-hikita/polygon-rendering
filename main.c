﻿// main.c
// Chikako Hikita

#define MAX_POLYGONS 2
#define MAX_TRIANGLES 3000

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	Vector centroid, tmp[1], offset;

	// Vector input;
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
	for (int i = 0; i < cubeCount; i++) centroid = cubeCentroid(centroid, cubes[i]);
	// for (int i = 0; i < cylinderCount; i++) centroid = cylinderCentroid(centroid, cylinders[i]);
	// for (int i = 0; i < sphereCount; i++) centroid = sphereCentroid(centroid, spheres[i]);

	offset.x = 100;	
	offset.y = 100;
	offset.z = 100;

	// step = 300;
	// screen.d = movePointCloser(centroid, screen.c, step);
	// screen.d = subtract(centroid, offset);
	screen.d = centroid;
	// screen.d.x = 100; screen.d.y = 100; screen.d.z = 100;
	printf("screen.d: (%.0lf, %.0lf, %.0lf)\n", centroid.x, centroid.y, centroid.z);
	
	tmp[0] = screen.iplot;
	world2Camera(tmp, screen, 1);
	screen.iplot = tmp[0];
	printf("Iplot (main): (%.0lf, %.0lf, %.0lf)\n", screen.iplot.x, screen.iplot.y, screen.iplot.z);

	quit = 0;
	while (1) {
		printf("\nMenu\n");
		printf("0: Quit\n");
		printf("1: Start painting\n");
		printf("2: Update camera position\n");
		printf("3: Update transformation values\n");

		printf("\n> ");
		scanf("%d", &menu);
		printf("\n");

		switch (menu) {
			case 0:
				quit = 1;
				break;
			case 1:
				printf("Painting...\n");
				background(screen.width, screen.height);

				triCount = 0;
				initializeTriangles(tri, MAX_TRIANGLES);

				for (int i = 0; i < cubeCount; i++) triCount += cube2triangle(tri, cubes[i], screen, tf, centroid, triCount);
				// for (int i = 0; i < cylinderCount; i++) triCount += cylinder2triangle(tri, cylinders[i], tf,  centroid, triCount);
				// for (int i = 0; i < sphereCount; i++) triCount += sphere2triangle(tri, spheres[i], tf,  centroid, triCount);

				drawPrimitive(triCount, tri, screen);
				bmpout("output.bmp", screen.width, screen.height);

				break;
			case 2:
    			printf("Current camera position: (%.0lf, %.0lf, %.0lf)\n", screen.c.x, screen.c.y, screen.c.z);
				printf("Enter new camera position (x y z)> ");
				scanf("%lf %lf %lf", &screen.c.x, &screen.c.y, &screen.c.z);
				break;
			case 3:
				printf("Enter scale (in %%) >");
				scanf("%d", &tf.scale);

				printf("Enter translation values (x y z)> ");
				scanf("%lf %lf %lf", &tf.translate.x, &tf.translate.y, &tf.translate.z);

				printf("Enter rotation angles (x y z in degrees)> ");
				scanf("%lf %lf %lf", &tf.rotate.x, &tf.rotate.y, &tf.rotate.z);

				printTransform(tf);
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
