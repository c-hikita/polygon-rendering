// paintTriangle.c
// Chikako Hikita

void background() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			Pixel[i][j][0] = (unsigned char) 0;
			Pixel[i][j][1] = (unsigned char) 0;
			Pixel[i][j][2] = (unsigned char) 0;
		}
	}
}

double interpolate(double a, double b, double t) {
    return (1 - t) * a + t * b;
}

Color255 interpolateColor(Color255 c1, Color255 c2, double t) {
    Color255 result;
    result.r = (int)((1.0 - t) * c1.r + t * c2.r);
    result.g = (int)((1.0 - t) * c1.g + t * c2.g);
    result.b = (int)((1.0 - t) * c1.b + t * c2.b);
    return result;
}

int myMin(int a, int b) {
    return (a < b) ? a : b;
}

int myMax(int a, int b) {
    return (a > b) ? a : b;
}

// Paint a triangle using the Z-buffer
void paintTriangle(Rendered rendered) {
    int minX, maxX, minY, maxY;
    double lambda1, lambda2, lambda3;
    double lambda01, lambda02, lambda03;
    Vector p;

    ColorPlot v1 = rendered.cp[0];
    ColorPlot v2 = rendered.cp[1];
    ColorPlot v3 = rendered.cp[2];

    minX = myMin(v1.p.x, myMin(v2.p.x, v3.p.x));
    maxX = myMax(v1.p.x, myMax(v2.p.x, v3.p.x));
    minY = myMin(v1.p.y, myMin(v2.p.y, v3.p.y));
    maxY = myMax(v1.p.y, myMax(v2.p.y, v3.p.y));

    for (int y = minY; y <= maxY && y < HEIGHT; y++) {
        for (int x = minX; x <= maxX && x < WIDTH; x++) {
            p.x = x + 0.5;
            p.y = y + 0.5;

            lambda1 = ((v2.p.y - v3.p.y) * (p.x - v3.p.x) + (v3.p.x - v2.p.x) * (p.y - v3.p.y)) /
                             ((v2.p.y - v3.p.y) * (v1.p.x - v3.p.x) + (v3.p.x - v2.p.x) * (v1.p.y - v3.p.y));
            lambda2 = ((v3.p.y - v1.p.y) * (p.x - v3.p.x) + (v1.p.x - v3.p.x) * (p.y - v3.p.y)) /
                             ((v2.p.y - v3.p.y) * (v1.p.x - v3.p.x) + (v3.p.x - v2.p.x) * (v1.p.y - v3.p.y));
            lambda3 = 1.0 - lambda1 - lambda2;

            if (lambda1 >= 0 && lambda2 >= 0 && lambda3 >= 0) {
                double interpolatedZ = lambda1 * v1.p.z + lambda2 * v2.p.z + lambda3 * v3.p.z;

                if (interpolatedZ < ZBuffer[y][x]) {
                    ZBuffer[y][x] = interpolatedZ;

                    Color255 color1 = interpolateColor(v1.c, v2.c, lambda2 / (lambda1 + lambda2));
                    Color255 pixelColor = interpolateColor(color1, v3.c, lambda3);
                    pixelColor = clampColor(pixelColor);

                    Pixel[y][x][0] = pixelColor.r;
                    Pixel[y][x][1] = pixelColor.g;
                    Pixel[y][x][2] = pixelColor.b;
                }
            }
        }
    }
}
