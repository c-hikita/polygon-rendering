// t-final
// Chikako Hikita

#include "cg.h"
#include "writeBmp.c"
#include "structures.c"
#include "calcVector.c"
#include "renderTriangle.c"
#include "paintTriangle.c"
#include "drawPrimitive.c"
#include "polygon2Triangle.c"

void main(void) {
	Settings screen;
	screen.width = 640;	screen.height = 480;
	screen.c.x = 300;	screen.c.y = 300; screen.c.z = 0;
	screen.d = 200;
	screen.a.r = 0.7;	screen.a.g = 0.7;	screen.a.b = 0.7;
	screen.iplot.x = 100;	screen.iplot.y = 200;	screen.iplot.z = 80;
	screen.icolor.r = 1;	screen.icolor.g = 1;	screen.icolor.b = 1;

	// sample triangles
	/*
	Triangle3D t[6];
	int num = 6;

	t[0].p[0].x = 50; 	t[0].p[0].y = 50;	t[0].p[0].z = 200;
	t[0].p[1].x = 100; 	t[0].p[1].y = 150;	t[0].p[1].z = 200;
	t[0].p[2].x = 150; 	t[0].p[2].y = 50;	t[0].p[2].z = 200;

	t[1].p[0].x = 100; 	t[1].p[0].y = 200;	t[1].p[0].z = 200;
	t[1].p[1].x = 50; 	t[1].p[1].y = 300;	t[1].p[1].z = 200;
	t[1].p[2].x = 150; 	t[1].p[2].y = 300;	t[1].p[2].z = 200;
	
	t[2].p[0].x = 200; 	t[2].p[0].y = 50;	t[2].p[0].z = 200;
	t[2].p[1].x = 250; 	t[2].p[1].y = 150;	t[2].p[1].z = 200;
	t[2].p[2].x = 350; 	t[2].p[2].y = 200;	t[2].p[2].z = 200;

	t[3].p[0].x = 350; 	t[3].p[0].y = 100;	t[3].p[0].z = 200;
	t[3].p[1].x = 400; 	t[3].p[1].y = 150;	t[3].p[1].z = 200;
	t[3].p[2].x = 450; 	t[3].p[2].y = 50;	t[3].p[2].z = 200;

	t[4].p[0].x = 250; 	t[4].p[0].y = 200;	t[4].p[0].z = 200;
	t[4].p[1].x = 200; 	t[4].p[1].y = 300;	t[4].p[1].z = 200;
	t[4].p[2].x = 300; 	t[4].p[2].y = 250;	t[4].p[2].z = 200;

	t[5].p[0].x = 350; 	t[5].p[0].y = 250;	t[5].p[0].z = 200;
	t[5].p[1].x = 450; 	t[5].p[1].y = 300;	t[5].p[1].z = 200;
	t[5].p[2].x = 400; 	t[5].p[2].y = 200;	t[5].p[2].z = 200;

	for (int i = 0; i < num; i++) {
		t[i].o.r = 200;	t[i].o.g = 200;	t[i].o.b = 255;
		t[i].n = 9;
		t[i].k[0] = 0.5;	t[i].k[1] = 0.5;	t[i].k[2] = 0.5;
	}
	*/
	
	// 直方体データ定義
	Cube cube;
	Triangle3D tcube[12];
	cube.x1 = 300;	cube.y1 = 300;	cube.z1 = 300;
	cube.x2 = 200;	cube.y2 = 400;	cube.z2 = 350;
	cube.o.r = 200;	cube.o.g = 200;	cube.o.b = 255;
	cube.n = 9;
	cube.k[0] = 0.5;	cube.k[1] = 0.5;	cube.k[2] = 0.5;
	cube.num = 12;

	background(screen.width, screen.height);
	cube2triangle(tcube, cube);
	drawPrimitive(cube.num, tcube, screen);

	// 24ビット-ビットマップファイルへの書き込み
	bmpout("sample.bmp", screen.width, screen.height);
}