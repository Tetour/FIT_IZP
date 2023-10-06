#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    int a = 5;
    int b = 2;
    int c = 4;
    int d;
    double x1, x2;

    d = b*b - 4*a*c;

    if (d > 0) {
        x1 = (-b + sqrt(d))/(2*a);
        x2 = (-b - sqrt(d))/(2*a);
        printf("dva koreny, x1 = %f, x2 = %f", x1, x2);
    } else if (d == 0) {
        x1 = (-b)/(2*a);
        printf("jeden koren, x1 = %f", x1);
    } else if (d < 0) {
        // TODO: finish complex root
    }

    return 0;
}
