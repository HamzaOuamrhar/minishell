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

void	excute_cmd_dup(t_parse *st, t_params *params)
{
	int	pid;
	int	fd;

	fd = open(st->in_dup, O_RDONLY);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		execve(st->com_path, st->cmd, params->env2); //protection
		close (fd);
	}
	wait(0);
}

int	in_out_dup(t_parse *st, t_params *params)
{
	if (check_ins(st))
		return (1);
	excute_cmd_dup(st, params);
	return (0);
}
