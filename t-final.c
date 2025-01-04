// t-final
// Chikako Hikita

#include "cg.h"
#include "writeBmp.c"
#include "structures.c"
#include "calcVector.c"
#include "rotate.c"
#include "renderTriangle.c"
#include "paintTriangle.c"
#include "drawPrimitive.c"
#include "polygon2Triangle.c"

void main(void) {
	Settings screen;
	screen.width = 640;	screen.height = 480;
	screen.c.x = 200;	screen.c.y = 200; screen.c.z = 100;
	screen.d = 400;
	screen.a.r = 0.7;	screen.a.g = 0.7;	screen.a.b = 0.7;
	screen.iplot.x = 150;	screen.iplot.y = 150;	screen.iplot.z = 100;
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

	Transform tf;
	tf.translate.x = 300;	tf.translate.y = 0;	tf.translate.z = 0;
	tf.scale = 100;
	tf.rotate.x = 0;	tf.rotate.y = 0;	tf.rotate.z = 0;

	// 直方体データ定義
	Cube cube;
	Triangle3D tcube[12];
	cube.p1.x = 200;	cube.p1.y = 200;	cube.p1.z = 200;
	cube.p2.x = 300;	cube.p2.y = 300;	cube.p2.z = 300;
	cube.o.r = 200;	cube.o.g = 200;	cube.o.b = 255;
	cube.n = 9;
	cube.k[0] = 0.5;	cube.k[1] = 0.5;	cube.k[2] = 0.5;
	cube.num = 12;

	// 円柱データ定義
	Cylinder cylinder;
	Triangle3D tcylinder[500];
	cylinder.r = 100;	cylinder.h = 100;
	cylinder.p.x = 200;	cylinder.p.y = 200;	cylinder.p.z = 200;
	cylinder.o.r = 200;	cylinder.o.g = 200;	cylinder.o.b = 255;
	cylinder.n = 9;
	cylinder.k[0] = 0.5;	cylinder.k[1] = 0.5;	cylinder.k[2] = 0.5;
	cylinder.div = 60;		
	cylinder.num = 4 * cylinder.div;

	// shpere
	Sphere sphere;
	Triangle3D tsphere[2000];
	sphere.r = 100;
	sphere.p.x = 200;	sphere.p.y = 200;	sphere.p.z = 250;
	sphere.o.r = 200;	sphere.o.g = 200;	sphere.o.b = 255;
	sphere.n = 9;
	sphere.k[0] = 0.5;	sphere.k[1] = 0.5;	sphere.k[2] = 0.5;
	sphere.lat_div = 24;		sphere.long_div = 24;
	// sphere.num = sphere.lat_div + sphere.long_div + sphere.lat_div * (sphere.long_div - 2) * 2;

	// printf("num: %d\n", sphere.num);

	background(screen.width, screen.height);
	// cube2triangle(tcube, cube, tf);
	// drawPrimitive(cube.num, tcube, screen);

	cylinder2triangle(tcylinder, cylinder, tf);
	drawPrimitive(cylinder.num, tcylinder, screen);

	// sphere.num = sphere2triangle(tsphere, sphere);
	// drawPrimitive(sphere.num, tsphere, screen);

	// 24ビット-ビットマップファイルへの書き込み
	bmpout("sample.bmp", screen.width, screen.height);
}