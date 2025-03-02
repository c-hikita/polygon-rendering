/** 
 * @file rotate.c
 * @brief Functions for rotating 3D points and vertices
 * This file contains functions that perform 3D rotations on points or vertices 
 * based on provided angles along the x, y, and z axes. The rotation is applied 
 * in a 3D space, and vertices are adjusted based on a given camera position.
 */

/**
 * @brief Rotate a 3D point around the x, y, and z axes
 * 
 * This function takes a 3D point and rotates it around the x, y, and z axes 
 * based on the given angles (in degrees). The rotation is performed using 
 * standard 3D rotation matrices for each axis.
 *
 * @param point The point to be rotated, represented as a vector (x, y, z).
 * @param theta_x The angle (in degrees) to rotate around the x-axis.
 * @param theta_y The angle (in degrees) to rotate around the y-axis.
 * @param theta_z The angle (in degrees) to rotate around the z-axis.
 * @return Vector The rotated point.
 */
Vector rotatePoint(Vector point, int theta_x, int theta_y, int theta_z) {
    Vector rotated = point;

    double rad_x = theta_x * PI / 180.0;  // Convert angle to radians
    double rad_y = theta_y * PI / 180.0;  // Convert angle to radians
    double rad_z = theta_z * PI / 180.0;  // Convert angle to radians

    // Rotate around x-axis if necessary
    if (theta_x != 0) {
        double cosX = cos(rad_x), sinX = sin(rad_x);
        double y = rotated.y, z = rotated.z;
        rotated.y = y * cosX - z * sinX;
        rotated.z = y * sinX + z * cosX;
    }

    // Rotate around y-axis if necessary
    if (theta_y != 0) {
        double cosY = cos(rad_y), sinY = sin(rad_y);
        double x = rotated.x, z = rotated.z;
        rotated.x = x * cosY + z * sinY;
        rotated.z = -x * sinY + z * cosY;
    }

    // Rotate around z-axis if necessary
    if (theta_z != 0) {
        double cosZ = cos(rad_z), sinZ = sin(rad_z);
        double x = rotated.x, y = rotated.y;
        rotated.x = x * cosZ - y * sinZ;
        rotated.y = x * sinZ + y * cosZ;
    }

    return rotated;  // Return the rotated point
}

/**
 * @brief Rotate an array of vertices around the x, y, and z axes based on given angles
 * 
 * This function applies the 3D rotation to an array of vertices (points) 
 * using the provided angles. The vertices are first translated to the origin, 
 * rotated, and then translated back to their original position relative to the camera.
 *
 * @param v The array of vertices to be rotated.
 * @param s The settings for the scene, including camera position and dimensions.
 * @param angle The angles for rotation around the x, y, and z axes.
 * @param num The number of vertices in the array to rotate.
 */
void rotateVertices(Vector v[], Settings s, Vector angle, int num) {
    // Translate vertices to the origin (relative to the camera position)
    for (int i = 0; i < num; i++) {
        v[i].x -= (s.camera_d.x + WIDTH / 2);
        v[i].y -= (s.camera_d.y + HEIGHT / 2);
        v[i].z -= s.camera_d.z;
    }

    // Rotate all vertices based on the given angles
    for (int i = 0; i < num; i++) {
        v[i] = rotatePoint(v[i], angle.x, angle.y, angle.z);
    }

    // Translate vertices back to their original position (relative to the camera)
    for (int i = 0; i < num; i++) {
        v[i].x += (s.camera_d.x + WIDTH / 2);
        v[i].y += (s.camera_d.y + HEIGHT / 2);
        v[i].z += s.camera_d.z;
    }
}