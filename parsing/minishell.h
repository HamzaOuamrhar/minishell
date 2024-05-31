#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct t_env
{
    char *key;
    char *value;
    struct t_env *next;
}   t_env;

typedef struct t_count
{
    int in;
    int out;
    int app;
    int words;
}   t_count;

typedef    struct t_token
{
    char            *value;
    char            *type;
    int             flag;
    int             wh;
    int             here;
    int             has_q;
    struct t_token   *next;
}    t_token;

typedef struct t_parse
{
    char    **cmd;
    char    **in;
    char    **out;
    char    **app;
    char    *in_dup;
    char    *out_dup;
    int     i;
    struct  t_parse *next;
}   t_parse;

typedef struct t_garbage
{
    void    *p;
    struct t_garbage *next;
}   t_garbage;

typedef struct t_decl
{
    int still;
    int first;
    int j;
    int i;
    char    *value;
}   t_decl;

typedef struct t_decl2
{
    int     in_quote;
	int     i;
	char    quote;
	char    *n_t_v;
	int     start;
	char    *value;
	int     j;
	int     z;
    int     h;
	int     still;
}   t_decl2;

typedef struct t_decl3
{
    int	i;
	int j;
	int k;
	int z;
	int	l;
	char 	*line;
	int		fd;
	int		f_time;
}   t_decl3;

void     tokenize(t_token **token, char *line, int *q);
char	**ft_split(char const *s, char c, int *still);
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
int     syntax(t_token *token);
void	tokens_reset(t_token **token);
void	set_env(t_env **env_vars, char **env);
void	expander(t_token *token);
char	*get_env(char *key, t_env *env_vars);
int	    ft_strcmp(char *s1, char *s2);
int	    in_str(char *str, char c);
void	quotes_removal(t_token *tokens);
int	    is_alph(char c);
int     parser(t_token *tokens, t_parse **parse);
void	add_back_parse(t_parse **parse, t_parse *new);
void	non_quotes_expander(t_token **token);
void	get_var_key(char *token_value, int *i);
void	add_middle(t_token **token, char **arr);
int	    word_count(char *str);
int	    white_word(char *str);
void	add_middle_n(t_token **token, char *value);
int	    no_rest(char *str, int i);
void	quotes_expander(t_token **token, char *token_value);
void	comp(t_decl decl, t_token **token, char *token_value, int *i);
void	out_quotes(t_decl2 *decl, char *t_v, t_token **token);
void	first_word_pos(char *value, int *i, int *j);
char	*ft_itoa(int n);
void	expand_line(char **line);
void	*ft_malloc(size_t size, int flag);

void	print(t_parse **parse);

#endif