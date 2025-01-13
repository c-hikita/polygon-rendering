// drawPrimitive.c
// Chikako Hikita

// Initialize the Z-buffer to a far depth value
void initializeZBuffer(int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ZBuffer[i][j] = 10000; // Initialize with the maximum possible value
        }
    }
}


// 後面除去
int hiddenSurfaceRemoval(int num, Triangle3D removed[], Triangle3D t[], Settings s) {
	int check, rtn = 0;
	Vector u1, u2, n, v;
	double nv;

	// printf("***hiddenSurfaceRemoval***\n");
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

// 三角形面をz座標でソート
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

// プリミティブの描画
void drawPrimitive(int num, Triangle3D t[], Settings s) {
	int count;
	Triangle3D removed[1000];
	// double ZBuffer[HEIGHT][WIDTH];
	Rendered rendered;

	s.c.x = 0;
	s.c.y = 0; 
	s.c.z = 0;

	initializeTriangles(removed, num);
	count = hiddenSurfaceRemoval(num, removed, t, s);

	initializeZBuffer(s.width, s.height);
	// sortTriangles(count, removed);

	// printf("zbuffer:\n");
    // for (int i = 0; i < s.height; i++) {
    //     for (int j = 0; j < s.width; j++) {
    //         printf("%.0lf ", ZBuffer[i][j]); // Initialize with the maximum possible value
    //     }
	// 	printf("\n");
    // }

	for (int i = 0; i < count; i++) {
		// printf("\ntriangle %d\n", i);
		t[i].g.x = (t[i].p[0].x + t[i].p[1].x + t[i].p[2].x)/3;
		t[i].g.y = (t[i].p[0].y + t[i].p[1].y + t[i].p[2].y)/3;
		t[i].g.z = (t[i].p[0].z + t[i].p[1].z + t[i].p[2].z)/3;

		rendered = renderTriangle(removed[i], s);	// 三角形のレンダリング
		paintTriangle(s.width, s.height, rendered);	// 三角形の塗りつぶし
	}
}