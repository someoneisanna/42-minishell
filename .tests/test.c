#include <stdio.h>
#include "libft/libft.h"

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
	t_token	*token;
}	t_minishell;

int		ft_add_token(t_token **token_lst, char *input, t_type type);
t_token *ft_new_token(char *input, t_type type);
void	ft_add_token_back(t_token **token, t_token *new_token);
void	ft_print_token_lst(t_token *token_lst);
void	ft_clear_token_lst(t_token **token_lst);
int		ft_add_command_token(t_token **token_lst, char *input, t_type type);
int		ft_size_until_match(char *input, char *match);

int main(void)
{
	t_minishell *ms = ft_calloc(1, sizeof(t_minishell));
	char *input = "\' anna \'";

	int i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (input[i] == '|')
			i += ft_add_token(&ms->token, "|", T_PIPE);
		else if (input[i] == '<' && input[i + 1] != '<')
			i += ft_add_token(&ms->token, "<", T_REDIR_IN);
		else if (input[i] == '>' && input[i + 1] != '>')
			i += ft_add_token(&ms->token, ">", T_REDIR_OUT);
		else if (input[i] == '<' && input[i + 1] == '<')
			i += ft_add_token(&ms->token, "<<", T_REDIR2_IN);
		else if (input[i] == '>' && input[i + 1] == '>')
			i += ft_add_token(&ms->token, ">>", T_REDIR2_OUT);
		else if (input[i] == '\'')
		{
			int j = ft_add_command_token(&ms->token, input + i, T_QUOTE);
			printf("j: %d\n", j);
			i += j;
		}
		else if (input[i] == '\"')
			i += printf("s: %s\n", input + i);
			//ft_add_command_token(&ms->token, input + i, T_DQUOTE);
		else
			i += ft_add_command_token(&ms->token, input + i, T_OTHER);
	}
	printf("PRINT_TOKENS\n");
	ft_print_token_lst(ms->token);
	ft_clear_token_lst(&ms->token);
	free(ms);
}

int	ft_add_token(t_token **token_lst, char *input, t_type type)
{
	t_token	*new_token;

	new_token = ft_new_token(input, type);
	if (!new_token || !input)
		return (0);
	ft_add_token_back(token_lst, new_token);
	return (ft_strlen(input));
}

t_token *ft_new_token(char *input, t_type type)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(input);
	if (!new_token->content)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = type;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	ft_add_token_back(t_token **token_lst, t_token *new_token)
{
	t_token	*current;

	if (!*token_lst)
	{
		*token_lst = new_token;
		return ;
	}
	current = *token_lst;
	while (current && current->next)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

void	ft_print_token_lst(t_token *token_lst)
{
	t_token	*current;

	if (!token_lst)
		return ;
	current = token_lst;
	while (current)
	{
		printf("content: %s | ", current->content);
		printf("type: %d\n", current->type);
		current = current->next;
	}
}

void	ft_clear_token_lst(t_token **token_lst)
{
	t_token	*current;
	t_token	*next;

	if (!*token_lst)
		return ;
	current = *token_lst;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*token_lst = NULL;
}

int	ft_add_command_token(t_token **token_lst, char *input, t_type type)
{
	char	*match;
	char	*command;
	int		found_match;

	if (type == T_QUOTE)
		match = "\'";
	else if (type == T_DQUOTE)
		match = "\"";
	else
		match = "<>\'\"| ";
	found_match = ft_size_until_match(input, match);
	command = ft_substr(input, 0, found_match);
	ft_add_token(token_lst, command, type);
	return (found_match);
}

int	ft_size_until_match(char *input, char *match)
{
	int	i;

	i = 0;
	while (input[i] && ft_strchr(match, input[i]) == NULL)
	{
		i++;
	}
	return (i);
}

/*
void pname(char c)
{
	static int i;

	if (c == 'q')
		printf("quote\n");
	else if (c == 'd')
		printf("dquote\n");
	else if (c == '|')
		printf("pipe\n");
	else if (c == '<' || c == '>')
		printf("redirection\n");
	else
	{
		i++;
		printf("char %d\n", i);
	}
}

int main(int ac, char **av)
{
	if (ac < 2)
		return (printf("Usage: ./test [arg]\n"));
	char *input = av[1];

	int i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		while (input[i] && input[i] != ' ')
		{
			if (input[i] == '\'')
				pname('q');
			else if (input[i] == '\"')
				pname('d');
			else if (input[i] == '|')
				pname('|');
			else if (input[i] == '<' || input[i] == '>')
				pname('<');
			else
				pname('c');
			i++;
		}
	}
}
*/

/*
int	main(int ac, char **av)
{
	int	i;
	int j;

	if (ac < 2)
		return (printf("Usage: ./test [args]\n"));
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == ' ')
				j++;
			while (av[i][j] && av[i][j] != ' ')
			{
				if (av[i][j] == '\'')
					printf("quote\n");
				else if (av[i][j] == '\"')
					printf("dquote\n");
				else if (av[i][j] == '|')
					printf("pipe\n");
				else if (av[i][j] == '<' || av[i][j] == '>')
					printf("redirection\n");
				else
					printf("char\n");
				j++;
			}
		}
		i++;
	}
}
*/
