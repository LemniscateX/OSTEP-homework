#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = (int *)malloc(100 * sizeof(int));
    free(data);
    printf("%d\n", data[50]);
    return 0;
}