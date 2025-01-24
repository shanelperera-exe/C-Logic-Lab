#include <stdio.h>

void swap(int *a, int *b);

int main(void) {
    int a, b;

    printf("a: ");
    scanf("%d", &a);

    printf("b: ");
    scanf("%d", &b);

    printf("Before swap: a = %d, b = %d\n", a,b);
    swap(&a, &b);

    printf("After swap: a = %d, b = %d\n", a,b);

    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}