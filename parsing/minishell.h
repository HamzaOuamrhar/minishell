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
// $ : env
// word


typedef    struct t_token
{
    char            *value;
    char            *type;
    struct t_token   *next;
}    t_token;

void	tokenize(t_token **token, char *line);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
void	add_back(t_token **token, t_token *new);
size_t	ft_strlen(const char *s);
void	exit_syntax_error();
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	    is_in_word(char c);
int	    is_white(char c);
int	    is_alph_num(char c);
char	*ft_strjoin(char *s1, char *s2);

#endif