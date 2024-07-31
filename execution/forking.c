#include "../minishell.h"

int first_cmd(int fds[2])
{
    close(fds[0]);
	if (dup2(fds[1], STDOUT_FILENO) == -1)
    {
        ////imad"error in dup");
        return (1);
    }
	close(fds[1]);
	// close(fds[0]);
    return (0);
}

int last_cmd(int fds[2])
{
    close(fds[1]);
	if (dup2(fds[0], STDIN_FILENO) == -1)
    {
        return (1);
    }
	close(fds[0]);
    return (0);
}


void	forking_piping(t_params *params)
{
	ssize_t		r;
	char		buffer[500];

	if (params->flag && params->i > 1 && params->flag_2)
	{
		r = 1;
		while (r)	
			r = read(params->save_fd, buffer, sizeof(buffer));//handle the failure of read
	}
	if (params->i == 0 && params->cmds > 1)
	{
		if (first_cmd(params->fds))
		{
			close(params->fds[0]);
			close(params->fds[1]);
			return ;
		}
	}
	else //middle or last command
	{
		if (params->i != 0)
		{
			if (params->flag  && params->i != params->cmds - 1)
			{
				if (dup2(params->fds[0], STDIN_FILENO) == -1)
				{
						perror("dup2");
						return ;
					}
					close(params->fds[0]);
				}
				else if (params->save_fd != -1)
				{
					if (dup2(params->save_fd, STDIN_FILENO) == -1)
					{ 
						perror("dup2");//remember to close the params->fds in failure cases
						// return ;
					}
					close(params->save_fd);
				}
			}
			if (params->i != params->cmds - 1 && params->i < params->cmds)
			{
				close(params->fds[0]);
				if (dup2(params->fds[1], STDOUT_FILENO) == -1)
				{
					perror("dup2");
					return ;
				}
				close(params->fds[1]);
			}
		}
	// close(params->fds[1]);
	// close(params->save_fd); //need to do something here
	close(params->fds[0]);
}

void	forking_checker(t_parse *st, t_params *params)
{
	// (void)st;
	slash_path(st, params);
	// if (params->cmds == 1) //check this later
	// {
	forking_piping(params);
		// params->pid = fork();
	//do not check for the command path
	// else
}

void	initialiaze_vars(t_params *params, t_token **token, int f)
{
	if (f)
	{
		params->flag = 0;
		*token = NULL;
		_g_signal = 0;
	}
	_g_signal = 0;
	params->pid = 1;
	params->flag_2 = 0;
	params->save_fd = -1;
	params->i = 0;
}
