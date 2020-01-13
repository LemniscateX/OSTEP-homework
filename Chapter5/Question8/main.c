#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int fd[2];  // fd[0] is for reading, fd[1] is for writing
    if (pipe(fd) < 0) {
        fprintf(stderr, "pipe failed\n");
        exit(1);
    }

    int rc_1 = fork();
    if (rc_1 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc_1 == 0) {
        // child process 1

        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        printf("standard output of child 1\n");
        close(fd[1]);

    } else {
        int rc_2 = fork();
        if (rc_2 < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc_2 == 0) {
            // child process 2

            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            char buffer[256];
            while (fgets(buffer, sizeof(buffer), stdin)) {
                printf("standard input of child 2: %s", buffer);
            }

        } else {
            // parent process
            wait(NULL);
        }
    }
}