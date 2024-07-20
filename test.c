#include <stdio.h>
int main()
{
    printf("hello world how the hell are you/n");
    return (0);
}

void	forking_checker(t_parse *st, t_params *params, int i)
{
	slash_path(st, params);
	if (((params->cmds != 1 && check_builtins(st->cmd[0]))
		|| ((params->cmds == 1 && !check_builtins(st->cmd[0])) && (st->com_path))) && ft_strlen(st->cmd[0]))
	{
		puts("forking here \n\n");
		forking_piping(params, i);
	}
}