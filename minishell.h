/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:30:28 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/05 10:31:38 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

// ---------------------------------- INCLUDES ---------------------------------

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>

// ---------------------------------- DEFINES ----------------------------------

# define TRUE			1
# define FALSE			0

# define YES			1
# define NO				0

# define ERROR_FOUND	1
# define EXIT_FAILURE	1
# define EXIT_SUCCESS	0

# define PIPE_W			1
# define PIPE_R			0

# define E_QUOTES		"Syntax Error: Unclosed quotes"
# define E_SYNTAX		"Syntax error near unexpected token"
// ---------------------------------- STRUCTS ----------------------------------

typedef enum e_type
{
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR2_IN,
	T_REDIR2_OUT,
	T_QUOTE,
	T_DQUOTE,
	T_OTHER,
}	t_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;
typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_minishell
{
	char	*input;

	t_env	*env;
	t_token	*token;
}	t_minishell;

// --------------------------------- PROTOTYPES ---------------------------------

// ROOT _________________________________________________________________________

// main.c
void	ft_main_loop(t_minishell *ms);
void	ft_free_all(t_minishell *ms, int exit_flag);

// parser.c
int		ft_parser(t_minishell *ms, char *input);
int		ft_quote_checker(char *input);

// PARSING ______________________________________________________________________

// tokenizer.c
void	ft_tokenizer(t_minishell *ms, char *input);
int		ft_add_token(t_token **token_lst, char *input, t_type type);
int		ft_add_command_token(t_token **token_lst, char *input, t_type type);

// tokenizer_utils.c
t_token *ft_new_token(char *input, t_type type);
void	ft_add_token_back(t_token **token, t_token *new_token);
void	ft_free_token_lst(t_token **token_lst);

// syntax_checker.c
int		ft_syntax_checker(t_token *token);

// expander.c
void	ft_expander(t_minishell *ms, t_token *token);
void	ft_expand_command(t_minishell *ms, t_token *token);
char	*ft_get_key(char *cmd);
char	*ft_get_env_value(t_env **env_lst, char *key);
char	*ft_replace_content(char *cmd, char *key, char *value);

// ENVIRONMENT __________________________________________________________________

// environment_lst.c
void	ft_init_env_lst(t_env **env, char **envp);
t_env	*ft_new_env(char *key, char *value);
void	ft_add_env_back(t_env **env_lst, t_env *new_env);
void	ft_free_env_lst(t_env **env_lst);

// UTILS ________________________________________________________________________

// utils_0.c
int		ft_is_space(char c);
int		ft_everything_is_space(char *str);
int		ft_len_until_match(char *input, char *match);
int		ft_is_cmd_or_file(t_type type);
int		ft_perror(char *error);

# endif
