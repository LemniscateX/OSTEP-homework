#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = NULL;
    printf("%d\n", *p);  // This is exactly what causes a core dump
    free(p);
    return 0;
}