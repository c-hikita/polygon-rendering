// t-final
// Chikako Hikita

#include "cg.h"
#include "writeBmp.c"
#include "structures.c"
#include "calcVector.c"
#include "renderTriangle.c"
#include "paintTriangle.c"

void main(void) {
	Settings screen;
	screen.width = 640;	screen.height = 480;
	screen.c.x = 300;	screen.c.y = 300; screen.c.z = 0;
	screen.d = 200;
	screen.a.r = 0.7;	screen.a.g = 0.7;	screen.a.b = 0.7;
	screen.iplot.x = 100;	screen.iplot.y = 200;	screen.iplot.z = 80;
	screen.icolor.r = 1;	screen.icolor.g = 1;	screen.icolor.b = 1;

	Triangle3D t[6];
	Rendered rendered;

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

	background(screen.width, screen.height);

	for (int i = 0; i < 6; i++) {
		printf("\ntriangle %d\n", i);
		t[i].o.r = 200;	t[i].o.g = 200;	t[i].o.b = 255;
		t[i].n = 9;
		t[i].k[0] = 0.5;	t[i].k[1] = 0.5;	t[i].k[2] = 0.5;

		t[i].g.x = (t[i].p[0].x + t[i].p[1].x + t[i].p[2].x)/3;
		t[i].g.y = (t[i].p[0].y + t[i].p[1].y + t[i].p[2].y)/3;
		t[i].g.z = (t[i].p[0].z + t[i].p[1].z + t[i].p[2].z)/3;

		rendered = renderTriangle(t[i], screen);

		printf("rendered:\n");
		printf("(r,g,b) = (%d, %d, %d)\n\n", rendered.cp[2].c.r, rendered.cp[2].c.g, rendered.cp[2].c.b);		
		paintTriangle(screen.width, screen.height, rendered);
	}

	// 24ビット-ビットマップファイルへの書き込み
	bmpout("sample.bmp", screen.width, screen.height);
}