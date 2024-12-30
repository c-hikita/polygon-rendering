// paintTriangle.c
// Chikako Hikita

void background(int width, int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Pixel[i][j][0] = (unsigned char) 255;
			Pixel[i][j][1] = (unsigned char) 255;
			Pixel[i][j][2] = (unsigned char) 255;
		}
	}
}

// Helper function for linear interpolation
Color255 interpolateColor(Color255 c1, Color255 c2, double t) {
    Color255 result;
    result.r = (unsigned char)((1 - t) * c1.r + t * c2.r);
    result.g = (unsigned char)((1 - t) * c1.g + t * c2.g);
    result.b = (unsigned char)((1 - t) * c1.b + t * c2.b);
    return result;
}

// Function to render a triangle with Gouraud shading
void paintTriangle(int width, int height, Rendered rendered) {
    // unsigned char Pixel[height][width][3] = {0};

    // Extract vertices and colors
    ColorPlot v1 = rendered.cp[0];
    ColorPlot v2 = rendered.cp[1];
    ColorPlot v3 = rendered.cp[2];

    // Determine the bounding box for the triangle
    double minX = fmin(fmin(v1.p.x, v2.p.x), v3.p.x);
    double maxX = fmax(fmax(v1.p.x, v2.p.x), v3.p.x);
    double minY = fmin(fmin(v1.p.y, v2.p.y), v3.p.y);
    double maxY = fmax(fmax(v1.p.y, v2.p.y), v3.p.y);

    // Iterate through pixels in the bounding box
    for (int y = (int)ceil(minY); y <= (int)floor(maxY) && y < height; y++) {
        for (int x = (int)ceil(minX); x <= (int)floor(maxX) && x < width; x++) {
            Vector p = {x + 0.5, y + 0.5}; // Pixel center

            // Compute barycentric coordinates
            double lambda1 = ((v2.p.y - v3.p.y) * (p.x - v3.p.x) + (v3.p.x - v2.p.x) * (p.y - v3.p.y)) /
                             ((v2.p.y - v3.p.y) * (v1.p.x - v3.p.x) + (v3.p.x - v2.p.x) * (v1.p.y - v3.p.y));
            double lambda2 = ((v3.p.y - v1.p.y) * (p.x - v3.p.x) + (v1.p.x - v3.p.x) * (p.y - v3.p.y)) /
                             ((v2.p.y - v3.p.y) * (v1.p.x - v3.p.x) + (v3.p.x - v2.p.x) * (v1.p.y - v3.p.y));
            double lambda3 = 1.0 - lambda1 - lambda2;

            // If inside the triangle, interpolate color
            if (lambda1 >= 0 && lambda2 >= 0 && lambda3 >= 0) {
                Color255 pixelColor = interpolateColor(
                    interpolateColor(v1.c, v2.c, lambda2 / (lambda1 + lambda2)),
                    v3.c,
                    lambda3
                );

                // Set the pixel color
                Pixel[y][x][0] = pixelColor.r;
                Pixel[y][x][1] = pixelColor.g;
                Pixel[y][x][2] = pixelColor.b;
            }
        }
    }
}
