// world2Camera.c
// Chikako Hikita

#define SIZE 4

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

void multiplyRows(double row[SIZE], double matrix[SIZE][SIZE], double result[SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        result[j] = 0;  
        for (int k = 0; k < SIZE; k++) {
            result[j] += row[k] * matrix[k][j]; 
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

// ワールド座標系からカメラ座標系への変換
void world2Camera(Vector vertices[], Settings s, int count) {
	Vector u, v, n, vnn;
	double w[SIZE], c[SIZE], a[SIZE][SIZE], t[SIZE][SIZE], r[SIZE][SIZE], vn;

	n = subtract(s.world_d, s.c);
	n = normalize(n);	

	v.x = 0; v.y = 0; v.z = 1;
	vn = dotProduct(v, n);
	vnn = multiply(n, vn);
	v = subtract(v, vnn);
	v = normalize(v);
	u = crossProduct(n, v);

	t[0][0] = 1;		t[0][1] = 0;		t[0][2] = 0;		t[0][3] = 0;
	t[1][0] = 0;		t[1][1] = 1;		t[1][2] = 0;		t[1][3] = 0;
	t[2][0] = 0;		t[2][1] = 0;		t[2][2] = 1;		t[2][3] = 0;
	t[3][0] = -s.c.x;	t[3][1] = -s.c.y;	t[3][2] = -s.c.z;	t[3][3] = 1;

	r[0][0] = u.x;		r[0][1] = v.x;		r[0][2] = n.x;		r[0][3] = 0;
	r[1][0] = u.y;		r[1][1] = v.y;		r[1][2] = n.y;		r[1][3] = 0;
	r[2][0] = u.z;		r[2][1] = v.z;		r[2][2] = n.z;		r[2][3] = 0;
	r[3][0] = 0;		r[3][1] = 0;		r[3][2] = 0;	r[3][3] = 1;

	multiplyMatrices(t, r, a);

	for (int i = 0; i < count; i++) {
		w[0] = vertices[i].x;
		w[1] = vertices[i].y;
		w[2] = vertices[i].z;
		w[3] = 1;

		multiplyRows(w, a, c);

		vertices[i].x = c[0] + s.width / 2;
		vertices[i].y = c[1] + s.height / 2;
		vertices[i].z = c[2];
	}
}