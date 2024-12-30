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