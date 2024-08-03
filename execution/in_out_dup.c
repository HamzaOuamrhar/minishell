/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:24:39 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/03 16:06:00 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_perms(t_parse *st, t_params *params)
{
	int		fd;
	t_files	*tmp;
	struct stat path;
	
	(void)params;
	tmp = st->files;
	while (tmp)
	{
		stat(tmp->file, &path);
		if (S_ISDIR(path.st_mode))
			return (print_error(NULL, ": is a directory\n", tmp->file), 1);
		if (access(tmp->file, R_OK) == -1 && access(tmp->file, F_OK) != -1)
			return (print_error(NULL, ": Permission denied\n", tmp->file), 1);
		if (tmp->type != 1)
		{
			tmp = tmp->next;
			continue ;
		}
		fd = open(tmp->file, O_RDONLY);
		if (fd == -1)
			return (print_error(NULL, ": No such file or directory\n",
					tmp->file), 1);
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
		execve(st->com_path, st->cmd, params->env2);
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
	while (file)
	{
		if (file->is_amb)
		{
			close(st->in_fd);
			g_status = 1;
			printf("shellantics: ambiguous redirect\n");
			return (1);
		}
		if (file->type == 2)
			st->out_fd = open(file->file, O_RDWR | O_CREAT, 0777);
		else if (file->type == 3)
			st->out_fd = open(file->file, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (st->out_fd == -1 || st->in_fd == -1)
			return (perror("open"), 1);
		if (file->next)
			close (st->out_fd);
		file = file->next;
	}
	return (0);
}

int	in_out_dup(t_parse *st, t_params *params)
{
	if (check_perms(st, params))
	{
		g_status = 1;
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
	return (0);
}
