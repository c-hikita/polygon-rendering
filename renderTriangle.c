/** 
 * @file renderTriangle.c
 * @brief Functions for perspective projection, color calculation, and triangle rendering
 * This file contains functions that perform the projection of 3D points onto a 2D plane, 
 * calculate the color of each vertex of a triangle based on lighting and shading models, 
 * and render a triangle based on 3D data.
 */

/**
 * @brief Perform perspective projection on the triangle vertices
 * 
 * This function transforms the 3D coordinates of the triangle vertices by applying 
 * a perspective projection, which scales the x and y coordinates based on the z value.
 *
 * @param t Array of 3D vectors representing the triangle's vertices.
 * @param rtn Array where the 2D projected coordinates of the triangle's vertices will be stored.
 * @param d The distance to the projection plane.
 */
void projection(Vector t[], Vector rtn[], int d) {
    for (int i = 0; i < 3; i++) {
        double dz;
        if (t[i].z != 0) dz = d / t[i].z;  // Avoid division by zero

        rtn[i].x = dz * t[i].x;  // Apply perspective to x-coordinate
        rtn[i].y = dz * t[i].y;  // Apply perspective to y-coordinate
        rtn[i].z = t[i].z;       // Retain the z-coordinate for further computations
    }
}

/**
 * @brief Calculate the color of each vertex of a triangle based on lighting and shading
 * 
 * This function computes the color of each vertex in the triangle based on the 
 * Phong shading model, which includes ambient, diffuse, and specular lighting.
 * It also takes into account the properties of the triangle (e.g., material) and the scene settings.
 *
 * @param t The triangle for which the vertex colors are calculated.
 * @param rtn Array where the computed colors of the vertices will be stored.
 * @param s The settings of the scene, which includes the camera position and ambient color.
 */
void calcColor(Triangle3D t, Color255 rtn[], Settings s) {
    double color[3];  // Store the calculated color for each vertex
    double ln, rv;    // Diffuse and specular reflection components

    Color1 o1;        // The original color of the triangle
    Vector n, v, l, r;  // Normal vector, view vector, light direction vector, and reflection vector

    // Normalize the triangle's original color (from 0 to 255 to 0.0 to 1.0)
    o1.r = (double)t.o.r / 255;
    o1.g = (double)t.o.g / 255;
    o1.b = (double)t.o.b / 255;

    for (int i = 0; i < 3; i++) {
        n = t.v[i];
        n = normalize(n);  // Normalize the normal vector

        v = subtract(s.c, t.p[i]);
        v = normalize(v);  // Normalize the view vector

        l = subtract(s.camera_i, t.p[i]);
        l = normalize(l);  // Normalize the light direction vector

        ln = dotProduct(l, n);  // Compute the dot product for diffuse lighting
        ln = fmax(ln, 0.0);      // Clamp the value to avoid negative results

        r.x = 2 * ln * n.x - l.x;  // Compute the reflection vector
        r.y = 2 * ln * n.y - l.y;
        r.z = 2 * ln * n.z - l.z;
        r = normalize(r);  // Normalize the reflection vector

        rv = dotProduct(r, v);  // Compute the dot product for specular lighting
        rv = fmax(rv, 0.0);      // Clamp the value to avoid negative results

        // Calculate the specular component (Phong model)
        double specular = (rv > 0) ? pow(rv, t.n) : 0.0;

        // Combine ambient, diffuse, and specular components for each color channel
        color[0] = t.k[0] * o1.r * s.a.r + t.k[1] * o1.r * s.icolor.r * ln + t.k[2] * s.icolor.r * specular;
        color[1] = t.k[0] * o1.g * s.a.g + t.k[1] * o1.g * s.icolor.g * ln + t.k[2] * s.icolor.g * specular;
        color[2] = t.k[0] * o1.b * s.a.b + t.k[1] * o1.b * s.icolor.b * ln + t.k[2] * s.icolor.b * specular;

        // Store the final color values, ensuring they are within the valid range (0-255)
        rtn[i].r = (int)(fmax(0, fmin(255, color[0] * 255)));
        rtn[i].g = (int)(fmax(0, fmin(255, color[1] * 255)));
        rtn[i].b = (int)(fmax(0, fmin(255, color[2] * 255)));
    }
}

/**
 * @brief Render a 3D triangle to 2D coordinates with color
 * 
 * This function performs both the perspective projection and color calculation 
 * for a given triangle, and returns the rendered triangle with transformed 
 * vertex positions and their corresponding colors.
 *
 * @param tri3 The 3D triangle to be rendered.
 * @param s The settings of the scene, which includes camera and light parameters.
 * @return Rendered The rendered triangle with projected coordinates and colors.
 */
Rendered renderTriangle(Triangle3D tri3, Settings s) {
    Rendered rtn;
    Vector before[3], after[3];
    Color255 color[3];

    // Store the original 3D points for projection
    for (int i = 0; i < 3; i++) {
        before[i] = tri3.p[i];
    }

    projection(before, after, s.dist);  // Perform the perspective projection
    calcColor(tri3, color, s);  // Calculate the color of the triangle's vertices

    // Store the results (projected coordinates and colors)
    for (int i = 0; i < 3; i++) {
        rtn.cp[i].p = after[i];
        rtn.cp[i].c = color[i];
    }

    rtn.g = calcCentroid(after);  // Calculate the centroid of the projected triangle

    return rtn;  // Return the rendered triangle
}