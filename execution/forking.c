#include "../minishell.h"

int first_cmd(int fds[2])
{
	close(fds[0]);
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		return (1);
	close(fds[1]);
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
	if (params->flag && params->i > 1 && params->flag_2)
	{
		close (params->save_fd);
		params->save_fd = params->fds[0];
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
	else
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
	close(params->fds[0]);
}

void	forking_checker(t_parse *st, t_params *params)
{
	slash_path(st, params);
	forking_piping(params);
}

void	initialiaze_vars(t_params *params, t_token **token, int f)
{
	if (f)
	{
		params->flag = 0;
		*token = NULL;
	}
	params->pid = 1;
	params->flag_2 = 0;
	params->save_fd = -1;
	params->i = 0;
}
