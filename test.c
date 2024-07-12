#include <unistd.h>

int clear_pipe(int pipe_fd) {
  char buffer[1024]; // Adjust buffer size as needed
  ssize_t bytes_read;

  do {
    bytes_read = read(pipe_fd, buffer, sizeof(buffer));
  } while (bytes_read > 0);

  // Check for errors (e.g., handle EAGAIN if non-blocking mode)
  if (bytes_read == -1 && errno != EAGAIN) {
    perror("read");
    return -1;
  }

  return 0; // Indicate successful clearing (or no data to read)
}
