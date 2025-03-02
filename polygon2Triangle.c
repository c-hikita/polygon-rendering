
/**
 * @file polygon2Triangle
 * @brief This file contains functions for converting geometric shapes such as cubes, cylinders, and spheres into triangular mesh models, and calculating normal vectors for these shapes.
 */

/**
 * @brief Initializes the normal vectors array.
 * @param rtn The array of normal vectors to initialize.
 * @param num The number of normal vectors in the array.
 */
void initializeNV(NormalVectors rtn[], int num) {
    for (int i = 0; i < num; i++) {
        rtn[i].count = 0;
    }
}

/**
 * @brief Calculates the normal vector for a triangle and assigns it to the specified normal vectors.
 * @param rtn The array of normal vectors to store the calculated normal vectors.
 * @param t The 3D triangle for which the normal vector is calculated.
 * @param id1, id2, id3 Indices of the normal vectors to assign the calculated normal vector to.
 */
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

/**
 * @brief Averages the normal vectors for each vertex.
 * @param rtn The array to store the averaged normal vectors.
 * @param nv The array of normal vectors for each vertex.
 * @param num The number of vertices for which the normal vectors are averaged.
 */
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

/**
 * @brief Converts a cube into a triangle mesh model.
 * @param t The array of triangles to store the resulting mesh.
 * @param c The cube to convert.
 * @param s The settings for coordinate transformations.
 * @param tf The transformation to apply (scale, rotation, translation).
 * @param num The starting index for storing the resulting triangles.
 * @return The updated number of triangles.
 */
int cube2triangle(Triangle3D t[], Cube c, Settings s, Transform tf, int num) {
	// printf("\n*** cube2triangle ***\n");

    NormalVectors nv[8];
    Vector tmp[1], avg_nv[8];

    if (tf.scale != 100) {
        double scale = tf.scale / 100.0;
        c.p2.x = c.p1.x + (c.p2.x - c.p1.x) * scale;
        c.p2.y = c.p1.y + (c.p2.y - c.p1.y) * scale;
        c.p2.z = c.p1.z + (c.p2.z - c.p1.z) * scale;
    }

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

    // Convert from world coordinates to camera coordinates
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

    // Define the triangles of the cube using its vertices
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

/**
 * 円柱から三角形ポリゴンモデルへの変換
 * @brief Converts a cylinder to a triangle mesh by calculating its vertices and normal vectors for the top, bottom, and side faces.
 * @param t The array of `Triangle3D` objects where the resulting triangles will be stored.
 * @param c The `Cylinder` object that defines the cylinder's parameters (radius, height, number of divisions).
 * @param s The settings object that contains the camera transformation settings.
 * @param tf The transformation object that defines the scaling, rotation, and translation to be applied to the cylinder.
 * @param num The current index in the `Triangle3D` array where the triangles will start being placed.
 * @return Returns the total number of triangles generated for the cylinder.
 */
int cylinder2triangle(Triangle3D t[], Cylinder c, Settings s, Transform tf, int num) {
    // printf("\n*** cylinder2triangle ***\n");

    NormalVectors nv[100];
    Vector tmp[1], o[2], o_nv[2], avg_nv[100], vertices[100];
    double theta = 2 * PI / c.div;
    int next;

    initializeNV(nv, 100);

    // Apply scale transformation if necessary
    if (tf.scale != 100) {
        double scale = tf.scale / 100.0;
        c.r *= scale;
        c.h *= scale;
    }

    // Initialize the bottom and top positions of the cylinder
    o[0] = c.p;
    o[1] = (Vector){c.p.x, c.p.y, c.p.z + c.h};

    // Calculate the vertices for the top and bottom circles of the cylinder
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

    // Transform the vertices and cylinder positions from world space to camera space
    world2Camera(vertices, s, c.div * 2);
    world2Camera(o, s, 2);

    // Apply rotation if necessary
    if (tf.rotate.x != 0 || tf.rotate.y != 0 || tf.rotate.z != 0) {
        rotateVertices(vertices, s, tf.rotate, c.div * 2);
        rotateVertices(o, s, tf.rotate, 2);
    }

    // Apply translation to the vertices and the top/bottom positions
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

    // Calculate the centroid of the cylinder
    c.centroid = add(o[0], o[1]);
    c.centroid = divide(c.centroid, 2);

    // Generate triangles for the cylinder's bottom, top, and side surfaces
    for (int i = 0; i < c.div; i++) {
        next = (i + 1) % c.div;

        // Bottom face
        t[num + i].p[0] = o[0];
        t[num + i].p[1] = vertices[next];
        t[num + i].p[2] = vertices[i];

        // Top face
        t[num + i + c.div].p[0] = o[1];
        t[num + i + c.div].p[1] = vertices[next + c.div];
        t[num + i + c.div].p[2] = vertices[i + c.div];

        // Side face (first triangle)
        t[num + i + 2 * c.div].p[0] = vertices[i];
        t[num + i + 2 * c.div].p[1] = vertices[next];
        t[num + i + 2 * c.div].p[2] = vertices[next + c.div];

        // Side face (second triangle)
        t[num + i + 3 * c.div].p[0] = vertices[i];
        t[num + i + 3 * c.div].p[1] = vertices[i + c.div];
        t[num + i + 3 * c.div].p[2] = vertices[next + c.div];
    }

    // Assign object properties to each triangle
    for (int i = num; i < c.num + num; i++) {
        t[i].o = c.o;
        t[i].n = c.n;
        t[i].k[0] = c.k[0];
        t[i].k[1] = c.k[1];
        t[i].k[2] = c.k[2];
        t[i].ref = c.centroid;
        t[i].id = 2;

        // Calculate the centroid for each triangle
        t[i].g = (Vector){
            (t[i].p[0].x + t[i].p[1].x + t[i].p[2].x) / 3,
            (t[i].p[0].y + t[i].p[1].y + t[i].p[2].y) / 3,
            (t[i].p[0].z + t[i].p[1].z + t[i].p[2].z) / 3
        };
    }

    // Calculate the normal vectors for the top and bottom faces
    o_nv[0] = normalVector(t[num]);
    o_nv[1] = normalVector(t[num + c.div]);

    // Calculate normal vectors for side faces
    for (int i = 0; i < c.div; i++) {
        next = (i + 1) % c.div;

        // Bottom face
        calcNormalVector(nv, t[num + i], next, i, -1);

        // Top face
        calcNormalVector(nv, t[num + i + c.div], i + c.div, next + c.div, -1);

        // Side faces
        calcNormalVector(nv, t[num + i + 2 * c.div], i, next, next + c.div);
        calcNormalVector(nv, t[num + i + 3 * c.div], i, next + c.div, i + c.div);
    }

    // Calculate average normal vectors for each vertex
    calcAverageNV(avg_nv, nv, c.div * 2);

    // Assign normal vectors to each triangle
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

        // Side face
        t[num + i + 2 * c.div].v[0] = avg_nv[i];
        t[num + i + 2 * c.div].v[1] = avg_nv[next];
        t[num + i + 2 * c.div].v[2] = avg_nv[next + c.div];

        t[num + i + 3 * c.div].v[0] = avg_nv[i];
        t[num + i + 3 * c.div].v[1] = avg_nv[next + c.div];
        t[num + i + 3 * c.div].v[2] = avg_nv[i + c.div];
    }

    return c.num;  // Return the number of triangles generated for the cylinder
}

/**
 * @brief Converts a sphere to a triangle mesh by dividing it into latitudinal and longitudinal segments.
 * @param t The array of `Triangle3D` objects where the resulting triangles will be stored.
 * @param s The `Sphere` object that defines the sphere's parameters (radius, number of divisions).
 * @param set The settings object that contains the camera transformation settings.
 * @param tf The transformation object that defines the scaling, rotation, and translation to be applied to the sphere.
 * @param num The current index in the `Triangle3D` array where the triangles will start being placed.
 * @return Returns the total number of triangles generated for the sphere.
 */
int sphere2triangle(Triangle3D t[], Sphere s, Settings set, Transform tf, int num) {
    // Arrays for normal vectors, temporary storage, poles, and vertices
    NormalVectors nv[1000];
    Vector tmp[1], pole[2], avg_nv[1000], vertices[1000];
    double theta_step = PI / s.lat_div;  // Angle step for latitude
    double phi_step = 2 * PI / s.long_div;  // Angle step for longitude
    int count, rtn;

    // Initialize normal vectors array
    initializeNV(nv, 1000);

    // Apply scaling transformation if necessary
    if (tf.scale != 100) {
        double scale = tf.scale / 100.0;
        s.r *= scale;  // Scale the sphere radius
    }

    int idx = 0;

    // Calculate vertices based on latitude and longitude divisions
    for (int lat = 0; lat <= s.lat_div; lat++) {
        double theta = (lat * theta_step) - (PI / 2);  // Latitude angle
        for (int lon = 0; lon < s.long_div; lon++) {
            double phi = lon * phi_step;  // Longitude angle  

            // Calculate the vertex coordinates based on spherical coordinates
            vertices[idx].x = s.p.x + s.r * cos(theta) * cos(phi);
            vertices[idx].y = s.p.y + s.r * cos(theta) * sin(phi);
            vertices[idx].z = s.p.z + s.r * sin(theta);
            idx++;
        }
    }

    // Define the two poles of the sphere
    pole[0] = s.p;
    pole[1] = s.p;
    pole[0].z += s.r;  // North pole
    pole[1].z -= s.r;  // South pole

    tmp[0] = s.p;

    // Transform vertices and poles from world coordinates to camera coordinates
    world2Camera(vertices, set, idx);
    world2Camera(pole, set, 2);
    world2Camera(tmp, set, 1);

    // Apply rotation transformation if necessary
    if (tf.rotate.x != 0 || tf.rotate.y != 0 || tf.rotate.z != 0) {
        rotateVertices(vertices, set, tf.rotate, idx);
        rotateVertices(pole, set, tf.rotate, 2);
    }

    // Apply translation transformation to vertices and poles
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

    idx = 0;

    // Create triangles for the sphere using the vertices
    for (int lat = 0; lat < s.lat_div; lat++) {
        for (int lon = 0; lon < s.long_div; lon++) {
            int next_lon = (lon + 1) % s.long_div;  // Next longitude index
            int next_lat = lat + 1;  // Next latitude index

            // Top cap triangles (from north pole)
            if (lat == 0) {
                t[idx + num].p[0] = pole[0];
                t[idx + num].p[1] = vertices[next_lat * s.long_div + lon];
                t[idx + num].p[2] = vertices[next_lat * s.long_div + next_lon];
                idx++;
            }
            // Bottom cap triangles (from south pole)
            else if (lat == s.lat_div - 1) {
                t[idx + num].p[0] = vertices[lat * s.long_div + lon];
                t[idx + num].p[1] = pole[1];
                t[idx + num].p[2] = vertices[lat * s.long_div + next_lon];
                idx++;
            }
            // Middle triangles
            else {
                // Two triangles for each cell in the middle band
                t[idx + num].p[0] = vertices[lat * s.long_div + lon];
                t[idx + num].p[1] = vertices[next_lat * s.long_div + lon];
                t[idx + num].p[2] = vertices[next_lat * s.long_div + next_lon];
                idx++;

                t[idx + num].p[0] = vertices[lat * s.long_div + lon];
                t[idx + num].p[1] = vertices[next_lat * s.long_div + next_lon];
                t[idx + num].p[2] = vertices[lat * s.long_div + next_lon];
                idx++;
            }
        }
    }

    // Set object properties (e.g., color, normal) for each triangle
    for (int i = num; i < num + idx; i++) {
        t[i].o = s.o;  // Object properties
        t[i].n = s.n;
        t[i].k[0] = s.k[0];
        t[i].k[1] = s.k[1];
        t[i].k[2] = s.k[2];
        t[i].ref = tmp[0];  // Reference point
        t[i].id = 3;  // Sphere identifier

        // Calculate the centroid (geometric center) of each triangle
        t[i].g = (Vector){
            (t[i].p[0].x + t[i].p[1].x + t[i].p[2].x) / 3,
            (t[i].p[0].y + t[i].p[1].y + t[i].p[2].y) / 3,
            (t[i].p[0].z + t[i].p[1].z + t[i].p[2].z) / 3
        };
    }

    // Calculate normal vectors for each triangle
    idx = 0;
    for (int lat = 0; lat < s.lat_div; lat++) {
        for (int lon = 0; lon < s.long_div; lon++) {
            int next_lon = (lon + 1) % s.long_div;
            int next_lat = lat + 1;

            // Top cap and middle triangles
            if (lat == 0) {
                calcNormalVector(nv, t[idx + num], idx, next_lat * s.long_div + lon, next_lat * s.long_div + next_lon);
                idx++;
            }
            // Bottom cap triangles
            else if (lat == s.lat_div - 1) {
                calcNormalVector(nv, t[idx + num], lat * s.long_div + lon, idx + 1, lat * s.long_div + next_lon);
                idx++;
            }
            // Middle band triangles
            else {
                calcNormalVector(nv, t[idx + num], lat * s.long_div + lon, next_lat * s.long_div + lon, next_lat * s.long_div + next_lon);
                idx++;

                calcNormalVector(nv, t[idx + num], lat * s.long_div + lon, next_lat * s.long_div + next_lon, lat * s.long_div + next_lon);
                idx++;
            }
        }
    }

    // Calculate average normal vectors for each triangle
    calcAverageNV(avg_nv, nv, idx + 2);

    idx = 0;
    // Assign average normals to the triangles
    for (int lat = 0; lat < s.lat_div; lat++) {
        for (int lon = 0; lon < s.long_div; lon++) {
            int next_lon = (lon + 1) % s.long_div;
            int next_lat = lat + 1;

            // Top cap and middle triangles
            if (lat == 0) {
                t[idx + num].v[0] = avg_nv[idx];
                t[idx + num].v[1] = avg_nv[next_lat * s.long_div + lon];
                t[idx + num].v[2] = avg_nv[next_lat * s.long_div + next_lon];
                idx++;
            }
            // Bottom cap triangles
            else if (lat == s.lat_div - 1) {
                t[idx + num].v[0] = avg_nv[lat * s.long_div + lon];
                t[idx + num].v[1] = avg_nv[idx + 1];
                t[idx + num].v[2] = avg_nv[lat * s.long_div + next_lon];
                idx++;
            }
            // Middle band triangles
            else {
                t[idx + num].v[0] = avg_nv[lat * s.long_div + lon];
                t[idx + num].v[1] = avg_nv[next_lat * s.long_div + lon];
                t[idx + num].v[2] = avg_nv[next_lat * s.long_div + next_lon];
                idx++;

                t[idx + num].v[0] = avg_nv[lat * s.long_div + lon];
                t[idx + num].v[1] = avg_nv[next_lat * s.long_div + next_lon];
                t[idx + num].v[2] = avg_nv[lat * s.long_div + next_lon];
                idx++;
            }
        }
    }

    // Return the number of triangles created
    return idx;
}