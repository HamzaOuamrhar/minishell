#include "../minishell.h"

int	check_ins(t_parse *st)
{
	int		fd;
	t_files	*tmp;

	tmp = st->files;
	while (tmp)
	{
		if (tmp->type != 1)
		{
			tmp = tmp->next;
			continue ;
		}
		if (access(tmp->file, R_OK) == -1 && access(tmp->file, F_OK) != -1)
		{
			printf("shellantics: %s: Permission denied\n", tmp->file);
			return (1);
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
		||!(ft_strcmp(s, "pwd")))
		return (1);
	return (0);
}

int	excute_cmd_dup(t_parse *st, t_params *params, int fd)
{
	int	pid;

	// fd = open(st->in_dup, O_RDONLY); //already protected
	pid = fork();
	if (pid == 0)
	{
		if (check_builtins(st->cmd[0]))
		{
			close (fd);
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close (fd);
		st->com_path = get_acc_path(params->paths_array, st->cmd[0]);
		if (!st->com_path)
		{
			printf("%s :command not found\n", st->cmd[0]);
			exit (127);
		}
		execve(st->com_path, st->cmd, params->env2); //protection
		exit(1);
	}
	int status = 0;
	waitpid(pid, &status , 0);
	if (WIFEXITED(status))
		params->status = WEXITSTATUS(status);
	return (0);
}

int	in_out_dup(t_parse *st, t_params *params)
{
	if (check_ins(st))
	{
		params->status = 1;
		return (1);
	}
	if (!st->cmd[0] || !st->cmd)
		return (1);
	printf("%d\n", st->in_fd);
	if (!st->in_fd)
		st->in_fd = open(st->in_dup, O_RDONLY);
	if (excute_cmd_dup(st, params, st->in_fd))
		return (0);
	return (1);
}
