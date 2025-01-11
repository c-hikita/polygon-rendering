// calcVector
// Chikako Hikita

Vector add(Vector a, Vector b) {
    Vector result = {a.x + b.x, a.y + b.y, a.z + b.z};
    return result;
}
// 引き算
Vector subtract(Vector a, Vector b) {
    Vector result = {a.x - b.x, a.y - b.y, a.z - b.z};
    return result;
}

Vector multiply(Vector a, double n) {
    Vector result = {a.x * n, a.y * n, a.z * n};
    return result;
}

Vector divide(Vector a, double n) {
    Vector result = {a.x / n, a.y / n, a.z / n};
    return result;
}

// Function to compute the cross product of two vectors
Vector crossProduct(Vector a, Vector b) {
    Vector result = {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
    return result;
}

// 内積
double dotProduct(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// 単位ベクトル
Vector normalize(Vector v) {
    double length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (length > 0.0001) {  // avoid division by zero
        v.x /= length;
        v.y /= length;
        v.z /= length;
    }
    return v;
}

Vector calcCentroid(Vector p[]) {
    Vector rtn;
    rtn.x = (p[0].x + p[1].x + p[2].x) / 3;
    rtn.y = (p[0].y + p[1].y + p[2].y) / 3;
    rtn.z = (p[0].z + p[1].z + p[2].z) / 3;

    return rtn;
}

Vector normalVector(Triangle3D t) {
    // printf("*** normalVector ***\n");
    Vector n, u1, u2, reference;
    double test;

    // printf("ref = (%.3lf, %.3lf, %.3lf)\n", t.ref.x, t.ref.y, t.ref.z); 

    u1 = subtract(t.p[1], t.p[0]);
    u2 = subtract(t.p[2], t.p[0]);
    n = crossProduct(u2, u1);
	n = normalize(n);

    // printf("N = (%.3lf, %.3lf, %.3lf)\n", n.x, n.y, n.z); 

    reference = subtract(t.g, t.ref);
    reference = normalize(reference);
    // printf("ref = (%.3lf, %.3lf, %.3lf)\n", reference.x, reference.y, reference.z); 

    test = dotProduct(n, reference);
    // printf("test: %.3lf\n", test);
    
    if (test < 0) {
        n.x = - n.x;
        n.y = - n.y;
        n.z = - n.z;

        // printf("N rotated\n");
    }
    return n;
}

// 色成分のクランプ処理
Color255 clampColor(Color255 color) {
    color.r = (color.r < 0) ? 0 : (color.r > 255) ? 255 : color.r;
    color.g = (color.g < 0) ? 0 : (color.g > 255) ? 255 : color.g;
    color.b = (color.b < 0) ? 0 : (color.b > 255) ? 255 : color.b;
    return color;
}

void initializeTriangles(Triangle3D t[], int num) {
	for (int i = 0; i < num; i++) {
		Vector p[3], v[3];
		for (int j = 0; j < 3; j++) {
			t[i].p[j].x = 0;	t[i].p[j].y = 0;	t[i].p[j].z = 0;
			t[i].v[j].x = 0;	t[i].v[j].y = 0;	t[i].v[j].z = 0;
		}

		t[i].o.r = 0;	t[i].o.g = 0;	t[i].o.b = 0;
		t[i].n = 0;
		t[i].k[0] = 0;	t[i].k[1] = 0;	t[i].k[2] = 0;

		t[i].g.x = 0;	t[i].g.y = 0;	t[i].g.z = 0;
		t[i].ref.x = 0;	t[i].ref.y = 0;	t[i].ref.z = 0;

		t[i].id = 0;
	}
}