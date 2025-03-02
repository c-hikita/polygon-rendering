/** 
 * @file bmpout.c
 * @brief BMP file output and pixel data processing
 * This file contains functions to output 24-bit bitmap (BMP) data to a file and to store RGB pixel data 
 * in an array for BMP file creation.
 */

/**
 * @brief Write a 24-bit bitmap (BMP) file
 * This function outputs 24-bit bitmap data stored in an unsigned char array to a BMP file. It 
 * constructs the BMP header and pixel data and writes them to the specified file.
 * The file is created in binary write mode ("wb").
 *
 * @param filename The name of the BMP file to output the data to
 * @param width The width of the image in pixels
 * @param height The height of the image in pixels
 * 
 * @note The BMP file header and information header are written first, followed by 
 *       the pixel data. The pixel data is written in reverse order (BGR) as required by the BMP format.
 */
void bmpout(char *filename, int width, int height)
{
    FILE *fp;
    int i, j, k;

    WORD bfType           = 19778; // BM in hexadecimal
    DWORD bfSize;
    WORD bfReserved1      = 0,
         bfReserved2      = 0;
    DWORD bfOffBits       = 54; // Offset to pixel data
    DWORD biSize          = 40, // Size of the BITMAPINFOHEADER
          biWidth, biHeight;
    WORD biPlanes         = 1,
         biBitCount       = 24; // 24 bits per pixel
    DWORD biCompression   = 0, 
          biSizeImage, 
          biXPelsPerMeter = 3780, // Horizontal resolution in pixels per meter
          biYPelsPerMeter = 3780, // Vertical resolution in pixels per meter
          biClrUsed       = 0, 
          biClrImportant  = 0;
    
    biWidth     = width;
    biHeight    = height;
    biSizeImage = 3 * biWidth * biHeight; // 3 bytes per pixel (RGB)
    bfSize      = biSizeImage + bfOffBits;

    // Open the file for writing in binary mode
    if ((fp = fopen(filename, "wb")) == NULL) {
        printf("Open error!\n");
        exit(1);
    }
    printf("output file : %s\n", filename);

    // Write the BMP header
    fwrite(&bfType, sizeof(bfType), 1, fp);
    fwrite(&bfSize, sizeof(bfSize), 1, fp);
    fwrite(&bfReserved1, sizeof(bfReserved1), 1, fp);
    fwrite(&bfReserved2, sizeof(bfReserved2), 1, fp);
    fwrite(&bfOffBits, sizeof(bfOffBits), 1, fp);

    // Write the BMP information header
    fwrite(&biSize, sizeof(biSize), 1, fp);
    fwrite(&biWidth, sizeof(biWidth), 1, fp);
    fwrite(&biHeight, sizeof(biHeight), 1, fp);
    fwrite(&biPlanes, sizeof(biPlanes), 1, fp);
    fwrite(&biBitCount, sizeof(biBitCount), 1, fp);
    fwrite(&biCompression, sizeof(biCompression), 1, fp);
    fwrite(&biSizeImage, sizeof(biSizeImage), 1, fp);
    fwrite(&biXPelsPerMeter, sizeof(biXPelsPerMeter), 1, fp);
    fwrite(&biYPelsPerMeter, sizeof(biYPelsPerMeter), 1, fp);
    fwrite(&biClrUsed, sizeof(biClrUsed), 1, fp);
    fwrite(&biClrImportant, sizeof(biClrImportant), 1, fp);

    // Write the bitmap pixel data
    for (i = 0; i < biHeight; i++) {
        for (j = 0; j < biWidth; j++) {
            for (k = 0; k < 3; k++) {
                fwrite(&Pixel[i][j][2 - k], 1, 1, fp); // Write BGR in reverse order
            }
        }
    }

    // Close the file after writing
    fclose(fp);
}

/**
 * @brief Store RGB pixel data as unsigned char values
 * This function converts RGB data in the range [0.0, 1.0] to the range [0, 255] 
 * and stores the result in the Pixel array for the specified pixel location (u, v).
 * The data is clipped to ensure it falls within the range [0, 255].
 *
 * @param u The horizontal pixel coordinate (column)
 * @param v The vertical pixel coordinate (row)
 * @param rgb An array containing the RGB color values in the range [0.0, 1.0]
 * 
 * @note The function stores the resulting values in the `Pixel[v][u][3]` array, 
 *       where the values are converted and clipped to the appropriate range.
 */
void storePixel(int u, int v, double rgb[])
{
    int i;
    int c;
    
    // Convert and clip RGB values to the range [0, 255]
    for (i = 0; i < 3; i++) {
        c = 255 * rgb[i];
        if (c < 0) c = 0;
        if (c > 255) c = 255;
        Pixel[v][u][i] = (unsigned char)c;
    }
}