// transformPrimitive.c
// Chikako Hikita

Vector rotatePoint(Vector point, int theta_x, int theta_y, int theta_z) {
    Vector rtn;
    
    // Convert angles to radians
    double rad_x = theta_x * PI / 180.0;
    double rad_y = theta_y * PI / 180.0;
    double rad_z = theta_z * PI / 180.0;

    // Rotation matrices
    double R_x[4][4] = {
        {1, 0, 0, 0},
        {0, cos(rad_x), sin(rad_x), 0},
        {0, -sin(rad_x), cos(rad_x), 0},
        {0, 0, 0, 1}
    };

    double R_y[4][4] = {
        {cos(rad_y), 0, -sin(rad_y), 0},
        {0, 1, 0, 0},
        {sin(rad_y), 0, cos(rad_y), 0},
        {0, 0, 0, 1}
    };

    double R_z[4][4] = {
        {cos(rad_z), sin(rad_z), 0, 0},
        {-sin(rad_z), cos(rad_z), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    // Apply rotations in sequence
    double temp[4] = {point.x, point.y, point.z, 1};
    double result[4] = {0, 0, 0, 0};

    // Rotate around X
    for (int i = 0; i < 4; i++) {
        // result[i] = 0;
        for (int j = 0; j < 4; j++) {
            result[i] += R_x[i][j] * temp[j];
        }
    }

    // Copy result back
    for (int i = 0; i < 4; i++) temp[i] = result[i];

    // Rotate around Y
    for (int i = 0; i < 4; i++) {
        result[i] = 0;
        for (int j = 0; j < 4; j++) {
            result[i] += R_y[i][j] * temp[j];
        }
    }

    // Copy result back
    for (int i = 0; i < 4; i++) temp[i] = result[i];

    // Rotate around Z
    for (int i = 0; i < 4; i++) {
        result[i] = 0;
        for (int j = 0; j < 4; j++) {
            result[i] += R_z[i][j] * temp[j];
        }
    }

    // Update the point coordinates
    rtn.x = result[0];
    rtn.y = result[1];
    rtn.z = result[2];

    return rtn;
}

void translateCube(Cube cube, Vector t) {
    cube.p1.x += t.x;
    cube.p1.y += t.y;
    cube.p1.z += t.z;

    cube.p2.x += t.x;
    cube.p2.y += t.y;
    cube.p2.z += t.z;
}

void scaleCube(Cube cube, double scale) {
    // Scale the cube relative to one of its corners (e.g., `p1`).
    cube.p2.x = cube.p1.x + (cube.p2.x - cube.p1.x) * scale;
    cube.p2.y = cube.p1.y + (cube.p2.y - cube.p1.y) * scale;
    cube.p2.z = cube.p1.z + (cube.p2.z - cube.p1.z) * scale;
}
/*
void rotateCube(Cube cube, double theta_x, double theta_y, double theta_z) {
    cube.p1 = rotatePoint(cube.p1, theta_x, theta_y, theta_z);
    cube.p2 = rotatePoint(cube.p2, theta_x, theta_y, theta_z);
}
*/

Cube transformCube(Cube c, Transform t) {
    Cube rtn = c;

    printf("translate.x: %.3lf\n", t.translate.x);
    printf("Original Point1: (%f, %f, %f)\n", c.p1.x, c.p1.y, c.p1.z);
    printf("Original Point2: (%f, %f, %f)\n", c.p2.x, c.p2.y, c.p2.z);


    if (t.translate.x != 0 || t.translate.y != 0 || t.translate.z != 0) {
        rtn.p1.x += t.translate.x;
        rtn.p1.y += t.translate.y;
        rtn.p1.z += t.translate.z;

        rtn.p2.x += t.translate.x;
        rtn.p2.y += t.translate.y;
        rtn.p2.z += t.translate.z;
    }

    if (t.scale != 100) {
        double scale = t.scale / 100.0;

        rtn.p2.x = c.p1.x + (c.p2.x - c.p1.x) * scale;
        rtn.p2.y = c.p1.y + (c.p2.y - c.p1.y) * scale;
        rtn.p2.z = c.p1.z + (c.p2.z - c.p1.z) * scale;
    }

    if (t.rotate_x != 0 || t.rotate_y != 0 || t.rotate_z != 0) {
       //  rtn.p1 = rotatePoint(c.p1, t.rotate_x, t.rotate_y, t.rotate_z);
       //  rtn.p2 = rotatePoint(c.p2, t.rotate_x, t.rotate_y, t.rotate_z);
    }

    printf("Transformed Point1: (%f, %f, %f)\n", rtn.p1.x, rtn.p1.y, rtn.p1.z);
    printf("Transformed Point2: (%f, %f, %f)\n", rtn.p2.x, rtn.p2.y, rtn.p2.z);

    return rtn;
}


/*
void translate_sphere(Sphere s, double tx, double ty, double tz) {
    s.center.x += tx;
    s.center.y += ty;
    s.center.z += tz;
}

void scale_sphere(Sphere *s, double scale) {
    s.radius *= scale;
}

void rotate_sphere(Sphere *s, double angle, char axis) {
    // Rotation doesn't directly apply to a sphere as it's symmetric.
    // But if needed, you can define an orientation or apply rotation to its components.
    // Here, it's left as a placeholder.
}

void translate_cylinder(Cylinder *c, double tx, double ty, double tz) {
    c.bottom_center.x += tx;
    c.bottom_center.y += ty;
    c.bottom_center.z += tz;

    c.top_center.x += tx;
    c.top_center.y += ty;
    c.top_center.z += tz;
}

void scale_cylinder(Cylinder *c, double scale) {
    c.radius *= scale;
    c.height *= scale;
}

void rotate_cylinder(Cylinder *c, double angle, char axis) {
    // Implement rotation around the specified axis (e.g., 'x', 'y', 'z').
    // This would typically require rotating `bottom_center` and `top_center` about the axis.
}
*/


/*
Vector applyTransformation(Matrix4x4 matrix, Vector v) {
    Vector result;
    result.x = matrix.m[0][0] * v.x + matrix.m[0][1] * v.y + matrix.m[0][2] * v.z + matrix.m[0][3];
    result.y = matrix.m[1][0] * v.x + matrix.m[1][1] * v.y + matrix.m[1][2] * v.z + matrix.m[1][3];
    result.z = matrix.m[2][0] * v.x + matrix.m[2][1] * v.y + matrix.m[2][2] * v.z + matrix.m[2][3];
    return result;
}

Matrix4x4 createTranslationMatrix(double tx, double ty, double tz) {
    Matrix4x4 matrix = {{{1, 0, 0, tx},
                         {0, 1, 0, ty},
                         {0, 0, 1, tz},
                         {0, 0, 0, 1}}};
    return matrix;
}

Matrix4x4 createScalingMatrix(double sx, double sy, double sz) {
    Matrix4x4 matrix = {{{sx, 0, 0, 0},
                         {0, sy, 0, 0},
                         {0, 0, sz, 0},
                         {0, 0, 0, 1}}};
    return matrix;
}



void transformCube(Cube cube, Matrix4x4 matrix) {
    cube.p1 = applyTransformation(matrix, cube.p1);
    cube.p2 = applyTransformation(matrix, cube.p2);
}

void transformCylinder(Cylinder *cylinder, Matrix4x4 matrix) {
    cylinder.bottom_center = applyTransformation(matrix, cylinder.bottom_center);
    cylinder.top_center = applyTransformation(matrix, cylinder.top_center);
}

void transformSphere(Sphere *sphere, Matrix4x4 matrix) {
    sphere.center = applyTransformation(matrix, sphere.center);
}

int main() {
    // Example usage
    Cube cube = {{0, 0, 0}, {1, 1, 1}};
    Cylinder cylinder = {{0, 0, 0}, {0, 0, 1}, 1, 0.5};
    Sphere sphere = {{0, 0, 0}, 1};

    Matrix4x4 translation = createTranslationMatrix(2, 2, 2);
    transformCube(&cube, translation);
    transformCylinder(&cylinder, translation);
    transformSphere(&sphere, translation);

    printf("Cube: p1(%.2f, %.2f, %.2f), p2(%.2f, %.2f, %.2f)\n", 
            cube.p1.x, cube.p1.y, cube.p1.z, cube.p2.x, cube.p2.y, cube.p2.z);
    printf("Cylinder: bottom(%.2f, %.2f, %.2f), top(%.2f, %.2f, %.2f)\n", 
            cylinder.bottom_center.x, cylinder.bottom_center.y, cylinder.bottom_center.z,
            cylinder.top_center.x, cylinder.top_center.y, cylinder.top_center.z);
    printf("Sphere: center(%.2f, %.2f, %.2f), radius %.2f\n", 
            sphere.center.x, sphere.center.y, sphere.center.z, sphere.radius);

    return 0;
}

*/