/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:52:27 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/07/12 08:44:20 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	excute_cmd(t_parse *st, t_params *params, int i)
{
	int			pid;
	int			fds[2];

	if (i != params->cmds - 1)
		pipe(fds);
	pid = fork();
	// if (pid < 0) //handle failure
	if (pid == 0)
	{
	if (params->flag && i != 0)
		{
			char buffer[1024];
  			ssize_t bytes_read;
  			do {
   			 bytes_read = read(params->save_fd, buffer, sizeof(buffer));
  			} while (bytes_read > 0);
		}
		if (i == 0 && params->cmds > 1)
		{
			if (first_cmd(fds))
				return (1);
		}
		else
		{ // Middle or last command
			
          if (i != 0)
		  {
              if (dup2(params->save_fd, STDIN_FILENO) == -1)
			  {
                perror("dup2");
                return (1);
              }
            close(params->save_fd);
          }
          if (i != params->cmds - 1 && i < params->cmds)
		  {
            close(fds[0]); // Close read end
            if (dup2(fds[1], STDOUT_FILENO) == -1)
			{
                perror("dup2");
                return (1);
            }
            close(fds[1]);
          }
        }
		execve(st->com_path, st->cmd, params->env2);
	}
	else
    {
    	wait(0);
		params->flag = 0;
		if (i != 0)
			close(params->save_fd);
        if (i != params->cmds - 1)
        {
           	close(fds[1]);
			params->save_fd = fds[0];
        }
    }
	return (0);
}

void change_directory(t_parse *st, t_params *params)
{
	char	*home;

	if (count_args(st->cmd) == 1)
	{
		home = get_key("HOME", params->env);
		if (!home)
		{
			printf("Shellantics: cd: HOME not set\n");
			return ;
		}
		change_dir(st, params, home);
		return ;
	}
	change_dir(st, params, st->cmd[1]);
}

void	excute_file(t_parse *st, t_params *params)
{
	int		pid;
	char	*tmp;

	tmp = ft_substr(st->cmd[0] ,2 , ft_strlen(st->cmd[0]));
	if (access(tmp, X_OK) == -1)
	{
		printf("%s: Permission denied\n", st->cmd[0]);
		free (tmp);
		params->status = 126;
		return ;
	}
	pid = fork();
	free (tmp);
	if (pid == 0)
		if (execve(st->cmd[0], st->cmd, params->env2) == -1)
		{
			params->status = 127;
			printf("Shellantics: %s: No such file or directory\n", st->cmd[0]);
		}
	wait (0);
}

void	terminate_shell(t_parse *st, t_params *params)
{
	int	args_n;

	args_n = count_args(st->cmd);
	if (args_n == 1 || args_n == 2)
		ft_exit(st, args_n, params);
	if (!(numbered_arg(st->cmd[1])) && (count_args(st->cmd)) > 2)
	{
		printf("exit\nShellantics: exit: too many arguments\n");
		return ;//its one 
	}
	if ((numbered_arg(st->cmd[1])))
	{
		printf("exit\nShellantics: exit: %s: numeric argument required\n", st->cmd[1]);
		// freeing(st, params);
		exit (255);
	}
}
