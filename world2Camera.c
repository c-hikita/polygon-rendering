/** 
 * @file world2Camera.c
 * @brief World to Camera transformation and matrix operations
 * This file contains functions to perform world-to-camera coordinate transformations, 
 * along with matrix operations for transforming vertices in 3D space.
 */

/**
 * @brief Multiply two matrices and store the result
 * This function multiplies two 4x4 matrices (matrixA and matrixB) and stores the result in the 'result' matrix.
 * The matrix multiplication is done using the standard row-by-column method.
 *
 * @param matrixA A 4x4 matrix to be multiplied
 * @param matrixB A 4x4 matrix to be multiplied
 * @param result A 4x4 matrix where the result of the multiplication will be stored
 */
void multiplyMatrices(double matrixA[SIZE][SIZE], double matrixB[SIZE][SIZE], double result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;  
            for (int k = 0; k < SIZE; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

/**
 * @brief Multiply a row vector with a matrix and store the result
 * This function multiplies a row vector (row) with a 4x4 matrix and stores the result in the 'result' vector.
 *
 * @param row A 4-element vector to be multiplied with the matrix
 * @param matrix A 4x4 matrix to be multiplied
 * @param result A 4-element vector where the result of the multiplication will be stored
 */
void multiplyRows(double row[SIZE], double matrix[SIZE][SIZE], double result[SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        result[j] = 0;  
        for (int k = 0; k < SIZE; k++) {
            result[j] += row[k] * matrix[k][j]; 
        }
    }
}

/**
 * @brief Print the elements of a matrix
 * This function prints the contents of a 4x4 matrix to the console. Each row is printed on a new line.
 *
 * @param matrix A 4x4 matrix to be printed
 */
void printMatrix(double matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Convert world coordinates to camera coordinates
 * This function performs the transformation of a set of 3D vertices from world coordinates 
 * to camera coordinates using a series of transformations. The transformation is done 
 * by first calculating the camera space basis vectors (u, v, n), constructing the 
 * transformation matrices, and then applying the transformations to each vertex.
 *
 * @param vertices An array of 3D vectors representing the vertices to be transformed
 * @param s The settings struct that contains the camera position and target point
 * @param count The number of vertices to transform
 *
 * @note This function modifies the input vertices array by transforming each vertex 
 *       into camera coordinates.
 */
void world2Camera(Vector vertices[], Settings s, int count) {
    Vector u, v, n, vnn;
    double w[SIZE], c[SIZE], a[SIZE][SIZE], t[SIZE][SIZE], r[SIZE][SIZE], vn;

    // Compute the camera space basis vectors (n, v, u)
    n = subtract(s.world_d, s.c);
    n = normalize(n);  

    v.x = 0; v.y = 0; v.z = 1;
    vn = dotProduct(v, n);
    vnn = multiply(n, vn);
    v = subtract(v, vnn);
    v = normalize(v);
    u = crossProduct(n, v);

    // Construct the translation matrix (t)
    t[0][0] = 1; t[0][1] = 0; t[0][2] = 0; t[0][3] = 0;
    t[1][0] = 0; t[1][1] = 1; t[1][2] = 0; t[1][3] = 0;
    t[2][0] = 0; t[2][1] = 0; t[2][2] = 1; t[2][3] = 0;
    t[3][0] = -s.c.x; t[3][1] = -s.c.y; t[3][2] = -s.c.z; t[3][3] = 1;

    // Construct the rotation matrix (r)
    r[0][0] = u.x; r[0][1] = v.x; r[0][2] = n.x; r[0][3] = 0;
    r[1][0] = u.y; r[1][1] = v.y; r[1][2] = n.y; r[1][3] = 0;
    r[2][0] = u.z; r[2][1] = v.z; r[2][2] = n.z; r[2][3] = 0;
    r[3][0] = 0; r[3][1] = 0; r[3][2] = 0; r[3][3] = 1;

    // Multiply translation and rotation matrices
    multiplyMatrices(t, r, a);

    // Apply the transformation to each vertex
    for (int i = 0; i < count; i++) {
        w[0] = vertices[i].x;
        w[1] = vertices[i].y;
        w[2] = vertices[i].z;
        w[3] = 1;

        multiplyRows(w, a, c);

        // Adjust the transformed vertex position
        vertices[i].x = c[0] + WIDTH / 2;
        vertices[i].y = c[1] + HEIGHT / 2;
        vertices[i].z = c[2];
    }
}
