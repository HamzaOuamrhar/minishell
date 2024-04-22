#ifndef MINISHELL_H
#define MINISHELL_H

#include <libc.h>


#include <readline/readline.h>
#include <readline/history.h>


// types:
// "
// '
// input : <
// output : >
// heredoc : <<
// append : >>
// pipe : |
// $
// word


typedef    struct t_parse
{
    char            **arg;
    char            *type;
    struct t_parse   *next;
}    t_parse;

void	parsing(t_parse **parse, char *line);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
void	add_back(t_parse **parse, t_parse *new);

#endif