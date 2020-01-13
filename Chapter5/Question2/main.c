#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    int fd = open("file.txt", O_RDWR | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
    if (fd == -1) {
        fprintf(stderr, "file open failed with errno %d\n", errno);
    } else {
        int rc = fork();
        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc == 0) {
            // child process
            const char* child_stmt = "This is from child\n";
            if (write(fd, child_stmt, strlen(child_stmt)) < 0)
                fprintf(stderr, "write failed\n");
        } else {
            // parent process
            const char* parent_stmt = "This is from parent\n";
            if (write(fd, parent_stmt, strlen(parent_stmt)) < 0)
                fprintf(stderr, "write failed\n");
        }
        close(fd);
    }
}