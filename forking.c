#include "../minisehll.h"

void    forking_piping(t_parse *st, t_params *params)
{
if (i != params->cmds - 1)
		pipe(fds);
	pid = fork();
	if (pid < 0) 
	{
		perror("fork)");
	}//handle failure
	if (pid == 0)
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
			if (first_cmd(fds))
			{
				close(fds[0]);
				close(fds[1]);
				return (1);
			}
		}
		else //middle or last command
		{
			if (i != 0)
			{
			if (params->flag  && i != params->cmds - 1)
			{
				if (dup2(fds[0], STDIN_FILENO) == -1)
				{
					perror("dup2");
					return (1);
				}
				close(fds[0]);
			}
			else if (params->save_fd != -1)
			{
				// puts("before");
				if (dup2(params->save_fd, STDIN_FILENO) == -1)
		  		{
			  		perror("dup2");//remember to close the fds in failure cases
		    		return (1);
		  		}
				// puts("after");
		  		close(params->save_fd);
			}
          }
          if (i != params->cmds - 1 && i < params->cmds)
		  {
            close(fds[0]);
            if (dup2(fds[1], STDOUT_FILENO) == -1)
			{
                perror("dup2");
                return (1);
            }
            close(fds[1]);
          }
        }
		// close(fds[1]);
		// close(params->save_fd);
		close(fds[0]);
    }
}
