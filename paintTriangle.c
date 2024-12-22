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

void paintTriangle(int width, int height, ColorPlot t[]) {
    // Sort the points by y-coordinate
    sortColorPlot(t);
    int xmin, xmax, ymin, ymax, fmin, fmax;
    int f[3]; // Intersection points of edges with scanlines
    int xsort[3] = { t[0].x, t[1].x, t[2].x };  // x coordinates of vertices
    sort3Points(xsort);  // Sorting x-coordinates

    ymin = t[0].y;
    ymax = t[2].y;

    // Determine which edge is horizontal and which vertices to process
    int eqmin = (ymin == t[1].y);
    int eqmax = (ymax == t[1].y);

    // Prepare to loop over each scanline between ymin and ymax
    for (int y = ymin; y <= ymax; y++) {
        // Calculate intersection points of edges with the current scanline
        for (int i = 0; i < 3; i++) {
            int next = (i + 1) % 3;  // Get next vertex index cyclically
            f[i] = t[i].x * (y - t[next].y) + t[next].x * (t[i].y - y);
            f[i] /= (t[i].y - t[next].y);  // Avoid division by zero
        }

        // Sort the intersection points for the current scanline
        sort3Points(f);

        // Determine the left and right intersection points for coloring
        if (y == ymin) {
            fmin = 0;
            for (int i = 0; i < 3; i++) {
                if (f[fmin] < xmin) fmin++;
            }
            fmax = fmin + 1;
        } else {
            if (y > t[1].y + 1) {
                fmin = 0;
                for (int i = 0; i < 3; i++) {
                    if (f[fmin] < xmin) fmin++;
                }
                fmax = fmin + 1;
            }
        }

        // Interpolate the colors across the scanline
        ColorPlot left, right;
        for (int i = 0; i < 3; i++) {
            int next = (i + 1) % 3;
            if (fmin == fmax) {
                left.r = t[i].r;
                left.g = t[i].g;
                left.b = t[i].b;
            } else {
                // Interpolate between the two points based on the y-position
                double div = 1.0;
                if (t[i].y != t[next].y) {
                    div = t[i].y - t[next].y;
                }
                left.r = (t[i].r * (y - t[next].y) + t[next].r * (t[i].y - y)) / div;
                left.g = (t[i].g * (y - t[next].y) + t[next].g * (t[i].y - y)) / div;
                left.b = (t[i].b * (y - t[next].y) + t[next].b * (t[i].y - y)) / div;
            }
        }

        // Apply shading logic and handle color interpolation
        for (int i = 0; i < 3; i++) {
            if (i < 2) next = i + 1;
            else next = 0;

            // Check for triangle orientation (upward or downward)
            if (t[0].y != xmax) {
                if (eqmin == 0) {
                    if (y == ymin) {
                        a1 = 0;    a2 = 0;
                        b1 = 0;    b2 = 0;
                    } else if (y < t[1].y) {
                        if (t[0].x != xmax) {
                            a2 = 2;
                            b2 = 1;
                        } else {
                            a2 = 1;
                            b2 = 2;
                        }
                    } else if (y == t[1].y) {
                        if (t[1].x != xmin) b1 = 1;
                        else                a1 = 1;
                    } else if (y < t[2].y) {
                        if (t[1].x != xmin) b2 = 2;
                        else                a2 = 2;
                    } else if (y == t[2].y) {
                        a1 = 2;    a2 = 2;
                        b1 = 2;    b2 = 2;
                    }
                }
            }
        }

        for (int i = 0; i < 3; i++) {
            if (tmp[i] < 0) tmp[i] = 0;
        }

        for (int i = 0; i < 3; i++) {
            if (tmp[i] < 0) tmp[i] = 0;
        }
    }
}
