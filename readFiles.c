// readFiles.c
// Chikako Hikita

// Manually check if a substring exists in a string
int containsSubstring(const char* line, const char* substring) {
    int sub_len = 0;
    // Find length of substring manually
    while (substring[sub_len] != '\0') {
        sub_len++;
    }

    while (*line) {
        if (strncmp(line, substring, sub_len) == 0) {
            return 1;  // Substring found
        }
        line++;
    }
    return 0;  // Substring not found
}

void readSettings(FILE* file, Settings* screen) {
    fscanf(file, "screen_width = %d\n", &screen->width);
    fscanf(file, "screen_height = %d\n", &screen->height);
    fscanf(file, "camera_x = %lf\n", &screen->c.x);
    fscanf(file, "camera_y = %lf\n", &screen->c.y);
    fscanf(file, "camera_z = %lf\n", &screen->c.z);
    fscanf(file, "distance = %d\n", &screen->d);
    fscanf(file, "ambient_r = %lf\n", &screen->a.r);
    fscanf(file, "ambient_g = %lf\n", &screen->a.g);
    fscanf(file, "ambient_b = %lf\n", &screen->a.b);
    fscanf(file, "iplot_x = %lf\n", &screen->iplot.x);
    fscanf(file, "iplot_y = %lf\n", &screen->iplot.y);
    fscanf(file, "iplot_z = %lf\n", &screen->iplot.z);
    fscanf(file, "icolor_r = %lf\n", &screen->icolor.r);
    fscanf(file, "icolor_g = %lf\n", &screen->icolor.g);
    fscanf(file, "icolor_b = %lf\n", &screen->icolor.b);
}

void readPolygons(FILE* file, Cube cubes[MAX_POLYGONS], int* cubeCount, Cylinder cylinders[MAX_POLYGONS], int* cylinderCount, Sphere spheres[MAX_POLYGONS], int* sphereCount) {
    char line[256];
    char currentPolygonType = 0; // 1: Cube, 2: Cylinder, 3: Sphere

    *cubeCount = 0;
    *cylinderCount = 0;
    *sphereCount = 0;

    while (fgets(line, sizeof(line), file)) {
        if (containsSubstring(line, "# Cube")) {
            currentPolygonType = 1;
        } else if (containsSubstring(line, "# Cylinder")) {
            currentPolygonType = 2;
        } else if (containsSubstring(line, "# Sphere")) {
            currentPolygonType = 3;
        }

        // Read cube data
        if (currentPolygonType == 1) {
            fscanf(file, "cube_p1_x = %lf\n", &cubes[*cubeCount].p1.x);
            fscanf(file, "cube_p1_y = %lf\n", &cubes[*cubeCount].p1.y);
            fscanf(file, "cube_p1_z = %lf\n", &cubes[*cubeCount].p1.z);
            fscanf(file, "cube_p2_x = %lf\n", &cubes[*cubeCount].p2.x);
            fscanf(file, "cube_p2_y = %lf\n", &cubes[*cubeCount].p2.y);
            fscanf(file, "cube_p2_z = %lf\n", &cubes[*cubeCount].p2.z);
            fscanf(file, "cube_color_r = %d\n", &cubes[*cubeCount].o.r);
            fscanf(file, "cube_color_g = %d\n", &cubes[*cubeCount].o.g);
            fscanf(file, "cube_color_b = %d\n", &cubes[*cubeCount].o.b);
            fscanf(file, "cube_n = %d\n", &cubes[*cubeCount].n);
            fscanf(file, "cube_k0 = %lf\n", &cubes[*cubeCount].k[0]);
            fscanf(file, "cube_k1 = %lf\n", &cubes[*cubeCount].k[1]);
            fscanf(file, "cube_k2 = %lf\n", &cubes[*cubeCount].k[2]);
            fscanf(file, "cube_num = %d\n", &cubes[*cubeCount].num);
            (*cubeCount)++;
        }

        // Read cylinder data
        if (currentPolygonType == 2) {
            fscanf(file, "cylinder_radius = %lf\n", &cylinders[*cylinderCount].r);
            fscanf(file, "cylinder_height = %lf\n", &cylinders[*cylinderCount].h);
            fscanf(file, "cylinder_pos_x = %lf\n", &cylinders[*cylinderCount].p.x);
            fscanf(file, "cylinder_pos_y = %lf\n", &cylinders[*cylinderCount].p.y);
            fscanf(file, "cylinder_pos_z = %lf\n", &cylinders[*cylinderCount].p.z);
            fscanf(file, "cylinder_color_r = %d\n", &cylinders[*cylinderCount].o.r);
            fscanf(file, "cylinder_color_g = %d\n", &cylinders[*cylinderCount].o.g);
            fscanf(file, "cylinder_color_b = %d\n", &cylinders[*cylinderCount].o.b);
            fscanf(file, "cylinder_n = %d\n", &cylinders[*cylinderCount].n);
            fscanf(file, "cylinder_k0 = %lf\n", &cylinders[*cylinderCount].k[0]);
            fscanf(file, "cylinder_k1 = %lf\n", &cylinders[*cylinderCount].k[1]);
            fscanf(file, "cylinder_k2 = %lf\n", &cylinders[*cylinderCount].k[2]);
            fscanf(file, "cylinder_div = %d\n", &cylinders[*cylinderCount].div);
            fscanf(file, "cylinder_num = %d\n", &cylinders[*cylinderCount].num);
            (*cylinderCount)++;
        }

        // Read sphere data
        if (currentPolygonType == 3) {
            fscanf(file, "sphere_radius = %lf\n", &spheres[*sphereCount].r);
            fscanf(file, "sphere_pos_x = %lf\n", &spheres[*sphereCount].p.x);
            fscanf(file, "sphere_pos_y = %lf\n", &spheres[*sphereCount].p.y);
            fscanf(file, "sphere_pos_z = %lf\n", &spheres[*sphereCount].p.z);
            fscanf(file, "sphere_color_r = %d\n", &spheres[*sphereCount].o.r);
            fscanf(file, "sphere_color_g = %d\n", &spheres[*sphereCount].o.g);
            fscanf(file, "sphere_color_b = %d\n", &spheres[*sphereCount].o.b);
            fscanf(file, "sphere_n = %d\n", &spheres[*sphereCount].n);
            fscanf(file, "sphere_k0 = %lf\n", &spheres[*sphereCount].k[0]);
            fscanf(file, "sphere_k1 = %lf\n", &spheres[*sphereCount].k[1]);
            fscanf(file, "sphere_k2 = %lf\n", &spheres[*sphereCount].k[2]);
            fscanf(file, "sphere_lat_div = %d\n", &spheres[*sphereCount].lat_div);
            fscanf(file, "sphere_long_div = %d\n", &spheres[*sphereCount].long_div);
            (*sphereCount)++;
        }
    }
}

void printSettings(Settings* screen) {
    printf("\nSettings:\n");
    printf("Width: %d, Height: %d\n", screen->width, screen->height);
    printf("Camera position: (%.2lf, %.2lf, %.2lf)\n", screen->c.x, screen->c.y, screen->c.z);
    printf("Distance: %d\n", screen->d);
    printf("Ambient color: (%.2lf, %.2lf, %.2lf)\n", screen->a.r, screen->a.g, screen->a.b);
    printf("Iplot position: (%.2lf, %.2lf, %.2lf)\n", screen->iplot.x, screen->iplot.y, screen->iplot.z);
    printf("Icolor: (%.2lf, %.2lf, %.2lf)\n", screen->icolor.r, screen->icolor.g, screen->icolor.b);
}

void printPolygons(int cubeCount, Cube cubes[MAX_POLYGONS], int cylinderCount, Cylinder cylinders[MAX_POLYGONS], int sphereCount, Sphere spheres[MAX_POLYGONS]) {
    printf("\nCubes:\n");
	printf("cubecont: %d\n", cubeCount);
    for (int i = 0; i < cubeCount; i++) {
        printf("Cube %d:\n", i + 1);
        printf("p1: (%.2lf, %.2lf, %.2lf) p2: (%.2lf, %.2lf, %.2lf)\n", cubes[i].p1.x, cubes[i].p1.y, cubes[i].p1.z, cubes[i].p2.x, cubes[i].p2.y, cubes[i].p2.z);
        printf("Color: (%d, %d, %d)\n", cubes[i].o.r, cubes[i].o.g, cubes[i].o.b);
        printf("n: %d k: (%.2lf, %.2lf, %.2lf) num: %d\n", cubes[i].n, cubes[i].k[0], cubes[i].k[1], cubes[i].k[2], cubes[i].num);
    }

    printf("\nCylinders:\n");
    for (int i = 0; i < cylinderCount; i++) {
        printf("Cylinder %d:\n", i + 1);
        printf("Radius: %.2lf Height: %.2lf Position: (%.2lf, %.2lf, %.2lf)\n", cylinders[i].r, cylinders[i].h, cylinders[i].p.x, cylinders[i].p.y, cylinders[i].p.z);
        printf("Color: (%d, %d, %d)\n", cylinders[i].o.r, cylinders[i].o.g, cylinders[i].o.b);
        printf("n: %d k: (%.2lf, %.2lf, %.2lf) Div: %d num: %d\n", cylinders[i].n, cylinders[i].k[0], cylinders[i].k[1], cylinders[i].k[2], cylinders[i].div, cylinders[i].num);
    }

    printf("\nSpheres:\n");
    for (int i = 0; i < sphereCount; i++) {
        printf("Sphere %d:\n", i + 1);
        printf("Radius: %.2lf Position: (%.2lf, %.2lf, %.2lf)\n", spheres[i].r, spheres[i].p.x, spheres[i].p.y, spheres[i].p.z);
        printf("Color: (%d, %d, %d)\n", spheres[i].o.r, spheres[i].o.g, spheres[i].o.b);
        printf("n: %d k: (%.2lf, %.2lf, %.2lf) LatDiv: %d LongDiv: %d\n", spheres[i].n, spheres[i].k[0], spheres[i].k[1], spheres[i].k[2], spheres[i].lat_div, spheres[i].long_div);
    }
}