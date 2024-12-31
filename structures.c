// structures.c
// Chikako Hikita

typedef struct {
	double x;
	double y;
	double z;
} Vector;

typedef struct {
	double r;
	double g;
	double b;
} Color1;

typedef struct {
	int r;
	int g;
	int b;
} Color255;

typedef struct {
	Vector p;
    Color255 c;
} ColorPlot;

typedef struct {
	Vector p[3];
	Color255 o;
	int n;
	double k[3];
	Vector g;
	Vector ref;
} Triangle3D;

typedef struct {
	ColorPlot cp[3];
	Vector g;
} Rendered;

typedef struct {
	int width, height;	// スクリーンの大きさ
	Vector c;				// 視点C
	int d;				// 焦点距離d
	Vector iplot;			// 光源Iの位置
	Color1 icolor, a;	// 光源Iの色, 環境光
} Settings;

typedef struct {
	Vector p1, p2;
	Vector centroid;
	// int x1;	int y1;	int z1;
	// int x2; int y2; int z2;
	Color255 o;
	int n;
	double k[3];
	int num;
} Cube;

typedef struct {
	int r;
	int h;
	int x;	int y; int z;
	Color255 o;
	int n;
	double k[3];
	int div;
	int num;
} Cylinder;

typedef struct {
	int r;
	int x; int y; int z;
} Sphere;