#include "arr2d.h"


void arr2d() {
    int arr2d[ROWS][COLS] = {0};

    printArray2d(arr2d);
    saveArray2d(arr2d);
}

void printArray2d(int arr2d[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", arr2d[i][j]);
        }
        printf("\n");
    }
}

void saveArray2d(int arr2d[ROWS][COLS]) {
    FILE *fid;
    fid = fopen (MY_FILE, "w");
    if (fid != NULL) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                fprintf(fid, "%d ", arr2d[i][j]);
            }
            fprintf(fid, "\n");
        }
    }
}
