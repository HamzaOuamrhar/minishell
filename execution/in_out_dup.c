#include "../minishell.h"

int	check_perms(t_parse *st, t_params *params)
{
	int		fd;
	t_files	*tmp;

	tmp = st->files;
	while (tmp)
	{
		// printf("[[file==%s]], type==%d\n", tmp->file, tmp->type);
		if (access(tmp->file, R_OK) == -1 && access(tmp->file, F_OK) != -1)
		{
			if (!params->pid)
				exit (0);
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
			if (!params->pid)
				exit (0);
			printf("shellantics: %s: No such file or directory\n", tmp->file);
			return (1);
		}
		close (fd);
		tmp = tmp->next;
	}
	return (0);
}



int	excute_cmd_dup(t_parse *st, t_params *params, int fd)
{
	if (!params->pid)
	{
		if (check_builtins(st->cmd[0]))
		{
			close (fd);
			return (1);
		}
		if (fd)
		{
			dup2(fd, 0);
			close (fd);
		}
		if (st->out_fd)
		{
			dup2(st->out_fd, 1);
			close (st->out_fd);
		}
		if (!st->com_path)
		{
			printf("%s :command not found\n", st->cmd[0]);
			exit (127); 
		}
		execve(st->com_path, st->cmd, params->env2); //protection
	}
	return (0);
}

int	get_type(t_files *files, char *s)
{
	while (files)
	{
		if (!(ft_strcmp(files->file, s)))
			return (files->type);
		files = files->next;
	}
	return (0);
}

int	open_files(t_parse *st)
{
	t_files	*file;

	file = st->files;
	if (st->in_dup)
		st->in_fd = open(st->in_dup, O_RDONLY);
	if (st->in_fd == -1)
	{
		perror("open"); // handele this later
		return (1);
	}
	while (file)
	{
		if (file->is_amb)
		{
			close(st->in_fd);
			_g_signal = 1;
			printf("shellantics: ambiguous redirect\n"); //fucking problem witht the status value
			return (1);
		}
		if (file->type == 2)
			st->out_fd = open(file->file, O_RDWR | O_CREAT, 0777);
		else if (file->type == 3)
			st->out_fd = open(file->file, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (st->out_fd == -1)
		{
			perror("open"); // handele this later
			return (1); //this shoule be 0
		}
		if (file->next)
			close (st->out_fd);
		file = file->next;
	}
	return (0);
}

int	in_out_dup(t_parse *st, t_params *params)
{
	////imad"gots here");
	////imad"hello in_out  \n");
	if (check_perms(st, params))
	{
		_g_signal = 1;
		if (!params->pid)
			exit (0);
		return (1);
	}
	st->in_fd = 0;
	if (!params->pid)
	{
		if (open_files(st))
			exit (0);
	}
	if (!st->cmd[0] || !st->cmd)
		return (1);
	if (!params->pid)
		excute_cmd_dup(st, params, st->in_fd);
	return (1);
}

