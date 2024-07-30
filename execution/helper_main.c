#include "../minishell.h"

void    excute_cmds(t_parse *st, t_params *params)
{
    if (params->cmds == 1 && check_builtins(st->cmd[0]))
        // excute_builtins(st, params);
        ;
}
// void    excute_builitns(t_parse *parse, t_params *params)
// {
    
// }`