// polygon2Triangle
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
        t[i].id = 1;

		t[i].g.x = (t[i].p[0].x + t[i].p[1].x + t[i].p[2].x) / 3;
		t[i].g.y = (t[i].p[0].y + t[i].p[1].y + t[i].p[2].y) / 3;
		t[i].g.z = (t[i].p[0].z + t[i].p[1].z + t[i].p[2].z) / 3;
	}
}

void cylinder2triangle(Triangle3D t[], Cylinder c) {
    printf("\n*** cylinder2triangle ***\n");

    Vector o1, o2, vertex[300];
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
        vertex[i + c.div] = (Vector){vertex[i].x, vertex[i].y, c.p.z + c.h};
    }

    // Base triangles
    for (int i = 0; i < c.div; i++) {
        int next = (i + 1) % c.div;

        // Bottom face
        t[i].p[0] = o1;
        t[i].p[1] = vertex[i];
        t[i].p[2] = vertex[next];

        // Top face
        t[i + c.div].p[0] = o2;
        t[i + c.div].p[1] = vertex[next + c.div];
        t[i + c.div].p[2] = vertex[i + c.div];

        // Side faces
        t[i + 2 * c.div].p[0] = vertex[i];
        t[i + 2 * c.div].p[1] = vertex[next];
        t[i + 2 * c.div].p[2] = vertex[next + c.div];

        t[i + 3 * c.div].p[0] = vertex[i];
        t[i + 3 * c.div].p[1] = vertex[next + c.div];
        t[i + 3 * c.div].p[2] = vertex[i + c.div];
    }

    // Set triangle properties
    for (int i = 0; i < c.num; i++) {
        t[i].o = c.o;
        t[i].n = c.n;
        t[i].k[0] = c.k[0];
        t[i].k[1] = c.k[1];
        t[i].k[2] = c.k[2];
		t[i].ref = c.centroid;
        t[i].id = 2;

        // Calculate centroid
        t[i].g = (Vector){(t[i].p[0].x + t[i].p[1].x + t[i].p[2].x) / 3,
                          (t[i].p[0].y + t[i].p[1].y + t[i].p[2].y) / 3,
                          (t[i].p[0].z + t[i].p[1].z + t[i].p[2].z) / 3};
    }
}

int sphere2triangle(Triangle3D t[], Sphere s) {
    printf("\n*** sphere2triangle ***\n");

    Vector vertex[2000];
    double theta_step = PI / s.lat_div;  // Vertical step
    double phi_step = 2 * PI / s.long_div;  // Horizontal step

    // Generate vertices
    int idx = 0;
    for (int lat = 0; lat <= s.lat_div; lat++) {
        double theta = lat * theta_step;  // Vertical angle
        for (int lon = 0; lon < s.long_div; lon++) {
            double phi = lon * phi_step;  // Horizontal angle

            // Calculate the vertex position using spherical coordinates
            vertex[idx].x = s.p.x + s.r * sin(theta) * cos(phi);
            vertex[idx].y = s.p.y + s.r * sin(theta) * sin(phi);
            vertex[idx].z = s.p.z + s.r * cos(theta);
            idx++;
        }
    }

    // Add the poles as separate vertices
    Vector north_pole = {s.p.x, s.p.y, s.p.z + s.r};
    Vector south_pole = {s.p.x, s.p.y, s.p.z - s.r};

    // Generate triangles for the horizontal slices (latitudinal)
    idx = 0;
    for (int lat = 0; lat < s.lat_div; lat++) {
        for (int lon = 0; lon < s.long_div; lon++) {
            int next_lon = (lon + 1) % s.long_div;
            int next_lat = lat + 1;

            if (lat == 0) {
                // Triangles at the north pole
                t[idx].p[0] = north_pole;
                t[idx].p[1] = vertex[next_lat * s.long_div + lon];
                t[idx].p[2] = vertex[next_lat * s.long_div + next_lon];
                idx++;
            } else if (lat == s.lat_div - 1) {
                // Triangles at the south pole
                t[idx].p[0] = vertex[lat * s.long_div + lon];
                t[idx].p[1] = south_pole;
                t[idx].p[2] = vertex[lat * s.long_div + next_lon];
                idx++;
            } else {
                // Bottom triangles
                t[idx].p[0] = vertex[lat * s.long_div + lon];
                t[idx].p[1] = vertex[next_lat * s.long_div + lon];
                t[idx].p[2] = vertex[next_lat * s.long_div + next_lon];
                idx++;

                // Top triangles
                t[idx].p[0] = vertex[lat * s.long_div + lon];
                t[idx].p[1] = vertex[next_lat * s.long_div + next_lon];
                t[idx].p[2] = vertex[lat * s.long_div + next_lon];
                idx++;
            }
        }
    }

    printf("idx: %d\n", idx);

    // Set triangle properties (assuming you want them like the cylinder function)
    for (int i = 0; i < idx; i++) {
        t[i].o = s.o;
        t[i].n = s.n;
        t[i].k[0] = s.k[0];
        t[i].k[1] = s.k[1];
        t[i].k[2] = s.k[2];
        t[i].ref = s.p;  // Sphere's center as reference
        t[i].id = 3;

        // Calculate centroid of each triangle
        t[i].g = (Vector){
            (t[i].p[0].x + t[i].p[1].x + t[i].p[2].x) / 3,
            (t[i].p[0].y + t[i].p[1].y + t[i].p[2].y) / 3,
            (t[i].p[0].z + t[i].p[1].z + t[i].p[2].z) / 3
        };
    }

    return idx;
}
