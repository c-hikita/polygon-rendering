// calcVector
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