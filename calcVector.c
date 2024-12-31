﻿// calcVector
// Chikako Hikita

// 引き算
Vector subtract(Vector a, Vector b) {
    Vector result = {a.x - b.x, a.y - b.y, a.z - b.z};
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
    printf("*** normalVector ***\n");
    Vector n, u1, u2, reference;
    double test;

    // printf("ref = (%.3lf, %.3lf, %.3lf)\n", t.ref.x, t.ref.y, t.ref.z); 

    u1 = subtract(t.p[1], t.p[0]);
    u2 = subtract(t.p[2], t.p[0]);
    n = crossProduct(u2, u1);
	n = normalize(n);

    printf("N = (%.3lf, %.3lf, %.3lf)\n", n.x, n.y, n.z); 

    if (abs(n.x) == 1 || abs(n.y) == 1 || abs(n.z) == 1) {
        reference = subtract(t.g, t.ref);
        reference = normalize(reference);
        printf("ref = (%.3lf, %.3lf, %.3lf)\n", reference.x, reference.y, reference.z); 

        test = dotProduct(n, reference);
        printf("test: %.3lf\n", test);
        
        if (test < 0) {
            n.x = - n.x;
            n.y = - n.y;
            n.z = - n.z;
        }
        
        printf("N = (%.3lf, %.3lf, %.3lf)\n", n.x, n.y, n.z); 
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