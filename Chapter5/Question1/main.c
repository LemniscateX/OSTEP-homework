#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int x = 100;
    printf("Initial x of Parent: %d\n", x);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        printf("Initial x of Child:  %d\n", x);
        x = 0;
        printf("Later x of Child:    %d\n", x);
    } else {
        // parent process
        x = 1000;
        printf("Later x of Parent:   %d\n", x);
    }
}