// readFiles.c
// Chikako Hikita

int containsSubstring(const char* line, const char* substring) {
    int sub_len = 0;
    while (substring[sub_len] != '\0') {
        sub_len++;
    }

    while (*line) {
        if (strncmp(line, substring, sub_len) == 0) {
            return 1; 
        }
        line++;
    }
    return 0; 
}

void readSettings(FILE* file, Settings* screen) {
    fscanf(file, "camera = (%lf, %lf, %lf)\n", &screen->c.x, &screen->c.y, &screen->c.z);
    fscanf(file, "distance = %d\n", &screen->dist);
    fscanf(file, "ambience = (%lf, %lf, %lf)\n", &screen->a.r, &screen->a.g, &screen->a.b);
    fscanf(file, "iplot = (%lf, %lf, %lf)\n", &screen->world_i.x, &screen->world_i.y, &screen->world_i.z);
    fscanf(file, "icolor = (%lf, %lf, %lf)\n", &screen->icolor.r, &screen->icolor.g, &screen->icolor.b);
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
            fscanf(file, "point1 = (%lf, %lf, %lf)\n", &cubes[*cubeCount].p1.x, &cubes[*cubeCount].p1.y, &cubes[*cubeCount].p1.z);
            fscanf(file, "point2 = (%lf, %lf, %lf)\n", &cubes[*cubeCount].p2.x, &cubes[*cubeCount].p2.y, &cubes[*cubeCount].p2.z);
            fscanf(file, "color = (%d, %d, %d)\n", &cubes[*cubeCount].o.r, &cubes[*cubeCount].o.g, &cubes[*cubeCount].o.b);
            fscanf(file, "n = %d\n", &cubes[*cubeCount].n);
            fscanf(file, "Ka = %lf\n", &cubes[*cubeCount].k[0]);
            fscanf(file, "Kd = %lf\n", &cubes[*cubeCount].k[1]);
            fscanf(file, "Ks = %lf\n", &cubes[*cubeCount].k[2]);

            cubes[*cubeCount].num = 12;
            cubes[*cubeCount].centroid.x = (cubes[*cubeCount].p1.x + cubes[*cubeCount].p2.x) / 2;
            cubes[*cubeCount].centroid.y = (cubes[*cubeCount].p1.y + cubes[*cubeCount].p2.y) / 2;
            cubes[*cubeCount].centroid.z = (cubes[*cubeCount].p1.z + cubes[*cubeCount].p2.z) / 2;

            (*cubeCount)++;
        }

        // Read cylinder data
        if (currentPolygonType == 2) {
            fscanf(file, "radius = %lf\n", &cylinders[*cylinderCount].r);
            fscanf(file, "height = %lf\n", &cylinders[*cylinderCount].h);
            fscanf(file, "position = (%lf, %lf, %lf)\n", &cylinders[*cylinderCount].p.x, &cylinders[*cylinderCount].p.y, &cylinders[*cylinderCount].p.z);
            fscanf(file, "color = (%d, %d, %d)\n", &cylinders[*cylinderCount].o.r, &cylinders[*cylinderCount].o.g, &cylinders[*cylinderCount].o.b);
            fscanf(file, "n = %d\n", &cylinders[*cylinderCount].n);
            fscanf(file, "Ka = %lf\n", &cylinders[*cylinderCount].k[0]);
            fscanf(file, "Kd = %lf\n", &cylinders[*cylinderCount].k[1]);
            fscanf(file, "Ks = %lf\n", &cylinders[*cylinderCount].k[2]);

            cylinders[*cylinderCount].div = 24;
            cylinders[*cylinderCount].num = 4 * cylinders[*cylinderCount].div;

            cylinders[*cylinderCount].centroid = cylinders[*cylinderCount].p;
            cylinders[*cylinderCount].centroid.z += cylinders[*cylinderCount].h / 2;
            
            (*cylinderCount)++;
        }

        // Read sphere data
        if (currentPolygonType == 3) {
            fscanf(file, "radius = %lf\n", &spheres[*sphereCount].r);
            fscanf(file, "position = (%lf, %lf, %lf)\n", &spheres[*sphereCount].p.x, &spheres[*sphereCount].p.y, &spheres[*sphereCount].p.z);
            fscanf(file, "color = (%d, %d, %d)\n", &spheres[*sphereCount].o.r, &spheres[*sphereCount].o.g, &spheres[*sphereCount].o.b);
            fscanf(file, "n = %d\n", &spheres[*sphereCount].n);
            fscanf(file, "Ka = %lf\n", &spheres[*sphereCount].k[0]);
            fscanf(file, "Kd = %lf\n", &spheres[*sphereCount].k[1]);
            fscanf(file, "Ks = %lf\n", &spheres[*sphereCount].k[2]);

            spheres[*sphereCount].lat_div = 20;
            spheres[*sphereCount].long_div = 20;
            (*sphereCount)++;
        }
    }
}

void printSettings(Settings* screen) {
    printf("\nCurrent Settings:\n");
    printf("Camera position: (%.0lf, %.0lf, %.0lf)\n", screen->c.x, screen->c.y, screen->c.z);
    printf("Distance: %d\n", screen->dist);
    printf("Ambient color: (%.2lf, %.2lf, %.2lf)\n", screen->a.r, screen->a.g, screen->a.b);
    printf("I position: (%.0lf, %.0lf, %.0lf)\n", screen->world_i.x, screen->world_i.y, screen->world_i.z);
    printf("I color: (%.2lf, %.2lf, %.2lf)\n", screen->icolor.r, screen->icolor.g, screen->icolor.b);
}

void printPolygons(int cubeCount, Cube cubes[MAX_POLYGONS], int cylinderCount, Cylinder cylinders[MAX_POLYGONS], int sphereCount, Sphere spheres[MAX_POLYGONS]) {
    printf("\nCurrent Primitive:\n");
    for (int i = 0; i < cubeCount; i++) {
        printf("\nCube %d:\n", i + 1);
        printf("p1: (%.0lf, %.0lf, %.0lf) p2: (%.0lf, %.0lf, %.0lf)\n", cubes[i].p1.x, cubes[i].p1.y, cubes[i].p1.z, cubes[i].p2.x, cubes[i].p2.y, cubes[i].p2.z);
        printf("Color: (%d, %d, %d)\n", cubes[i].o.r, cubes[i].o.g, cubes[i].o.b);
        printf("n: %d Ka: %.2lf Kd: %.2lf Ks: %.2lf\n", cubes[i].n, cubes[i].k[0], cubes[i].k[1], cubes[i].k[2]);
    }

    for (int i = 0; i < cylinderCount; i++) {
        printf("\nCylinder %d:\n", i + 1);
        printf("Radius: %.2lf Height: %.2lf Position: (%.0lf, %.0lf, %.0lf)\n", cylinders[i].r, cylinders[i].h, cylinders[i].p.x, cylinders[i].p.y, cylinders[i].p.z);
        printf("Color: (%d, %d, %d)\n", cylinders[i].o.r, cylinders[i].o.g, cylinders[i].o.b);
        printf("n: %d Ka: %.2lf Kd: %.2lf Ks: %.2lf\nDiv: %d\n", cylinders[i].n, cylinders[i].k[0], cylinders[i].k[1], cylinders[i].k[2], cylinders[i].div);
    }

    for (int i = 0; i < sphereCount; i++) {
        printf("\nSphere %d:\n", i + 1);
        printf("Radius: %.2lf Position: (%.0lf, %.0lf, %.0lf)\n", spheres[i].r, spheres[i].p.x, spheres[i].p.y, spheres[i].p.z);
        printf("Color: (%d, %d, %d)\n", spheres[i].o.r, spheres[i].o.g, spheres[i].o.b);
        printf("n: %d Ka: %.2lf Kd: %.2lf Ks: %.2lf\nLatDiv: %d LongDiv: %d\n", spheres[i].n, spheres[i].k[0], spheres[i].k[1], spheres[i].k[2], spheres[i].lat_div, spheres[i].long_div);
    }
}

void printTransform(Transform tf) {
    printf("\nCurrent Transformation Values:\n");
    printf("Translation: (%.0f, %.0f, %.0f)\n", tf.translate.x, tf.translate.y, tf.translate.z);
    printf("Scale: %d%%\n", tf.scale);
    printf("Rotation: (%.0f, %.0f, %.0f)\n", tf.rotate.x, tf.rotate.y, tf.rotate.z);
}