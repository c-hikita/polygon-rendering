// structures.c
// Chikako Hikita

typedef struct {
	double x, y, z;
} Vector;

/*
typedef struct {
    double x, y, z, w;
} Vector4;
*/

typedef struct {
	double r, g, b;
} Color1;

typedef struct {
	int r, g, b;
} Color255;

typedef struct {
	Vector p;
    Color255 c;
} ColorPlot;

/*
typedef struct {
    double m[4][4];
} Matrix4x4;
*/

typedef struct {
	Vector v[6];
	int count;
} NormalVectors;

typedef struct {
	Vector p[3], v[3];
	Color255 o;
	int n;
	double k[3];
	Vector g, ref; 
	int id; // 1: cube, 2: cylinder, 3: sphere
} Triangle3D;

typedef struct {
	ColorPlot cp[3];
	Vector g;
} Rendered;

typedef struct {
	int width, height;	// スクリーンの大きさ
	Vector c, d;		// 視点C, 見る点D
	int dist;				// 焦点距離d
	Vector iplot;			// 光源Iの位置
	Color1 icolor, a;	// 光源Iの色, 環境光
} Settings;

typedef struct {
	Vector translate;
	int scale;
	Vector rotate;
} Transform;

typedef struct {
	Vector p1, p2, centroid;
	Color255 o;
	int n;
	double k[3];
	int num;
} Cube;

typedef struct {
	double r, h;
	Vector p, centroid;
	Color255 o;
	int n;
	double k[3];
	int div, num;
} Cylinder;

typedef struct {
	double r;
	Vector p;
	Color255 o;
	int n;
	double k[3];
	int lat_div, long_div, num;
} Sphere;