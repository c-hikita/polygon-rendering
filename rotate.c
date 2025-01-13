// rotate.c
// Chikako Hikita

Vector rotatePoint(Vector point, int theta_x, int theta_y, int theta_z) {
    Vector rotated = point;

    double rad_x = theta_x * PI / 180.0;
    double rad_y = theta_y * PI / 180.0;
    double rad_z = theta_z * PI / 180.0;

    if (theta_x != 0) {
        double cosX = cos(rad_x), sinX = sin(rad_x);
        double y = rotated.y, z = rotated.z;
        rotated.y = y * cosX - z * sinX;
        rotated.z = y * sinX + z * cosX;
    }

    if (theta_y != 0) {
        double cosY = cos(rad_y), sinY = sin(rad_y);
        double x = rotated.x, z = rotated.z;
        rotated.x = x * cosY + z * sinY;
        rotated.z = -x * sinY + z * cosY;
    }

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
        v[i].x -= (s.camera_d.x + WIDTH / 2);
        v[i].y -= (s.camera_d.y + HEIGHT / 2);
        v[i].z -= s.camera_d.z;
    }

    for (int i = 0; i < num; i++) {
        v[i] = rotatePoint(v[i], angle.x, angle.y, angle.z);
    }

    for (int i = 0; i < num; i++) {
        v[i].x += (s.camera_d.x + WIDTH / 2);
        v[i].y += (s.camera_d.y + HEIGHT / 2);
        v[i].z += s.camera_d.z;
    }
}