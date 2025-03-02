/**
 * @file drawPrimitive.c
 * @brief Functions for rendering 3D primitives with hidden surface removal and Z-buffering.
 * 
 * This file contains functions to initialize the Z-buffer, remove hidden surfaces,
 * sort triangles by depth, and render 3D primitives using a Z-buffer approach.
 */

/**
 * @brief Initializes the Z-buffer by setting all depth values to a large number.
 * 
 * The Z-buffer is used to determine visibility during rendering. 
 * Each pixel's depth value is initialized to 10000, ensuring that closer objects are drawn first.
 */
void initializeZBuffer() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            ZBuffer[i][j] = 10000; 
        }
    }
}

/**
 * @brief Performs hidden surface removal using back-face culling.
 * 
 * This function removes triangles that face away from the camera based on the dot product
 * between the normal vector of the triangle and the view vector. The remaining visible triangles
 * are stored in the `removed` array.
 * 
 * @param num The number of input triangles.
 * @param removed An array to store the resulting visible triangles after removal.
 * @param t The array of input triangles.
 * @param s The rendering settings, including the camera position.
 * @return The number of triangles remaining after hidden surface removal.
 */
int hiddenSurfaceRemoval(int num, Triangle3D removed[], Triangle3D t[], Settings s) {
    int rtn = 0;
    Vector u1, u2, n, v;
    double nv;

    for (int i = 0; i < num; i++) {
        if (t[i].p[0].x < 0 || t[i].p[0].y < 0 || t[i].p[0].z < 0) continue;
        if (t[i].p[1].x < 0 || t[i].p[1].y < 0 || t[i].p[1].z < 0) continue;
        if (t[i].p[2].x < 0 || t[i].p[2].y < 0 || t[i].p[2].z < 0) continue;

        n = normalVector(t[i]);
        v = subtract(s.c, t[i].g);
        v = normalize(v);
        nv = dotProduct(n, v);

        if (nv > 1e-6 || nv < -1e-6) {
            removed[rtn] = t[i];
            rtn++;
        }       
    }

    return rtn;
}

/**
 * @brief Sorts an array of triangles based on their depth (Z-coordinate).
 * 
 * The function sorts triangles in descending order of their average Z-coordinate
 * using the Bubble Sort algorithm, ensuring that farther objects are drawn first.
 * 
 * @param n The number of triangles.
 * @param t The array of triangles to be sorted.
 */
void sortTriangles(int n, Triangle3D t[]) {
    int swapped;
    Triangle3D tmp;

    for (int i = 0; i < n - 1; i++) {
        swapped = 0;

        for (int j = 0; j < n - i - 1; j++) {
            if (t[j].g.z < t[j + 1].g.z) {
                tmp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = tmp;
                swapped = 1;
            }
        }

        if (swapped == 0) break;
    }
}

/**
 * @brief Renders and draws 3D primitives with hidden surface removal and Z-buffering.
 * 
 * This function applies hidden surface removal, initializes the Z-buffer, and then renders 
 * and paints visible triangles using the given settings. It computes the centroid of each 
 * triangle before rendering.
 * 
 * @param num The number of triangles to render.
 * @param t The array of input triangles.
 * @param s The rendering settings, including camera position and other parameters.
 */
void drawPrimitive(int num, Triangle3D t[], Settings s) {
    int count;
    Triangle3D removed[1000];
    Rendered rendered;

    s.c.x = 0;
    s.c.y = 0; 
    s.c.z = 0;

    initializeTriangles(removed, num);
    count = hiddenSurfaceRemoval(num, removed, t, s);

    initializeZBuffer();

    for (int i = 0; i < count; i++) {
        t[i].g.x = (t[i].p[0].x + t[i].p[1].x + t[i].p[2].x) / 3;
        t[i].g.y = (t[i].p[0].y + t[i].p[1].y + t[i].p[2].y) / 3;
        t[i].g.z = (t[i].p[0].z + t[i].p[1].z + t[i].p[2].z) / 3;

        rendered = renderTriangle(removed[i], s); // Render the triangle
        paintTriangle(rendered);                 // Fill the triangle with color
    }
}