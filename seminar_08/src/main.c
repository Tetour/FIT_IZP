#include "main.h"


int main(int argc, char *argv[])
{
    vector_t vect_1;
    vector_t vect_2;

    vector_init(&vect_1, 3);
    vector_init(&vect_2, 4);

    vector_print(&vect_1);
    vector_print(&vect_2);

    vector_merge(&vect_1, &vect_2);

    vector_print(&vect_1);

    return 0;
}

int vector_init(vector_t * vect, int size) {
    int retVal = 1;

    vect->data = calloc(size, sizeof(double));
    if (vect->data == NULL) {
        vect->size = 0;
        retVal = 1;
    } else {
        vect->size = size;
        retVal = 0;
    }
    return retVal;
}

int vector_print(vector_t * vect) {
    int retVal = 1;

    if (vect != NULL) {
        printf("Vector size: %d\n", vect->size);
        printf("Vector data: ");
        for (int i = 0; i < vect->size; i++) {
            printf("%.0lf ", vect->data[i]);
        }
        printf("\n");
        retVal = 0;
    }
    return retVal;
}

int vector_merge(vector_t * v_1, vector_t * v_2) {
    int retVal = 1;

    v_1->data = realloc(v_1->data, (v_1->size + v_2->size)*sizeof(double));
    if (v_1->data == NULL) {
        retVal = 1;
    } else {
        for (int i = 0; i < v_2->size; i++) {
        v_1->data[v_1->size + i] = v_2->data[i];
        }
        v_1->size += v_2->size;
        retVal = 0;
    }
    return retVal;
}

