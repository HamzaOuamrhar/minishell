#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>  // For perror

int main(int argc, char *argv[], char *env[]) {
  if (argc < 2) {
      fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
      return 1;
  }
  
  // Open the file in read-only mode to check if it exists
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
      perror("open");
      return 1;
  }
    dup2(fd,  STDIN_FILENO);
  // close(fd);  // Close the file descriptor since we don't actually need it
  char *const new_argv[] = {"cat", NULL};

  // Pass current environment to "cat"
  if (execve("/bin/cat", new_argv, env) == -1) {
      perror("execve");
      return 1;
  }

  // This line won't be reached after successful execve
  return 0;
}
