#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        close(STDOUT_FILENO);
        int fd = open("file.txt", O_RDWR | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
        printf("hello from child process\n");
    } else {
        // parent process
        printf("hello from parent process\n");
    }
}