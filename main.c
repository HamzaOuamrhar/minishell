#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Duplicate the file descriptor
    // int fd_dup = dup(fd);
    // if (fd_dup == -1) {
    //     perror("dup");
    //     close(fd);
    //     return 1;
    // }

    // Use the duplicated file descriptor
    write(fd, "Hello, World!\n", 14);

    // Redirect standard output to the file
    dup2(fd, STDOUT_FILENO);
    printf("This will be written to the file\n");

    // Close the file descriptors
    close(fd);
    // close(fd_dup);

    return 0;
}
