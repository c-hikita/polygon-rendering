﻿// polygon2Triangle
// Chikako Hikita

void cube2triangle(Triangle3D t[], Cube c) {
	printf("\n*** cube2triangle ***\n");

	Vector vertex[8];

	c.centroid.x = (c.p1.x + c.p2.x) / 2;
	c.centroid.y = (c.p1.y + c.p2.y) / 2;
	c.centroid.z = (c.p1.z + c.p2.z) / 2;

	// printf("centroid: (%.3lf, %.3lf, %.3lf)\n", c.centroid.x, c.centroid.y, c.centroid.z);
	// printf("p1: (%.3lf, %.3lf, %.3lf)\n", c.p1.x, c.p1.y, c.p1.z); 		

	vertex[0].x = c.p1.x;	vertex[0].y = c.p1.y;	vertex[0].z = c.p2.z;
	vertex[1].x = c.p1.x;	vertex[1].y = c.p1.y;	vertex[1].z = c.p1.z;
	vertex[2].x = c.p2.x;	vertex[2].y = c.p1.y;	vertex[2].z = c.p1.z;
	vertex[3].x = c.p2.x;	vertex[3].y = c.p1.y;	vertex[3].z = c.p2.z;
	vertex[4].x = c.p1.x;	vertex[4].y = c.p2.y;	vertex[4].z = c.p2.z;
	vertex[5].x = c.p1.x;	vertex[5].y = c.p2.y;	vertex[5].z = c.p1.z;
	vertex[6].x = c.p2.x;	vertex[6].y = c.p2.y;	vertex[6].z = c.p1.z;
	vertex[7].x = c.p2.x;	vertex[7].y = c.p2.y;	vertex[7].z = c.p2.z;

	t[0].p[0] = vertex[0];	t[0].p[1] = vertex[4];	t[0].p[2] = vertex[7];
	t[1].p[0] = vertex[7];	t[1].p[1] = vertex[3];	t[1].p[2] = vertex[0];
	t[2].p[0] = vertex[1];	t[2].p[1] = vertex[2];	t[2].p[2] = vertex[6];
	t[3].p[0] = vertex[6];	t[3].p[1] = vertex[5];	t[3].p[2] = vertex[1];
	t[4].p[0] = vertex[0];	t[4].p[1] = vertex[1];	t[4].p[2] = vertex[5];
	t[5].p[0] = vertex[5];	t[5].p[1] = vertex[4];	t[5].p[2] = vertex[0];
	t[6].p[0] = vertex[3];	t[6].p[1] = vertex[7];	t[6].p[2] = vertex[6];
	t[7].p[0] = vertex[6];	t[7].p[1] = vertex[2];	t[7].p[2] = vertex[3];
	t[8].p[0] = vertex[0];	t[8].p[1] = vertex[3];	t[8].p[2] = vertex[2];
	t[9].p[0] = vertex[2];	t[9].p[1] = vertex[1];	t[9].p[2] = vertex[0];
	t[10].p[0] = vertex[4];	t[10].p[1] = vertex[5];	t[10].p[2] = vertex[6];
	t[11].p[0] = vertex[6];	t[11].p[1] = vertex[7];	t[11].p[2] = vertex[4];

	for (int i = 0; i < 12; i++) {
		t[i].o = c.o;
		t[i].n = c.n;
		t[i].k[0] = c.k[0];
		t[i].k[1] = c.k[1];
		t[i].k[2] = c.k[2];
		t[i].ref = c.centroid;

		t[i].g.x = (t[i].p[0].x + t[i].p[1].x + t[i].p[2].x) / 3;
		t[i].g.y = (t[i].p[0].y + t[i].p[1].y + t[i].p[2].y) / 3;
		t[i].g.z = (t[i].p[0].z + t[i].p[1].z + t[i].p[2].z) / 3;
	}
}

void cylinder2triangle(Triangle3D t[], Cylinder c) {
    printf("\n*** cylinder2triangle ***\n");

    Vector o1, o2, vertex[24];
    double theta = 2 * PI / c.div;

    // Cylinder base points
    o1 = c.p; 
    o2 = (Vector){c.p.x, c.p.y, c.p.z + c.h};
    c.centroid = (Vector){c.p.x, c.p.y, c.p.z + c.h / 2};

    // Generate vertices
    for (int i = 0; i < c.div; i++) {
        vertex[i] = (Vector){c.p.x + c.r * cos(theta * i),
                             c.p.y + c.r * sin(theta * i),
                             c.p.z};
        vertex[i + 12] = (Vector){vertex[i].x, vertex[i].y, c.p.z + c.h};
    }

    // Base triangles
    for (int i = 0; i < c.div; i++) {
        int next = (i + 1) % c.div;

        // Bottom face
        t[i].p[0] = o1;
        t[i].p[1] = vertex[i];
        t[i].p[2] = vertex[next];

        // Top face
        t[i + 12].p[0] = o2;
        t[i + 12].p[1] = vertex[next + 12];
        t[i + 12].p[2] = vertex[i + 12];

        // Side faces
        t[i + 24].p[0] = vertex[i];
        t[i + 24].p[1] = vertex[next];
        t[i + 24].p[2] = vertex[next + 12];

        t[i + 36].p[0] = vertex[i];
        t[i + 36].p[1] = vertex[next + 12];
        t[i + 36].p[2] = vertex[i + 12];
    }

    // Set triangle properties
    for (int i = 0; i < c.num; i++) {
        t[i].o = c.o;
        t[i].n = c.n;
        t[i].k[0] = c.k[0];
        t[i].k[1] = c.k[1];
        t[i].k[2] = c.k[2];
		t[i].ref = c.centroid;

        // Calculate centroid
        t[i].g = (Vector){(t[i].p[0].x + t[i].p[1].x + t[i].p[2].x) / 3,
                          (t[i].p[0].y + t[i].p[1].y + t[i].p[2].y) / 3,
                          (t[i].p[0].z + t[i].p[1].z + t[i].p[2].z) / 3};
    }
}


/*
void cylinder2triangle(Triangle3D t[], Cylinder c) {
	printf("\n*** cylinder2triangle ***\n");
	// trying with 12 (change div in t-step[2])

	Vector o1, o2, vertex[24];
	double theta;

	o1.x = c.p.x;		o1.y = c.p.y;		o1.z = c.p.z;
	o2.x = c.p.x;		o2.y = c.p.y;		o2.z = c.p.z + c.h;

	c.centroid.x = c.p.x;
	c.centroid.y = c.p.y;
	c.centroid.z = c.p.z + c.h / 2;

	theta = 2 * PI / c.div;
	printf("theta: %.4lf\n", theta);

	for (int i = 0; i < c.div; i++) {
		vertex[i].x = c.p.x + (int) (c.r * cos(theta * i));
		vertex[i].y = c.p.y + (int) (c.r * sin(theta * i));
		vertex[i].z = c.p.z;

		vertex[i + 12].x = vertex[i].x;
		vertex[i + 12].y = vertex[i].y;
		vertex[i + 12].z = c.p.z + c.h;
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
		t[i].p[0] = o1;			t[i].p[1] = vertex[next];			t[i].p[2] = vertex[i];
		t[i + 12].p[0] = o2;	t[i + 12].p[1] = vertex[i + 12];	t[i + 12].p[2] = vertex[next + 12];


		// 側面（24-35, 36-47)
		// t[i + 24].p[0] = vertex[i];	t[i + 24].p[1] = vertex[next];		t[i + 24].p[2] = vertex[next + 12];
		// t[i + 36].p[0] = vertex[i];	t[i + 36].p[1] = vertex[next + 12];	t[i + 36].p[2] = vertex[i + 12];

		t[i + 24].p[0] = vertex[i];	t[i + 24].p[1] = vertex[next];		t[i + 24].p[2] = vertex[next + 12];
		t[i + 36].p[0] = vertex[i];	t[i + 36].p[1] = vertex[next + 12];	t[i + 36].p[2] = vertex[i + 12];
	}
	
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
*/