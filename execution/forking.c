#include "../minishell.h"

int    forking_piping(t_params *params, int i)
{
	ssize_t		r;
	char		buffer[500];

	// printf("%")
	if (i != params->cmds - 1)
		pipe(params->fds);
	params->pid = fork();
	if (params->pid < 0) 
	{
		perror("fork)");
	}//handle failure
	if (params->pid == 0)
	{
		if (params->flag && i > 1 && params->flag_2)
		{
			r = 1;
			puts("here");
  			while (r)	
   				r = read(params->save_fd, buffer, sizeof(buffer));//handle the failure of read
		}
		if (i == 0 && params->cmds > 1)
		{
			if (first_cmd(params->fds))
			{
				close(params->fds[0]);
				close(params->fds[1]);
				return (1);
			}
		}
		else //middle or last command
		{
			if (i != 0)
			{
			if (params->flag  && i != params->cmds - 1)
			{
				if (dup2(params->fds[0], STDIN_FILENO) == -1)
				{
					perror("dup2");
					return (1);
				}
				close(params->fds[0]);
			}
			else if (params->save_fd != -1)
			{
				// puts("before");
				if (dup2(params->save_fd, STDIN_FILENO) == -1)
		  		{
			  		perror("dup2");//remember to close the params->fds in failure cases
		    		// return (1);
		  		}
				// puts("after");
		  		close(params->save_fd);
			}
          }
          if (i != params->cmds - 1 && i < params->cmds)
		  {
            close(params->fds[0]);
            if (dup2(params->fds[1], STDOUT_FILENO) == -1)
			{
                perror("dup2");
                return (1);
            }
            close(params->fds[1]);
          }
        }
		// close(params->fds[1]);
		// close(params->save_fd);
		close(params->fds[0]);
    }
	return (0);
}
