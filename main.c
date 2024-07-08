#include "minishell.h"
int main()
{
    int i = 0;
    int counter = 2;

    int fds[2];  // Array to hold the pipe file descriptors
    int fd_in = 0;  // Input file descriptor for the current stage

    for (int i = 0; i < counter; i++) {
        if (i != counter - 1) {
            // Create a pipe for all but the last command
            pipe(fds);
        }

        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            if (i > 0) {
                // Redirect input from the previous stage
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }

            if (i != counter - 1) {
                // Redirect output to the next stage
                dup2(fds[1], STDOUT_FILENO);
                close(fds[1]);
                close(fds[0]);
            }

            // Execute the command here, e.g., execlp(...)
            // execlp(...);
            // perror("c");
        }
        else
        {
            // Parent process
            wait(NULL);  // Wait for the child process to complete

            if (i > 0) {
                // Close the previous input file descriptor
                close(fd_in);
            }

            if (i != counter - 1) 
            {
                // Close the write end of the current pipe
                close(fds[1]);
                // Keep the read end for the next iteration
                fd_in = fds[0];
            }
        }
    }
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void execute_cmd(t_parse *st, t_params *params) {
    int pid;
    int fds[2];
    static int i = 0;

    if (i != params->cmds - 1) 
      pipe(fds);

    pid = fork();

    
    if (pid == 0) { // Child process
        if (i == 0 && params->cmds > 1) {
            close(fds[0]); // Close the read end
            if (dup2(fds[1], STDOUT_FILENO) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            close(fds[1]); // Close the write end after duplicating
        } else if (i + 1 == params->cmds) {
            // Last command
            close(fds[0]);
            close(fds[1]);
        } else {
            close(fds[0]); // Close the read end
            if (dup2(fds[1], STDOUT_FILENO) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            close(fds[1]); // Close the write end after duplicating
        }
        
        execve(st->com_path, st->cmd, params->env2);
        perror("execve");
        exit(EXIT_FAILURE);
    }

    // Parent process
    if (i != 0) {
        close(fds[1]); // Close the write end
        if (dup2(fds[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(fds[0]); // Close the read end after duplicating
    }

    wait(NULL); // Wait for the child process to complete
    i++;
}

int main() {
    // Example setup, replace with actual initialization
    t_parse st;
    t_params params;

    // Populate st and params with appropriate values

    for (int j = 0; j < params.cmds; j++) {
        execute_cmd(&st, &params);
    }

    return 0;
}
