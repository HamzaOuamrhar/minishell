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
	}
	return (0);
}

int	in_out_dup(t_parse *st)
{
	if(check_ins(st))
		return (1);
	return (0);
}
