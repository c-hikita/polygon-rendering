// polygon2Triangle
// Chikako Hikita

void cube2triangle(Triangle3D t[], Cube c) {
	printf("\n*** cube2triangle ***\n");

	Vector vertex[8];

	vertex[0].x = c.x2;	vertex[0].y = c.y1;	vertex[0].z = c.z1;
	vertex[1].x = c.x1;	vertex[1].y = c.y1;	vertex[1].z = c.z1;
	vertex[2].x = c.x1;	vertex[2].y = c.y2;	vertex[2].z = c.z1;
	vertex[3].x = c.x2;	vertex[3].y = c.y2;	vertex[3].z = c.z1;
	vertex[4].x = c.x2;	vertex[4].y = c.y1;	vertex[4].z = c.z2;
	vertex[5].x = c.x1;	vertex[5].y = c.y1;	vertex[5].z = c.z2;
	vertex[6].x = c.x1;	vertex[6].y = c.y2;	vertex[6].z = c.z2;
	vertex[7].x = c.x2;	vertex[7].y = c.y2;	vertex[7].z = c.z2;

	t[0].p[0] = vertex[2];	t[0].p[1] = vertex[1];	t[0].p[2] = vertex[0];
	t[1].p[0] = vertex[0];	t[1].p[1] = vertex[3];	t[1].p[2] = vertex[2];
	t[2].p[0] = vertex[4];	t[2].p[1] = vertex[6];	t[2].p[2] = vertex[7];
	t[3].p[0] = vertex[6];	t[3].p[1] = vertex[4];	t[3].p[2] = vertex[5];
	t[4].p[0] = vertex[0];	t[4].p[1] = vertex[5];	t[4].p[2] = vertex[4];
	t[5].p[0] = vertex[5];	t[5].p[1] = vertex[0];	t[5].p[2] = vertex[1];
	t[6].p[0] = vertex[2];	t[6].p[1] = vertex[7];	t[6].p[2] = vertex[6];
	t[7].p[0] = vertex[7];	t[7].p[1] = vertex[2];	t[7].p[2] = vertex[3];
	t[8].p[0] = vertex[0];	t[8].p[1] = vertex[3];	t[8].p[2] = vertex[7];
	t[9].p[0] = vertex[7];	t[9].p[1] = vertex[4];	t[9].p[2] = vertex[0];
	t[10].p[0] = vertex[1];	t[10].p[1] = vertex[6];	t[10].p[2] = vertex[5];
	t[11].p[0] = vertex[6];	t[11].p[1] = vertex[1];	t[11].p[2] = vertex[2];

	for (int i = 0; i < 12; i++) {
		t[i].o = c.o;
		t[i].n = c.n;
		t[i].k[0] = c.k[0];
		t[i].k[1] = c.k[1];
		t[i].k[2] = c.k[2];

		t[i].g.x = (t[i].p[0].x + t[i].p[1].x + t[i].p[2].x) / 3;
		t[i].g.y = (t[i].p[0].y + t[i].p[1].y + t[i].p[2].y) / 3;
		t[i].g.z = (t[i].p[0].z + t[i].p[1].z + t[i].p[2].z) / 3;
	}
}

void cylinder2triangle(Triangle3D t[], Cylinder c) {
	printf("\n*** cylinder2triangle ***\n");
	// trying with 12 (change div in t-step[2])

	Vector o1, o2, vertex[24];
	double theta;

	o1.x = c.x;		o1.y = c.y;		o1.z = c.z;
	o2.x = c.x;		o2.y = c.y;		o2.z = c.z + c.h;

	theta = 2 * PI / c.div;
	printf("theta: %.4lf\n", theta);

	for (int i = 0; i < c.div; i++) {
		vertex[i].x = c.x + (int) (c.r * cos(theta * i));
		vertex[i].y = c.y + (int) (c.r * sin(theta * i));
		vertex[i].z = c.z;

		vertex[i + 12].x = vertex[i].x;
		vertex[i + 12].y = vertex[i].y;
		vertex[i + 12].z = c.z + c.h;
	}
	printf("\n");
	for (int i = 0; i < c.div * 2; i++) {
		printf("vertex[%d]: (%.3lf, %.3lf, %.3lf)\n", i, vertex[i].x, vertex[i].y, vertex[i].z);
	}
	
	printf("\n");
	// 底面（上下）
	for (int i = 0; i < c.div; i++) {
		int next;

		if (i < c.div - 1) next = i + 1;
		else next = 0;

		// if (i == c.div - 1) printf("next: %d\n", next);

		// 底面（下0-11, 上12-23）
		t[i].p[0] = o1;		t[i].p[1] = vertex[next];			t[i].p[2] = vertex[i];
		t[i + 12].p[0] = o2;	t[i + 12].p[1] = vertex[i + 12];	t[i + 12].p[2] = vertex[next + 12];

		/*
		printf("triangle[%d]: (%d, %d, %d) (%d, %d, %d) (%d, %d, %d)\n",
			i, t[i].p[0].x, t[i].p[0].y, t[i].p[0].z, t[i].p[1].x, t[i].p[1].y, t[i].p[1].z, t[i].p[2].x, t[i].p[2].y, t[i].p[2].z);
		*/

		// 側面（24-35, 36-47)
		// t[i + 24].p[0] = vertex[i];	t[i + 24].p[1] = vertex[next];		t[i + 24].p[2] = vertex[next + 12];
		// t[i + 36].p[0] = vertex[i];	t[i + 36].p[1] = vertex[next + 12];	t[i + 36].p[2] = vertex[i + 12];

		t[i + 24].p[0] = vertex[i];	t[i + 24].p[1] = vertex[next];		t[i + 24].p[2] = vertex[next + 12];
		t[i + 36].p[0] = vertex[i];	t[i + 36].p[1] = vertex[next + 12];	t[i + 36].p[2] = vertex[i + 12];
	}

	/*
	0 13 1
	6 19 7
	7 20 8
	8 21
	9 22
	10 23
	11 12

	0 12 13
	6 18 19
	7 19 20
	8 20 21
	9 21 22
	10 22 23
	11 23 12

	
	*/
	
	// printf("\n");
	for (int i = 0; i < c.num; i++) { 
		t[i].o = c.o;
		t[i].n = c.n;
		t[i].k[0] = c.k[0];
		t[i].k[1] = c.k[1];
		t[i].k[2] = c.k[2];

		t[i].g.x = (t[i].p[0].x + t[i].p[1].x + t[i].p[2].x) / 3;
		t[i].g.y = (t[i].p[0].y + t[i].p[1].y + t[i].p[2].y) / 3;
		t[i].g.z = (t[i].p[0].z + t[i].p[1].z + t[i].p[2].z) / 3;

		// printf("g[%d]: (%.2lf, %.2lf, %.2lf)\n", i, t[i].g.x, t[i].g.y, t[i].g.z);
	}
}
