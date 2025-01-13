// renderTriangle.c
// Chikako Hikita

// 透視投影
projection(Vector t[], Vector rtn[], int d) {
	for (int i = 0; i < 3; i++) {
		double dz;
		if (t[i].z != 0) dz = d / t[i].z;

		rtn[i].x = dz * t[i].x;
		rtn[i].y = dz * t[i].y;
		rtn[i].z = t[i].z;
	}
}

// 各頂点の輝度計算
void calcColor(Triangle3D t, Color255 rtn[], Settings s) {
	double color[3];	
	double ln, rv;

	Color1 o1;	// 三角形の元の色[0,1]
	Vector n, v, l, r;	// 法線ベクトルN, 視線V, 光源への方向ベクトルL, 正反射ベクトルR;

	o1.r = (double)t.o.r / 255;
	o1.g = (double)t.o.g / 255;
	o1.b = (double)t.o.b / 255;

	for (int i = 0; i < 3; i++) {
		n = t.v[i];
		n = normalize(n);

		v = subtract(s.c, t.p[i]);
		v = normalize(v);

		l = subtract(s.camera_i, t.p[i]);
		l = normalize(l);

		ln = dotProduct(l, n);
		ln = fmax(ln, 0.0);

		r.x = 2 * ln * n.x - l.x;
		r.y = 2 * ln * n.y - l.y;
		r.z = 2 * ln * n.z - l.z;
		r = normalize(r);

		rv = dotProduct(r, v);
		rv = fmax(rv, 0.0); 

		double specular = (rv > 0) ? pow(rv, t.n) : 0.0;

		color[0] = t.k[0] * o1.r * s.a.r + t.k[1] * o1.r * s.icolor.r * ln + t.k[2] * s.icolor.r * specular;
		color[1] = t.k[0] * o1.g * s.a.g + t.k[1] * o1.g * s.icolor.g * ln + t.k[2] * s.icolor.g * specular;
		color[2] = t.k[0] * o1.b * s.a.b + t.k[1] * o1.b * s.icolor.b * ln + t.k[2] * s.icolor.b * specular;

		rtn[i].r = (int)(fmax(0, fmin(255, color[0] * 255)));
		rtn[i].g = (int)(fmax(0, fmin(255, color[1] * 255)));
		rtn[i].b = (int)(fmax(0, fmin(255, color[2] * 255)));
	}
}

// 三角形のレンダリング
Rendered renderTriangle(Triangle3D tri3, Settings s) {
    Rendered rtn;
    Vector before[3], after[3];
    Color255 color[3];

    for (int i = 0; i < 3; i++) {
        before[i] = tri3.p[i];
    }

    projection(before, after, s.dist);
	calcColor(tri3, color, s);

    for (int i = 0; i < 3; i++) {
        rtn.cp[i].p = after[i];
        rtn.cp[i].c = color[i];
    }

    rtn.g = calcCentroid(after);

    return rtn;
}