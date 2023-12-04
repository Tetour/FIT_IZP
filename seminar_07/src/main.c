#include "main.h"


#define ARR_LEN 5


config_t conf = {
    .x = false,
    .y = false,
    .s = NULL,
    .n = 0,
};


int main(int argc, char *argv[])
{
    int arr[ARR_LEN] = {1, 2, 3, 4, 5};

    printArr(arr, ARR_LEN);

    multiArr(arr, ARR_LEN, 3);
    printArr(arr, ARR_LEN);

    vector_t vect;

    initVector(&vect, 5);

    return 0;
}

int initVector(vector_t * vect, int size) {
    (*vect).data = calloc(size * sizeof(double), 5);
    if (vect->data == NULL) {
        vect->size = 0;
        return 1;
    } else {
        vect->size = size;
        return 0;
    }

}

int parseArg(int argc, char ** argv) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-x") == 0) {
            conf.x = true;
        }
        if (strcmp(argv[i], "-y") == 0) {
            conf.y = true;
        }
        if (strcmp(argv[i], "-s") == 0) {
            if (i+1 < argc) {
                i++;
                conf.s = argv[i];
            } else {
                return 0;
            }
        }
    }

    if ((conf.x == true) && (conf.y == true)) {
        printf("ERROR: You can only select -x or -y, not both.");
        exit(1);
    }
}

void printCfg(config_t conf) {
    printf("%s\n", conf.x);
    printf("%s\n", conf.y);
    printf("%s\n", conf.s);
    printf("%d\n", conf.n);
}

void printArr(int * arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void multiArr(int * arr, int size, int multi) {
    for (int i = 0; i < size; i++) {
        arr[i] *= multi; 
    }
}
