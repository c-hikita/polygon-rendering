// drawPrimitive
// Chikako Hikita

int hiddenSurfaceRemoval(int num, Triangle3D removed[], Triangle3D t[], Settings s) {
	int check, rtn = 0;
	Vector u1, u2, n, v;
	double nv;

	// printf("***hiddenSurfaceRemoval***\n");
	for (int i = 0; i < num; i++) {
		if (t[i].p[0].x < 0 || t[i].p[0].y < 0 || t[i].p[0].z < 0) continue;
		if (t[i].p[1].x < 0 || t[i].p[1].y < 0 || t[i].p[1].z < 0) continue;
		if (t[i].p[2].x < 0 || t[i].p[2].y < 0 || t[i].p[2].z < 0) continue;

		// printf("triangle[%d]\n", i);
		n = normalVector(t[i]);
		// printf("N = (%.3lf, %.3lf, %.3lf)\n", n.x, n.y, n.z); 

		/*
		u1 = subtract(t[i].p[1], t[i].p[0]);
		u2 = subtract(t[i].p[2], t[i].p[0]);

		n = crossProduct(u1, u2);
		n = normalize(n);
		printf("N = (%.3lf, %.3lf, %.3lf)\n", n.x, n.y, n.z);
		*/
		
		/*
		check = 0;
		for (int j = 0; j < 3; j++) {
			v = subtract(s.c, t[i].p[j]);
        	v = normalize(v);

			nv = dotProduct(n, v);	
			if (nv < 0) check++;
		}

		if (check < 3) {
			removed[rtn] = t[i];
			rtn++;
		}
		*/
		
		v = subtract(s.c, t[i].g);
        v = normalize(v);
	 	// printf("V = (%.3lf, %.3lf, %.3lf)\n", v.x, v.y, v.z);

		nv = dotProduct(n, v);
		// printf("%d NV: %.3lf\n\n", i, nv);

		// if (nv >= 0) {
		if (nv > 1e-6 || nv < -1e-6) {
			removed[rtn] = t[i];
			rtn++;
		}
		
	}

	// printf("count: %d\n", rtn);

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

void drawPrimitive(int num, Triangle3D t[], Settings s) {
	int count;
	Triangle3D removed[1000];
	Rendered rendered;

	initializeTriangles(removed, num);
	count = hiddenSurfaceRemoval(num, removed, t, s);
	sortTriangles(count, removed);
	
	for (int i = 0; i < count; i++) {
		// printf("\ntriangle %d\n", i);
		// t[i].g.x = (t[i].p[0].x + t[i].p[1].x + t[i].p[2].x)/3;
		// t[i].g.y = (t[i].p[0].y + t[i].p[1].y + t[i].p[2].y)/3;
		// t[i].g.z = (t[i].p[0].z + t[i].p[1].z + t[i].p[2].z)/3;
		// printf("g: (%.3lf %.3lf %.3lf)\n", t[i].g.x, t[i].g.y, t[i].g.z);

		rendered = renderTriangle(removed[i], s);
		// printf("rendered: (%d %d %d)\n", rendered.cp[0].c.r, rendered.cp[0].c.g, rendered.cp[0].c.b);

		paintTriangle(s.width, s.height, rendered);
	}
}