#include <stdio.h>
#include <process.h>
#include <math.h>

#define PI 3.14159265

/* BMPファイル用 */
typedef unsigned short WORD;
typedef unsigned int DWORD;

/* ビットマップデータ */
#define Y_SIZE 1024
#define X_SIZE 1024
unsigned char Pixel[Y_SIZE][X_SIZE][3];
