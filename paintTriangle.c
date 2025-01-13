// paintTriangle.c
// Chikako Hikita

void background(int width, int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
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
void paintTriangle(int width, int height, Rendered rendered) {
    ColorPlot v1 = rendered.cp[0];
    ColorPlot v2 = rendered.cp[1];
    ColorPlot v3 = rendered.cp[2];

    int minX = myMin(v1.p.x, myMin(v2.p.x, v3.p.x));
    int maxX = myMax(v1.p.x, myMax(v2.p.x, v3.p.x));
    int minY = myMin(v1.p.y, myMin(v2.p.y, v3.p.y));
    int maxY = myMax(v1.p.y, myMax(v2.p.y, v3.p.y));

    for (int y = minY; y <= maxY && y < height; y++) {
        for (int x = minX; x <= maxX && x < width; x++) {
            Vector p = {x + 0.5, y + 0.5};

            double lambda1 = ((v2.p.y - v3.p.y) * (p.x - v3.p.x) + (v3.p.x - v2.p.x) * (p.y - v3.p.y)) /
                             ((v2.p.y - v3.p.y) * (v1.p.x - v3.p.x) + (v3.p.x - v2.p.x) * (v1.p.y - v3.p.y));
            double lambda2 = ((v3.p.y - v1.p.y) * (p.x - v3.p.x) + (v1.p.x - v3.p.x) * (p.y - v3.p.y)) /
                             ((v2.p.y - v3.p.y) * (v1.p.x - v3.p.x) + (v3.p.x - v2.p.x) * (v1.p.y - v3.p.y));
            double lambda3 = 1.0 - lambda1 - lambda2;

            if (lambda1 >= 0 && lambda2 >= 0 && lambda3 >= 0) {
                // Interpolate the depth
                double interpolatedZ = lambda1 * v1.p.z + lambda2 * v2.p.z + lambda3 * v3.p.z;

                // Check Z-buffer: Update only if this pixel is closer
                if (interpolatedZ < ZBuffer[y][x]) {
                    ZBuffer[y][x] = interpolatedZ; // Update Z-buffer

                    // Interpolate the color
                    Color255 color1 = interpolateColor(v1.c, v2.c, lambda2 / (lambda1 + lambda2));
                    Color255 pixelColor = interpolateColor(color1, v3.c, lambda3);
                    pixelColor = clampColor(pixelColor);

                    // Set the pixel color
                    Pixel[y][x][0] = pixelColor.r;
                    Pixel[y][x][1] = pixelColor.g;
                    Pixel[y][x][2] = pixelColor.b;
                }
            }
        }
    }
}


// // 三角形の塗りつぶし
// void paintTriangle(int width, int height, Rendered rendered) {
//     ColorPlot v1 = rendered.cp[0];
//     ColorPlot v2 = rendered.cp[1];
//     ColorPlot v3 = rendered.cp[2];

//     int minX = myMin(v1.p.x, myMin(v2.p.x, v3.p.x));
//     int maxX = myMax(v1.p.x, myMax(v2.p.x, v3.p.x));
//     int minY = myMin(v1.p.y, myMin(v2.p.y, v3.p.y));
//     int maxY = myMax(v1.p.y, myMax(v2.p.y, v3.p.y));

//     for (int y = minY; y <= maxY && y < height; y++) {
//         for (int x = minX; x <= maxX && x < width; x++) {
//             Vector p = {x + 0.5, y + 0.5};

//             double lambda1 = ((v2.p.y - v3.p.y) * (p.x - v3.p.x) + (v3.p.x - v2.p.x) * (p.y - v3.p.y)) /
//                              ((v2.p.y - v3.p.y) * (v1.p.x - v3.p.x) + (v3.p.x - v2.p.x) * (v1.p.y - v3.p.y));
//             double lambda2 = ((v3.p.y - v1.p.y) * (p.x - v3.p.x) + (v1.p.x - v3.p.x) * (p.y - v3.p.y)) /
//                              ((v2.p.y - v3.p.y) * (v1.p.x - v3.p.x) + (v3.p.x - v2.p.x) * (v1.p.y - v3.p.y));
//             double lambda3 = 1.0 - lambda1 - lambda2;

//             if (lambda1 >= 0 && lambda2 >= 0 && lambda3 >= 0) {
//                 Color255 color1 = interpolateColor(v1.c, v2.c, lambda2 / (lambda1 + lambda2));
//                 Color255 pixelColor = interpolateColor(color1, v3.c, lambda3);
//                 pixelColor = clampColor(pixelColor);
                
//                 Pixel[y][x][0] = pixelColor.r;
//                 Pixel[y][x][1] = pixelColor.g;
//                 Pixel[y][x][2] = pixelColor.b;
//             }
//         }
//     }
// }