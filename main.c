// main.c
// Chikako Hikita

#define MAX_POLYGONS 2
#define MAX_TRIANGLES 3000

#include "cg.h"
#include "writeBmp.c"
#include "structures.c"
#include "readFiles.c"
#include "calcVector.c"
#include "rotate.c"
#include "renderTriangle.c"
#include "paintTriangle.c"
#include "drawPrimitive.c"
#include "polygon2Triangle.c"

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
    int cubeCount = 0, cylinderCount = 0, sphereCount = 0, triCount = 0;;
	int menu, quit;
	Vector centroid;

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

	quit = 0;
	while (1) {
		printf("\nMenu\n");
		printf("0: Quit\n");
		printf("1: Start painting\n");
		printf("2: Update camera point\n");
		printf("3: Update transformation values\n");

		printf("\n> ");
		scanf("%d", &menu);

		switch (menu) {
			case 0:
				quit = 1;
				break;
			case 1:
				printf("Painting...\n");
				background(screen.width, screen.height);

				centroid.x = 0;	centroid.y = 0;	centroid.z = 0;
				for (int i = 0; i < cubeCount; i++) centroid = cubeCentroid(centroid, cubes[i]);
				for (int i = 0; i < cylinderCount; i++) centroid = cylinderCentroid(centroid, cylinders[i]);
				for (int i = 0; i < sphereCount; i++) centroid = sphereCentroid(centroid, spheres[i]);

				for (int i = 0; i < cubeCount; i++) triCount += cube2triangle(tri, cubes[i], tf, centroid, triCount);
				for (int i = 0; i < cylinderCount; i++) triCount += cylinder2triangle(tri, cylinders[i], tf,  centroid, triCount);
				for (int i = 0; i < sphereCount; i++) triCount += sphere2triangle(tri, spheres[i], tf,  centroid, triCount);

				drawPrimitive(triCount, tri, screen);
				bmpout("output.bmp", screen.width, screen.height);

				break;
			case 2:
				printf("Enter new camera point (x,y,z)> ");
				scanf("%lf,%lf,%lf", &screen.c.x, &screen.c.y, &screen.c.z);
				break;
			case 3:
				printf("Enter scale (in %%) >");
				scanf("%d", &tf.scale);

				printf("Enter translation values (x,y,z)> ");
				scanf("%lf,%lf,%lf", &tf.translate.x, &tf.translate.y, &tf.translate.z);

				printf("Enter rotation angles (x,y,z in degrees)> ");
				scanf("%lf,%lf,%lf", &tf.rotate.x, &tf.rotate.y, &tf.rotate.z);

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

    
    // Now you can use the data in cubes, cylinders, and spheres for rendering or further processing
    return 0;
}


/*
void main(void) {
	Settings screen;
	screen.width = 640;	screen.height = 480;
	screen.c.x = 300;	screen.c.y = 300; screen.c.z = 100;
	screen.d = 400;
	screen.a.r = 0.8;	screen.a.g = 0.8;	screen.a.b = 0.8;
	screen.iplot.x = 200;	screen.iplot.y = 200;	screen.iplot.z = 100;
	screen.icolor.r = 1;	screen.icolor.g = 1;	screen.icolor.b = 1;

	Transform tf;
	tf.translate.x = 0;	tf.translate.y = 0;	tf.translate.z = 0;
	tf.scale = 100;
	tf.rotate.x = 0;	tf.rotate.y = 0;	tf.rotate.z = 0;

	Triangle3D tri[3000];
	Vector centroid;
	int tnum = 0;

	// 直方体データ定義
	Cube cube;
	// Triangle3D tcube[12];
	cube.p1.x = 300;	cube.p1.y = 300;	cube.p1.z = 200;
	cube.p2.x = 400;	cube.p2.y = 400;	cube.p2.z = 300;
	cube.o.r = 200;		cube.o.g = 0;		cube.o.b = 200;
	cube.n = 9;
	cube.k[0] = 0.5;	cube.k[1] = 0.5;	cube.k[2] = 0.5;
	cube.num = 12;

	// 円柱データ定義
	Cylinder cylinder;
	// Triangle3D tcylinder[1000];
	cylinder.r = 100;	cylinder.h = 200;
	cylinder.p.x = 200;	cylinder.p.y = 200;	cylinder.p.z = 300;
	cylinder.o.r = 200;	cylinder.o.g = 200;	cylinder.o.b = 255;
	cylinder.n = 9;
	cylinder.k[0] = 0.7;	cylinder.k[1] = 0.7;	cylinder.k[2] = 0.7;
	cylinder.div = 30;		
	cylinder.num = 4 * cylinder.div;

	// shpere
	Sphere sphere;
	// Triangle3D tsphere[2000];
	sphere.r = 100;
	sphere.p.x = 500;	sphere.p.y = 200;	sphere.p.z = 300;
	sphere.o.r = 0;		sphere.o.g = 200;	sphere.o.b = 200;
	sphere.n = 9;
	sphere.k[0] = 0.5;	sphere.k[1] = 0.5;	sphere.k[2] = 0.5;
	sphere.lat_div = 20;		sphere.long_div = 20;
	// sphere.num = sphere.lat_div + sphere.long_div + sphere.lat_div * (sphere.long_div - 2) * 2;

	// printf("num: %d\n", sphere.num);

	background(screen.width, screen.height);

	centroid.x = 0;	centroid.y = 0;	centroid.z = 0;
	centroid = cubeCentroid(centroid, cube);
	printf("centroid: (%.3lf %.3lf %.3lf)\n", centroid.x, centroid.y, centroid.z);

	centroid = cylinderCentroid(centroid, cylinder);
	printf("centroid: (%.3lf %.3lf %.3lf)\n", centroid.x, centroid.y, centroid.z);

	centroid = sphereCentroid(centroid, sphere);
	printf("centroid: (%.3lf %.3lf %.3lf)\n", centroid.x, centroid.y, centroid.z);

	// cube2triangle(tcube, cube, tf);
	// drawPrimitive(cube.num, tcube, screen);

	// cylinder2triangle(tcylinder, cylinder, tf);
	// drawPrimitive(cylinder.num, tcylinder, screen);

	// sphere.num = sphere2triangle(tsphere, sphere, tf);
	// drawPrimitive(sphere.num, tsphere, screen);

	tnum += cube2triangle(tri, cube, tf, centroid, tnum);
	printf("tnum: %d\n", tnum);
	tnum += cylinder2triangle(tri, cylinder, tf,  centroid, tnum);
	printf("tnum: %d\n", tnum);
	tnum += sphere2triangle(tri, sphere, tf,  centroid, tnum);
	printf("tnum: %d\n", tnum);

	drawPrimitive(tnum, tri, screen);

	// 24ビット-ビットマップファイルへの書き込み
	bmpout("sample.bmp", screen.width, screen.height);
}
*/