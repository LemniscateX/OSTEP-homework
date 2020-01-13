#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process

        // int wc = wait(NULL);
        // printf("%d\n", wc);
        printf("hello from child process\n");
    } else {
        // parent process

        // int wc = wait(NULL);
        // printf("%d\n", wc);
        // printf("%d\n", rc);
        printf("hello from parent process\n");
    }
}