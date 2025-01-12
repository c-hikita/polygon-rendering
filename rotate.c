// rotate.c
// Chikako Hikita

Vector rotatePoint(Vector point, int theta_x, int theta_y, int theta_z) {
    Vector rotated = point;

    // Convert angles to radians
    double rad_x = theta_x * PI / 180.0;
    double rad_y = theta_y * PI / 180.0;
    double rad_z = theta_z * PI / 180.0;

    // Rotate around X-axis
    if (theta_x != 0) {
        double cosX = cos(rad_x), sinX = sin(rad_x);
        double y = rotated.y, z = rotated.z;
        rotated.y = y * cosX - z * sinX;
        rotated.z = y * sinX + z * cosX;
    }

    // Rotate around Y-axis
    if (theta_y != 0) {
        double cosY = cos(rad_y), sinY = sin(rad_y);
        double x = rotated.x, z = rotated.z;
        rotated.x = x * cosY + z * sinY;
        rotated.z = -x * sinY + z * cosY;
    }

    // Rotate around Z-axis
    if (theta_z != 0) {
        double cosZ = cos(rad_z), sinZ = sin(rad_z);
        double x = rotated.x, y = rotated.y;
        rotated.x = x * cosZ - y * sinZ;
        rotated.y = x * sinZ + y * cosZ;
    }

    return rotated;
}

void rotateVertices (Vector v[], Settings s, Vector angle, int num) {
    for (int i = 0; i < num; i++) {
        // v[i].x -= (s.c.x + s.width / 2);
        // v[i].y -= (s.c.y + s.height / 2);
        // v[i].z -= s.c.z;

        v[i].x -= (s.camera_d.x + s.width / 2);
        v[i].y -= (s.camera_d.y + s.height / 2);
        v[i].z -= s.camera_d.z;
    }

    // Rotate the vertices
    for (int i = 0; i < num; i++) {
        v[i] = rotatePoint(v[i], angle.x, angle.y, angle.z);
    }

    // Translate vertices back to the world coordinates
    for (int i = 0; i < num; i++) {
        // v[i].x += (s.c.x + s.width / 2);
        // v[i].y += (s.c.y + s.height / 2);
        // v[i].z += s.c.z;
    
        v[i].x += (s.camera_d.x + s.width / 2);
        v[i].y += (s.camera_d.y + s.height / 2);
        v[i].z += s.camera_d.z;
    }

    // Print the rotated vertices
    // printf("Rotated Vertices:\n");
    // for (int i = 0; i < num; i++) {
    //     printf("Vertex %d: (%f, %f, %f)\n", i, v[i].x, v[i].y, v[i].z);
    // }
}