// world2Camera.c
// Chikako Hikita

#define SIZE 4

void multiplyMatrices(double matrixA[SIZE][SIZE], double matrixB[SIZE][SIZE], double result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;  // Initialize result[i][j] to 0 before summing
            for (int k = 0; k < SIZE; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

void multiplyRows(double row[SIZE], double matrix[SIZE][SIZE], double result[SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        result[j] = 0;  // Initialize the result[j] to 0
        for (int k = 0; k < SIZE; k++) {
            result[j] += row[k] * matrix[k][j];  // Sum the products for each column of the matrix
        }
    }
}

void printMatrix(double matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void world2Camera(Vector vertices[], Settings s, int count) {
	Vector u, v, n, vnn;
	double w[SIZE], c[SIZE], a[SIZE][SIZE], t[SIZE][SIZE], r[SIZE][SIZE], vn;

	for (int i = 0; i < count; i++) {
		n = subtract(vertices[i], s.d);
		n = normalize(n);	

		v.x = 0; v.y = 0; v.z = 1;
		vn = dotProduct(v, n);
		vnn = multiply(n, vn);
		v = subtract(v, vnn);
		v = normalize(v);

		u = crossProduct(n, v);

		printf("N = (%.3lf, %.3lf, %.3lf)\n", n.x, n.y, n.z);
		printf("V = (%.3lf, %.3lf, %.3lf)\n", v.x, v.y, v.z);
		printf("U = (%.3lf, %.3lf, %.3lf)\n\n", u.x, u.y, u.z);

		t[0][0] = 1;		t[0][1] = 0;		t[0][2] = 0;		t[0][3] = 0;
		t[1][0] = 0;		t[1][1] = 1;		t[1][2] = 0;		t[1][3] = 0;
		t[2][0] = 0;		t[2][1] = 0;		t[2][2] = 1;		t[2][3] = 0;
		t[3][0] = -s.c.x;	t[3][1] = -s.c.y;	t[3][2] = -s.c.z;	t[3][3] = 1;
	
		r[0][0] = u.x;		r[0][1] = v.x;		r[0][2] = n.x;		r[0][3] = 0;
		r[1][0] = u.y;		r[1][1] = v.y;		r[1][2] = n.y;		r[1][3] = 0;
		r[2][0] = u.z;		r[2][1] = v.z;		r[2][2] = n.z;		r[2][3] = 0;
		r[3][0] = -s.c.x;	r[3][1] = -s.c.y;	r[3][2] = -s.c.z;	r[3][3] = 1;

		// printf("T:\n");
		// printMatrix(t);
		// printf("R:\n");
		// printMatrix(r);
		multiplyMatrices(t, r, a);
		// printf("A:\n");
		// printMatrix(r);

		w[0] = vertices[i].x;
		w[1] = vertices[i].y;
		w[2] = vertices[i].z;
		w[3] = 1;

		printf("world: ");
		for (int j = 0; j < SIZE; j++) printf("%f ", w[j]);
		printf("\n");

		multiplyRows(w, a, c);

		printf("camera: ");
		for (int j = 0; j < SIZE; j++) printf("%f ", c[j]);
		printf("\n\n");

		vertices[i].x = c[0];
		vertices[i].y = c[1];
		vertices[i].z = c[2];
	}


}