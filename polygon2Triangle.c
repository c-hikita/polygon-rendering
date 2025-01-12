﻿// polygon2Triangle
// Chikako Hikita

void initializeNV(NormalVectors rtn[], int num) {
    for (int i = 0; i < num; i++) {
        rtn[i].count = 0;
    }
}

void calcNormalVector(NormalVectors rtn[], Triangle3D t, int id1, int id2, int id3) {
    Vector normal;
    int idx1, idx2, idx3;

    idx1 = rtn[id1].count;
    idx2 = rtn[id2].count;
    idx3 = rtn[id3].count;

    normal = normalVector(t);

    rtn[id1].v[idx1] = normal;
    rtn[id2].v[idx2] = normal;
    if (id3 > 0) rtn[id3].v[idx3] = normal;

    rtn[id1].count++;
    rtn[id2].count++;
    if (id3 > 0) rtn[id3].count++;
}

void calcAverageNV(Vector rtn[], NormalVectors nv[], int num) {
    Vector tmp;

    for (int i = 0; i < num; i++) {
        tmp.x = 0;  tmp.y = 0;  tmp.z = 0;
        for (int j = 0; j < nv[i].count; j++) {
            tmp = add(tmp, nv[i].v[j]);
        }

        if (tmp.x == 0 && tmp.y == 0 && tmp.z == 0) {
            rtn[i] = tmp;
        } else {
            rtn[i] = divide(tmp, (double) nv[i].count);
        }
    }
}

int cube2triangle(Triangle3D t[], Cube c, Settings s, Transform tf, int num) {
	// printf("\n*** cube2triangle ***\n");

	// Vector vertices[8];
    NormalVectors nv[8];
    Vector tmp[1], avg_nv[8];

    // c.num = 12;

	// c.centroid.x = (c.p1.x + c.p2.x) / 2;
	// c.centroid.y = (c.p1.y + c.p2.y) / 2;
	// c.centroid.z = (c.p1.z + c.p2.z) / 2;

    // printf("Original Point1: (%f, %f, %f)\n", c.p1.x, c.p1.y, c.p1.z);
    // printf("Original Point2: (%f, %f, %f)\n", c.p2.x, c.p2.y, c.p2.z);

    // if (tf.translate.x != 0 || tf.translate.y != 0 || tf.translate.z != 0) {
    //     c.p1.x += tf.translate.x;
    //     c.p1.y += tf.translate.y;
    //     c.p1.z += tf.translate.z;

    //     c.p2.x += tf.translate.x;
    //     c.p2.y += tf.translate.y;
    //     c.p2.z += tf.translate.z;
    // }

    if (tf.scale != 100) {
        double scale = tf.scale / 100.0;
        c.p2.x = c.p1.x + (c.p2.x - c.p1.x) * scale;
        c.p2.y = c.p1.y + (c.p2.y - c.p1.y) * scale;
        c.p2.z = c.p1.z + (c.p2.z - c.p1.z) * scale;
    }

    // printf("Translated Point1: (%f, %f, %f)\n", c.p1.x, c.p1.y, c.p1.z);
    // printf("Translated Point2: (%f, %f, %f)\n", c.p2.x, c.p2.y, c.p2.z);

    // Define the cube vertices relative to its diagonal points
    Vector vertices[8] = {
        {c.p1.x, c.p1.y, c.p2.z},
        {c.p1.x, c.p1.y, c.p1.z},
        {c.p2.x, c.p1.y, c.p1.z},
        {c.p2.x, c.p1.y, c.p2.z},
        {c.p1.x, c.p2.y, c.p2.z},
        {c.p1.x, c.p2.y, c.p1.z},
        {c.p2.x, c.p2.y, c.p1.z},
        {c.p2.x, c.p2.y, c.p2.z}
    };

    // world2Camera
    world2Camera(vertices, s, 8);

    tmp[0] = c.centroid;
    world2Camera(tmp, s, 1);

    if (tf.rotate.x != 0 || tf.rotate.y != 0 || tf.rotate.z != 0) {
        rotateVertices(vertices, s, tf.rotate, 8);
    }

    if (tf.translate.x != 0 || tf.translate.y != 0 || tf.translate.z != 0) {
        for (int i = 0; i < 8; i++) {
            vertices[i].x += tf.translate.x;
            vertices[i].y += tf.translate.y;
            vertices[i].z += tf.translate.z;
        }
    }

	t[num].p[0] = vertices[0];	    t[num].p[1] = vertices[4];	    t[num].p[2] = vertices[7];
	t[num + 1].p[0] = vertices[7];	t[num + 1].p[1] = vertices[3];	t[num + 1].p[2] = vertices[0];
	t[num + 2].p[0] = vertices[1];	t[num + 2].p[1] = vertices[2];	t[num + 2].p[2] = vertices[6];
	t[num + 3].p[0] = vertices[6];	t[num + 3].p[1] = vertices[5];	t[num + 3].p[2] = vertices[1];
	t[num + 4].p[0] = vertices[0];	t[num + 4].p[1] = vertices[1];	t[num + 4].p[2] = vertices[5];
	t[num + 5].p[0] = vertices[5];	t[num + 5].p[1] = vertices[4];	t[num + 5].p[2] = vertices[0];
	t[num + 6].p[0] = vertices[3];	t[num + 6].p[1] = vertices[7];	t[num + 6].p[2] = vertices[6];
	t[num + 7].p[0] = vertices[6];	t[num + 7].p[1] = vertices[2];	t[num + 7].p[2] = vertices[3];
	t[num + 8].p[0] = vertices[0];	t[num + 8].p[1] = vertices[3];	t[num + 8].p[2] = vertices[2];
	t[num + 9].p[0] = vertices[2];	t[num + 9].p[1] = vertices[1];	t[num + 9].p[2] = vertices[0];
	t[num + 10].p[0] = vertices[4];	t[num + 10].p[1] = vertices[5];	t[num + 10].p[2] = vertices[6];
	t[num + 11].p[0] = vertices[6];	t[num + 11].p[1] = vertices[7];	t[num + 11].p[2] = vertices[4];

	for (int i = num; i < num + 12; i++) {
		t[i].o = c.o;
		t[i].n = c.n;
		t[i].k[0] = c.k[0];
		t[i].k[1] = c.k[1];
		t[i].k[2] = c.k[2];
		t[i].ref = tmp[0];
        t[i].id = 1;

		t[i].g.x = (t[i].p[0].x + t[i].p[1].x + t[i].p[2].x) / 3;
		t[i].g.y = (t[i].p[0].y + t[i].p[1].y + t[i].p[2].y) / 3;
		t[i].g.z = (t[i].p[0].z + t[i].p[1].z + t[i].p[2].z) / 3;
    
        t[i].v[0] = normalVector(t[i]);
        t[i].v[1] = t[i].v[0];
        t[i].v[2] = t[i].v[0];
	}
    return c.num;
}

int cylinder2triangle(Triangle3D t[], Cylinder c, Settings s, Transform tf, int num) {
    // printf("\n*** cylinder2triangle ***\n");

    NormalVectors nv[100];
    Vector tmp[1], o[2], o_nv[2], avg_nv[100], vertices[100];
    double theta = 2 * PI / c.div;
    int next;

    initializeNV(nv, 100);
    // c.num = 4 * c.div;

    // 1. Apply Scaling
    if (tf.scale != 100) {
        double scale = tf.scale / 100.0;
        c.r *= scale;
        c.h *= scale;
    }

    // 2. Define Base Points (before translation and rotation)

    // // 3. Apply Translation
    // c.p.x += tf.translate.x;
    // c.p.y += tf.translate.y;
    // c.p.z += tf.translate.z;

    // Update Points After Translation
    o[0] = c.p;
    o[1] = (Vector){c.p.x, c.p.y, c.p.z + c.h};
    c.centroid = (Vector){c.p.x, c.p.y, c.p.z + c.h / 2};

    // 4. Generate Vertices
    for (int i = 0; i < c.div; i++) {
        double angle = i * theta;
        vertices[i] = (Vector){
            c.p.x + c.r * cos(angle),
            c.p.y + c.r * sin(angle),
            c.p.z
        };
        vertices[i + c.div] = (Vector){
            vertices[i].x,
            vertices[i].y,
            c.p.z + c.h
        };
    }

    // world2Camera
    world2Camera(vertices, s, c.div * 2);
    world2Camera(o, s, 2);

    // tmp[0] = add(o[0], o[1]);
    // tmp[0] = divide(tmp[0], 2);    
    // world2Camera(tmp, s, 1);
    // c.centroid = tmp[0];

    // 5. Apply Rotation
    if (tf.rotate.x != 0 || tf.rotate.y != 0 || tf.rotate.z != 0) {
        rotateVertices(vertices, s, tf.rotate, c.div * 2);
        rotateVertices(o, s, tf.rotate, 2);
    }

    for (int i = 0; i < c.div * 2; i++) {
        if (i < 2) {
            o[i].x += tf.translate.x;
            o[i].y += tf.translate.y;
            o[i].z += tf.translate.z;
        }        
        vertices[i].x += tf.translate.x;
        vertices[i].y += tf.translate.y;
        vertices[i].z += tf.translate.z;
    }

    c.centroid = add(o[0], o[1]);
    c.centroid = divide(c.centroid, 2);

    // 6. Create Triangles (unchanged from original logic)
    for (int i = 0; i < c.div; i++) {
        next = (i + 1) % c.div;

        // Bottom face
        t[num + i].p[0] = o[0];
        t[num + i].p[1] = vertices[next];
        t[num + i].p[2] = vertices[i];
        // calcNormalVector(nv, t[num + i], next, i, -1);

        // Top face
        t[num + i + c.div].p[0] = o[1];
        t[num + i + c.div].p[1] = vertices[i + c.div];
        t[num + i + c.div].p[2] = vertices[next + c.div];
        // calcNormalVector(nv, t[num + i + c.div], i + c.div, next + c.div, -1);

        // Side faces
        t[num + i + 2 * c.div].p[0] = vertices[i];
        t[num + i + 2 * c.div].p[1] = vertices[next];
        t[num + i + 2 * c.div].p[2] = vertices[next + c.div];
        // calcNormalVector(nv, t[num + i + 2 * c.div], i, next, next + c.div);

        t[num + i + 3 * c.div].p[0] = vertices[i];
        t[num + i + 3 * c.div].p[1] = vertices[next + c.div];
        t[num + i + 3 * c.div].p[2] = vertices[i + c.div];
        // calcNormalVector(nv, t[num + i + 3 * c.div], i, next + c.div, i + c.div);
    }

    for (int i = num; i < c.num + num; i++) {
        t[i].o = c.o;
        t[i].n = c.n;
        t[i].k[0] = c.k[0];
        t[i].k[1] = c.k[1];
        t[i].k[2] = c.k[2];
        t[i].ref = c.centroid;
        t[i].id = 2;

        // printf("%2d: ", i - num);
        // for (int j = 0; j < 3; j++) {
        //     printf("(%.1lf %.1lf %.1lf) ", t[i].v[j].x, t[i].v[j].y, t[i].v[j].z);
        // }
        // printf("\n");

        // Calculate centroid
        t[i].g = (Vector){
            (t[i].p[0].x + t[i].p[1].x + t[i].p[2].x) / 3,
            (t[i].p[0].y + t[i].p[1].y + t[i].p[2].y) / 3,
            (t[i].p[0].z + t[i].p[1].z + t[i].p[2].z) / 3
        };
    }

    o_nv[0] = normalVector(t[num]);
    o_nv[1] = normalVector(t[num + c.div]);

    for (int i = 0; i < c.div; i++) {
        next = (i + 1) % c.div;

        calcNormalVector(nv, t[num + i], next, i, -1);
        calcNormalVector(nv, t[num + i + c.div], i + c.div, next + c.div, -1);
        calcNormalVector(nv, t[num + i + 2 * c.div], i, next, next + c.div);
        calcNormalVector(nv, t[num + i + 3 * c.div], i, next + c.div, i + c.div);
    }

    // printf("normal vectors: \n");
    // for (int i = 0; i < c.div * 2; i++) {
    //     printf("%d: ", i);
    //     printf("count: %d  ", nv[i].count);
    //     for (int j = 0; j < 6; j++) {
    //         printf("(%.1lf %.1lf %.1lf) ", nv[i].v[j].x, nv[i].v[j].y, nv[i].v[j].z);
    //     }
    //     printf("\n");
    // }

    // printf("o1: (%.1lf %.1lf %.1lf)\n", o_nv[0].x, o_nv[0].y, o_nv[0].z);
    // printf("o2: (%.1lf %.1lf %.1lf)\n", o_nv[1].x, o_nv[1].y, o_nv[1].z);

    calcAverageNV(avg_nv, nv, c.div * 2);

    /*
    printf("average vectors: \n");
    for (int i = 0; i < c.div * 2; i++) {
        printf("%d: (%.1lf %.1lf %.1lf)\n", i, avg_nv[i].x, avg_nv[i].y, avg_nv[i].z);
    }
    */
    
    // assign vectors
    for (int i = 0; i < c.div; i++) {
        int next = (i + 1) % c.div;

        // Bottom face
        t[num + i].v[0] = o_nv[0];
        t[num + i].v[1] = o_nv[0];
        t[num + i].v[2] = o_nv[0];

        // Top face
        t[num + i + c.div].v[0] = o_nv[1];
        t[num + i + c.div].v[1] = avg_nv[i + c.div];
        t[num + i + c.div].v[2] = avg_nv[next + c.div];

        // Side faces
        t[num + i + 2 * c.div].v[0] = avg_nv[i];
        t[num + i + 2 * c.div].v[1] = avg_nv[next];
        t[num + i + 2 * c.div].v[2] = avg_nv[next + c.div];

        t[num + i + 3 * c.div].v[0] = avg_nv[i];
        t[num + i + 3 * c.div].v[1] = avg_nv[next + c.div];
        t[num + i + 3 * c.div].v[2] = avg_nv[i + c.div];
    }

    return c.num;
}

int sphere2triangle(Triangle3D t[], Sphere s, Settings set, Transform tf, int num) {
    // printf("\n*** sphere2triangle ***\n");

    NormalVectors nv[1000];
    Vector tmp[1], pole[2], avg_nv[1000], vertices[1000];
    double theta_step = PI / s.lat_div;  // Vertical step
    double phi_step = 2 * PI / s.long_div;  // Horizontal step
    int count, rtn;

    initializeNV(nv, 1000);

    // 1. Apply Scaling
    if (tf.scale != 100) {
        double scale = tf.scale / 100.0;
        s.r *= scale;
    }

    // // 3. Apply Translation
    // s.p.x += tf.translate.x;
    // s.p.y += tf.translate.y;
    // s.p.z += tf.translate.z;

    // Generate vertices
    int idx = 0;
    for (int lat = 0; lat <= s.lat_div; lat++) {
        double theta = lat * theta_step;  // Vertical angle
        for (int lon = 0; lon < s.long_div; lon++) {
            double phi = lon * phi_step;  // Horizontal angle

            // Calculate the vertices position using spherical coordinates
            vertices[idx].x = s.p.x + s.r * sin(theta) * cos(phi);
            vertices[idx].y = s.p.y + s.r * sin(theta) * sin(phi);
            vertices[idx].z = s.p.z + s.r * cos(theta);
            idx++;
        }
    }

    // Add the poles as separate vertices
    pole[0] = s.p;
    pole[1] = s.p;

    pole[0].z += s.r;
    pole[1].z -= s.r;

    tmp[0] = s.p;

    // world2Camera
    world2Camera(vertices, set, idx);
    world2Camera(pole, set, 2);
    world2Camera(tmp, set, 1);

    // 5. Apply Rotation
    if (tf.rotate.x != 0 || tf.rotate.y != 0 || tf.rotate.z != 0) {
        rotateVertices(vertices, set, tf.rotate, idx);
        rotateVertices(pole, set, tf.rotate, 2);
    }

    for (int i = 0; i < idx; i++) {
        if (i < 2) {
            pole[i].x += tf.translate.x;
            pole[i].y += tf.translate.y;
            pole[i].z += tf.translate.z;
        }        
        vertices[i].x += tf.translate.x;
        vertices[i].y += tf.translate.y;
        vertices[i].z += tf.translate.z;
    }

    // Generate triangles for the horizontal slices (latitudinal)
    idx = 0;
    for (int lat = 0; lat < s.lat_div; lat++) {
        for (int lon = 0; lon < s.long_div; lon++) {
            int next_lon = (lon + 1) % s.long_div;
            int next_lat = lat + 1;

            if (lat == 0) {
                // Triangles at the north pole
                t[idx + num].p[0] = pole[0];
                t[idx + num].p[1] = vertices[next_lat * s.long_div + lon];
                t[idx + num].p[2] = vertices[next_lat * s.long_div + next_lon];
                idx++;
            } else if (lat == s.lat_div - 1) {
                // Triangles at the south pole
                t[idx + num].p[0] = vertices[lat * s.long_div + lon];
                t[idx + num].p[1] = pole[1];
                t[idx + num].p[2] = vertices[lat * s.long_div + next_lon];
                idx++;
            } else {
                // Bottom triangles
                t[idx + num].p[0] = vertices[lat * s.long_div + lon];
                t[idx + num].p[1] = vertices[next_lat * s.long_div + lon];
                t[idx + num].p[2] = vertices[next_lat * s.long_div + next_lon];
                idx++;

                // Top triangles
                t[idx + num].p[0] = vertices[lat * s.long_div + lon];
                t[idx + num].p[1] = vertices[next_lat * s.long_div + next_lon];
                t[idx + num].p[2] = vertices[lat * s.long_div + next_lon];
                idx++;
            }
        }
    }

    // rtn = idx - num;

    // Set triangle properties (assuming you want them like the cylinder function)
    for (int i = num; i < num + idx; i++) {
        t[i].o = s.o;
        t[i].n = s.n;
        t[i].k[0] = s.k[0];
        t[i].k[1] = s.k[1];
        t[i].k[2] = s.k[2];
        t[i].ref = tmp[0];  // Sphere's center as reference
        t[i].id = 3;

        /*
        printf("t[%d].p: ", i);
        for (int j = 0; j < 3; j++) {
            printf("(%.3lf %.3lf %.3lf) ", t[i].p[j].x, t[i].p[j].y, t[i].p[j].z);
        }
        printf("\n");
        */

        // Calculate centroid of each triangle
        t[i].g = (Vector){
            (t[i].p[0].x + t[i].p[1].x + t[i].p[2].x) / 3,
            (t[i].p[0].y + t[i].p[1].y + t[i].p[2].y) / 3,
            (t[i].p[0].z + t[i].p[1].z + t[i].p[2].z) / 3
        };
    }

    idx = 0;
    for (int lat = 0; lat < s.lat_div; lat++) {
        for (int lon = 0; lon < s.long_div; lon++) {
            int next_lon = (lon + 1) % s.long_div;
            int next_lat = lat + 1;

            if (lat == 0) {
                // Triangles at the north pole
                // t[idx].p[0] = pole[0];
                // t[idx].p[1] = vertices[next_lat * s.long_div + lon];
                // t[idx].p[2] = vertices[next_lat * s.long_div + next_lon];
                calcNormalVector(nv, t[idx + num], idx, next_lat * s.long_div + lon, next_lat * s.long_div + next_lon);
                idx++;
            } else if (lat == s.lat_div - 1) {
                // Triangles at the south pole
                // t[idx].p[0] = vertices[lat * s.long_div + lon];
                // t[idx].p[1] = pole[1];
                // t[idx].p[2] = vertices[lat * s.long_div + next_lon];
                calcNormalVector(nv, t[idx + num], lat * s.long_div + lon, idx + 1, lat * s.long_div + next_lon);
                idx++;
            } else {
                // Bottom triangles
                // t[idx].p[0] = vertices[lat * s.long_div + lon];
                // t[idx].p[1] = vertices[next_lat * s.long_div + lon];
                // t[idx].p[2] = vertices[next_lat * s.long_div + next_lon];
                calcNormalVector(nv, t[idx + num], lat * s.long_div + lon, next_lat * s.long_div + lon, next_lat * s.long_div + next_lon);
                idx++;

                // Top triangles
                // t[idx].p[0] = vertices[lat * s.long_div + lon];
                // t[idx].p[1] = vertices[next_lat * s.long_div + next_lon];
                // t[idx].p[2] = vertices[lat * s.long_div + next_lon];
                calcNormalVector(nv, t[idx + num], lat * s.long_div + lon, next_lat * s.long_div + next_lon, lat * s.long_div + next_lon);
                idx++;
            }
        }
    }

    // printf("normal vectors: \n");

    calcAverageNV(avg_nv, nv, idx + 2);
    // for (int i = 0; i < idx + 2; i++) {
    //     printf("%d: (%.1lf %.1lf %.1lf)\n", i, avg_nv[i].x, avg_nv[i].y, avg_nv[i].z);
    // }
    
    idx = 0;
    for (int lat = 0; lat < s.lat_div; lat++) {
        for (int lon = 0; lon < s.long_div; lon++) {
            int next_lon = (lon + 1) % s.long_div;
            int next_lat = lat + 1;

            if (lat == 0) {
                // Triangles at the north pole
                t[idx + num].v[0] = avg_nv[idx];
                t[idx + num].v[1] = avg_nv[next_lat * s.long_div + lon];
                t[idx + num].v[2] = avg_nv[next_lat * s.long_div + next_lon];
                idx++;
            } else if (lat == s.lat_div - 1) {
                // Triangles at the south pole
                t[idx + num].v[0] = avg_nv[lat * s.long_div + lon];
                t[idx + num].v[1] = avg_nv[idx + 1];
                t[idx + num].v[2] = avg_nv[lat * s.long_div + next_lon];
                idx++;
            } else {
                // Bottom triangles
                t[idx + num].v[0] = avg_nv[lat * s.long_div + lon];
                t[idx + num].v[1] = avg_nv[next_lat * s.long_div + lon];
                t[idx + num].v[2] = avg_nv[next_lat * s.long_div + next_lon];
                idx++;

                // Top triangles
                t[idx + num].v[0] = avg_nv[lat * s.long_div + lon];
                t[idx + num].v[1] = avg_nv[next_lat * s.long_div + next_lon];
                t[idx + num].v[2] = avg_nv[lat * s.long_div + next_lon];
                idx++;
            }
        }
    }

    return idx;
}
