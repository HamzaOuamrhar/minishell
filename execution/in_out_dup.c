#include "../minishell.h"

int	check_perms(t_parse *st)
{
	int		fd;
	t_files	*tmp;

	tmp = st->files;
	while (tmp)
	{
		if (access(tmp->file, R_OK) == -1 && access(tmp->file, F_OK) != -1)
		{
			printf("shellantics: %s: Permission denied\n", tmp->file);
			return (1);
		}
		if (tmp->type != 1)
		{
			tmp = tmp->next;
			continue ;
		}
		fd = open(tmp->file, O_RDONLY);
		if (fd == -1)
		{
			printf("shellantics: %s: No such file or directory\n", tmp->file);
			return (1);
		}
		close (fd);
		tmp = tmp->next;
	}
	return (0);
}

int	check_builtins(char *s)
{
	if (!(ft_strcmp(s, "cd")) || !(ft_strcmp(s, "export"))
		|| !(ft_strcmp(s, "unset"))
		|| !(ft_strcmp(s, "env")) || !(ft_strcmp(s, "exit"))
		||!(ft_strcmp(s, "pwd"))
		||!(ft_strcmp(s, ".")))
		return (1);
	return (0);
}

int	excute_cmd_dup(t_parse *st, t_params *params, int fd)
{
	int	status;

	status = 0;
	if (!params->pid)
	{
		if (check_builtins(st->cmd[0]))
		{
			close (fd);
			return (1);
		}
		if (fd)
		{
			lseek(fd, 0, SEEK_SET); //handele this
			dup2(fd, 0);
			close (fd);
		}
		if (st->out_fd)
		{
			dup2(st->out_fd, 1);
			// if (params->cmds > 1)
			close (st->out_fd);
		}
		slash_path(st, params);
		if (!st->com_path)
		{
			printf("%s :command not found\n", st->cmd[0]);
			exit (127); 
		}
		execve(st->com_path, st->cmd, params->env2); //protection
	}
	waitpid(params->pid, &status , 0);
	if (WIFEXITED(status))
		params->status = WEXITSTATUS(status);
	return (0);
}

int	in_out_dup(t_parse *st, t_params *params)
{
	if (check_perms(st))
	{
		params->status = 1;
		return (1);
	}
	if (!st->in_fd)
		st->in_fd = open(st->in_dup, O_RDONLY);
	st->out_fd = 0;
	if (st->out_dup)
	{
		st->out_fd = open(st->out_dup, O_RDWR | O_CREAT, 0777);
		if (st->out_fd == -1)
		{
			perror("open"); // handele this later
			return 1;
		}
	}
	if (!st->cmd[0] || !st->cmd)
		return (1);
	excute_cmd_dup(st, params, st->in_fd);
	return (1);
}
