// renderTriangle.c
// Chikako Hikita

// 透視投影
projection(Vector t[], Vector rtn[], Vector c, int d) {
	for (int i = 0; i < 3; i++) {
		rtn[i].x = d * t[i].x;
		rtn[i].y = d * t[i].y;

		if (t[i].z + c.x != 0) rtn[i].x /= (t[i].z + c.x);
		if (t[i].z + c.y != 0) rtn[i].y /= (t[i].z + c.y);

		/*
		if (t[i].z != 0) {
			rtn[i].x /= t[i].z;
			rtn[i].y /= t[i].z;
		}
		*/
		rtn[i].z = d;
	}
}

void calcColor(Triangle3D t, Color255 rtn[], Settings s) {
    // Vector u1, u2;	// 三角平面のベクトル
	// Plot plot[3] = {t.p1, t.p2, t.p3};

	double color[3];	// 表示色[0,1]
	// double nsize, vsize, lsize, rsize;	// ベクトルの大きさ
	double ln, rv;	// 内積

	// 三角形の元の色[0,1]
	Color1 o1;

	// 法線ベクトルN, 視線V, 光源への方向ベクトルL, 正反射ベクトルR;
	Vector n, v, l, r;

	// 物体の元の色Oを[0,255]から[0,1]に変換
	o1.r = (double)t.o.r / 255;
	o1.g = (double)t.o.g / 255;
	o1.b = (double)t.o.b / 255;

	// 3角形面の法線ベクトルNの算出
	// n = normalVector(t);
	// printf("N = (%.3lf, %.3lf, %.3lf)\n", n.x, n.y, n.z); 

	/*
	u1 = subtract(t.p[1], t.p[0]);
    u2 = subtract(t.p[2], t.p[0]);
    n = crossProduct(u2, u1);
	n = normalize(n);
	*/

	// Calculate lighting for each vertex
	for (int i = 0; i < 3; i++) {
		n = t.v[i];
		n = normalize(n);
		// printf("n: (%.2lf %.2lf %.2lf)\n", n.x, n.y, n.z);

		// Normalize vectors
		v = subtract(s.c, t.p[i]);
		v = normalize(v);

		l = subtract(s.iplot, t.p[i]);
		l = normalize(l);

		ln = dotProduct(l, n);
		ln = fmax(ln, 0.0); // Clamp diffuse component

		r.x = 2 * ln * n.x - l.x;
		r.y = 2 * ln * n.y - l.y;
		r.z = 2 * ln * n.z - l.z;
		r = normalize(r);

		rv = dotProduct(r, v);
		rv = fmax(rv, 0.0); // Clamp specular component

		double specular = (rv > 0) ? pow(rv, t.n) : 0.0;

		// Calculate color components
		color[0] = t.k[0] * o1.r * s.a.r + t.k[1] * o1.r * s.icolor.r * ln + t.k[2] * s.icolor.r * specular;
		color[1] = t.k[0] * o1.g * s.a.g + t.k[1] * o1.g * s.icolor.g * ln + t.k[2] * s.icolor.g * specular;
		color[2] = t.k[0] * o1.b * s.a.b + t.k[1] * o1.b * s.icolor.b * ln + t.k[2] * s.icolor.b * specular;

		// Clamp to [0, 255]
		rtn[i].r = (int)(fmax(0, fmin(255, color[0] * 255)));
		rtn[i].g = (int)(fmax(0, fmin(255, color[1] * 255)));
		rtn[i].b = (int)(fmax(0, fmin(255, color[2] * 255)));

		// printf("(r,g,b) = (%d, %d, %d)\n", rtn[i].r, rtn[i].g, rtn[i].b);
	}
}

Rendered renderTriangle(Triangle3D tri3, Settings s) {
    Rendered rtn;
    Vector before[3], after[3];
    Color255 color[3];

    for (int i = 0; i < 3; i++) {
        before[i] = tri3.p[i];
    }

    projection(before, after, s.c, s.d);
    calcColor(tri3, color, s);

    for (int i = 0; i < 3; i++) {
        rtn.cp[i].p = after[i];
        rtn.cp[i].c = color[i];
    }

    rtn.g = calcCentroid(after);

    return rtn;
}