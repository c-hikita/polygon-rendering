/**
 * @file calcVector.c
 * @brief Implements functions for 3D geometry calculations and rendering.
 *
 * This file includes functions for vector operations (addition, subtraction, 
 * multiplication, division, normalization, etc.), normal vector calculation, 
 * and centroid computation for various 3D shapes (triangle, cube, cylinder, sphere). 
 * It also handles color clamping and triangle initialization for rendering in a scene.
 */

 /**
 * @brief Adds two vectors and returns the result.
 * 
 * This function computes the element-wise sum of two vectors and 
 * returns the resulting vector.
 * 
 * @param a The first vector.
 * @param b The second vector.
 * @return The sum of the two vectors.
 */
Vector add(Vector a, Vector b) {
    Vector result = {a.x + b.x, a.y + b.y, a.z + b.z};
    return result;
}

/**
 * @brief Subtracts vector b from vector a and returns the result.
 * 
 * This function computes the element-wise difference between two vectors 
 * and returns the resulting vector.
 * 
 * @param a The vector to subtract from.
 * @param b The vector to subtract.
 * @return The difference of the two vectors.
 */
Vector subtract(Vector a, Vector b) {
    Vector result = {a.x - b.x, a.y - b.y, a.z - b.z};
    return result;
}

/**
 * @brief Multiplies a vector by a scalar n.
 * 
 * This function scales the components of the vector by the given scalar 
 * and returns the resulting vector.
 * 
 * @param a The vector to be scaled.
 * @param n The scalar multiplier.
 * @return The scaled vector.
 */
Vector multiply(Vector a, double n) {
    Vector result = {a.x * n, a.y * n, a.z * n};
    return result;
}

/**
 * @brief Divides a vector by a scalar n.
 * 
 * This function scales the components of the vector by the reciprocal 
 * of the scalar and returns the resulting vector.
 * 
 * @param a The vector to be divided.
 * @param n The scalar divisor.
 * @return The scaled vector.
 */
Vector divide(Vector a, double n) {
    Vector result = {a.x / n, a.y / n, a.z / n};
    return result;
}

/**
 * @brief Computes the cross product of two vectors.
 * 
 * This function calculates the cross product between two vectors, 
 * resulting in a vector that is perpendicular to both input vectors.
 * 
 * @param a The first vector.
 * @param b The second vector.
 * @return The cross product of the two vectors.
 */
Vector crossProduct(Vector a, Vector b) {
    Vector result = {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
    return result;
}

/**
 * @brief Computes the dot product of two vectors.
 * 
 * This function calculates the dot product between two vectors, which is 
 * a scalar value representing their directional alignment.
 * 
 * @param a The first vector.
 * @param b The second vector.
 * @return The dot product of the two vectors.
 */
double dotProduct(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/**
 * @brief Normalizes a vector to unit length.
 * 
 * This function scales the vector so that its magnitude is 1, 
 * preserving its direction.
 * 
 * @param v The vector to normalize.
 * @return The normalized vector.
 */
Vector normalize(Vector v) {
    double length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (length > 0.0001) { // Prevent division by zero
        v.x /= length;
        v.y /= length;
        v.z /= length;
    }
    return v;
}

/**
 * @brief Calculates the centroid of a triangle given three vertices.
 * 
 * This function computes the centroid of a triangle by averaging its 
 * three vertex positions.
 * 
 * @param p An array of three vertices representing the triangle.
 * @return The centroid of the triangle.
 */
Vector calcCentroid(Vector p[]) {
    Vector rtn;
    rtn.x = (p[0].x + p[1].x + p[2].x) / 3;
    rtn.y = (p[0].y + p[1].y + p[2].y) / 3;
    rtn.z = (p[0].z + p[1].z + p[2].z) / 3;

    return rtn;
}

/**
 * @brief Computes the normal vector of a given triangle.
 * 
 * This function calculates the normal vector of a triangle by first 
 * computing two edge vectors, taking their cross product, and normalizing the result.
 * The normal is then oriented based on a reference vector.
 * 
 * @param t The triangle for which the normal is computed.
 * @return The normal vector of the triangle.
 */
Vector normalVector(Triangle3D t) {
    Vector n, u1, u2, reference;
    double test;

    // Compute edge vectors
    u1 = subtract(t.p[1], t.p[0]);
    u2 = subtract(t.p[2], t.p[0]);

    // Compute the normal
    n = crossProduct(u2, u1);
    n = normalize(n);

    // Ensure correct orientation based on reference direction
    reference = subtract(t.g, t.ref);
    reference = normalize(reference);
    test = dotProduct(n, reference);
    
    if (test < 0) {
        n.x = - n.x;
        n.y = - n.y;
        n.z = - n.z;
    }
    return n;
}

/**
 * @brief Clamps color components to the valid range (0-255).
 * 
 * This function ensures that the RGB components of a color remain within 
 * the valid range of 0 to 255.
 * 
 * @param color The color to clamp.
 * @return The clamped color.
 */
Color255 clampColor(Color255 color) {
    color.r = (color.r < 0) ? 0 : (color.r > 255) ? 255 : color.r;
    color.g = (color.g < 0) ? 0 : (color.g > 255) ? 255 : color.g;
    color.b = (color.b < 0) ? 0 : (color.b > 255) ? 255 : color.b;
    return color;
}

/**
 * @brief Initializes an array of triangles with default values.
 * 
 * This function sets the vertices, colors, and other properties of the triangles 
 * to their default values.
 * 
 * @param t The array of triangles to initialize.
 * @param num The number of triangles to initialize.
 */
void initializeTriangles(Triangle3D t[], int num) {
    for (int i = 0; i < num; i++) {
        Vector p[3], v[3];
        for (int j = 0; j < 3; j++) {
            t[i].p[j].x = 0; t[i].p[j].y = 0; t[i].p[j].z = 0;
            t[i].v[j].x = 0; t[i].v[j].y = 0; t[i].v[j].z = 0;
        }

        t[i].o.r = 0; t[i].o.g = 0; t[i].o.b = 0;
        t[i].n = 0;
        t[i].k[0] = 0; t[i].k[1] = 0; t[i].k[2] = 0;

        t[i].g.x = 0; t[i].g.y = 0; t[i].g.z = 0;
        t[i].ref.x = 0; t[i].ref.y = 0; t[i].ref.z = 0;

        t[i].id = 0;
    }
}

/**
 * @brief Computes the centroid of a cube.
 * 
 * This function calculates the centroid of a cube by averaging the positions 
 * of two opposite corners.
 * 
 * @param centroid The current centroid to average with.
 * @param c The cube whose centroid is being computed.
 * @return The centroid of the cube.
 */
Vector cubeCentroid(Vector centroid, Cube c) {
    Vector thisCube, rtn;

    // Compute center of the cube
    thisCube = add(c.p1, c.p2);
    thisCube = divide(thisCube, 2);

    // If no previous centroid, return this cube's center
    if (centroid.x == 0 && centroid.y == 0 && centroid.z == 0) {
        return thisCube;
    }

    // Compute the new centroid by averaging with the previous one
    rtn = add(thisCube, centroid);
    rtn = divide(rtn, 2);
    return rtn;
}

/**
 * @brief Computes the centroid of a cylinder.
 * 
 * This function calculates the centroid of a cylinder by averaging the 
 * positions of the two circular ends.
 * 
 * @param centroid The current centroid to average with.
 * @param c The cylinder whose centroid is being computed.
 * @return The centroid of the cylinder.
 */
Vector cylinderCentroid(Vector centroid, Cylinder c) {
    Vector o1, o2, thisCylinder, rtn;

    o1 = c.p;
    o2 = (Vector){c.p.x, c.p.y, c.p.z + c.h};

    thisCylinder = add(o1, o2);
    thisCylinder = divide(thisCylinder, 2);

    if (centroid.x == 0 && centroid.y == 0 && centroid.z == 0) {
        return thisCylinder;
    }

    rtn = add(thisCylinder, centroid);
    rtn = divide(rtn, 2);
    return rtn;
}

/**
 * @brief Computes the centroid of a sphere.
 * 
 * This function calculates the centroid of a sphere, which is simply 
 * its center position.
 * 
 * @param centroid The current centroid to average with.
 * @param s The sphere whose centroid is being computed.
 * @return The centroid of the sphere.
 */
Vector sphereCentroid(Vector centroid, Sphere s) {
    Vector rtn;

    if (centroid.x == 0 && centroid.y == 0 && centroid.z == 0) {
        return s.p;
    }

    rtn = add(s.p, centroid);
    divide(rtn, 2);
    return rtn;
}