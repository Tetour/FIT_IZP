#include <stdio.h>

int main()
{
    int arr[5] = {0};
    int yarr[5] = {0};

    for (size_t i = 0; i < 5; i++) {
        scanf("%d", &arr[i]);
    }
    
    for (size_t i = 0, j = 4; i < 5; i++, j--) {
        yarr[j] = arr[i];
    }

    printf("\n");

    for (size_t i = 0; i < 5; i++)
    {
        printf("%d", yarr[i]);
    }

    printf("\n");

    return 0;
}
