#ifndef MINISHELL_H
#define MINISHELL_H

#include <libc.h>


#include <readline/readline.h>
#include <readline/history.h>



// types:
// input : <
// output : >
// heredoc : <<
// append : >>
// pipe : |
// word

// syntax error for redirections
// for the heredoc and input => anything execpt {<, >, <<, >>, |} for quotes it accepts anything
// the input and output and append expand the variables ($var)

// expanding exceptions
// echo $12DFGHJ_ => 2DFGHJ_

typedef struct t_env
{
    char *key;
    char *value;
    struct t_env *next;
}   t_env;

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
void	exit_syntax_error(char *error_msg);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	    is_in_word(char c);
int	    is_white(char c);
int	    is_alph_num(char c);
char	*ft_strjoin(char *s1, char *s2);
void	syntax(t_token *token);
void	tokens_reset(t_token **token);
void	set_env(t_env **env_vars, char **env);
void	expander(t_token *token, t_env *env_vars);
char	*get_env(char *key, t_env *env_vars);
int	    ft_strcmp(char *s1, char *s2);


#endif