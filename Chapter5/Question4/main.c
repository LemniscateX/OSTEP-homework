#define _GNU_SOURCE  // execvpe need it
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        char* const argv[] = {"ls", NULL};
        char* const env[] = {"HOME=/usr/home", "LOGNAME=home", NULL};

        // execl("/bin/ls", "ls", NULL);
        // execle("/bin/ls", "ls", NULL, env);
        // execlp("ls", "ls", NULL);

        // execv("/bin/ls", argv);
        // execve("/bin/ls", argv, env);
        // execvp("ls", argv);
        // execvpe("ls", argv, env);

    } else {
        // parent process
    }
}