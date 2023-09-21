#include "minishell.h"

void	ft_execvp(char **args)
{
	execvp(args[0], args);
}

void	ft_pipes_executer(char *cmd, int index, int last)
{
	pid_t	pid;
	int		pipefd[2];

	// SPLIT CMD
	char **args = ft_split(cmd, ' ');

	// CREATE PIPE
	if (pipe(pipefd) == -1)
		exit (1);

	// CREATE FORK
	pid = fork();
	if (pid < 0)
		exit (1);

	// CHILD PROCESS
	else if (pid == 0)
	{
		if (index == 0)
			dup2(pipefd[1], STDOUT_FILENO);
		else if (index == last)
			close(pipefd[0]);
		else
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
		}
		ft_execvp(args);
	}

	// PARENT PROCESS
	else
	{
		if (index == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
		}
		else if (index == last)
			;
		else
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
		}
		waitpid(pid, NULL, 0);
	}
}

char	**ft_command_creator(char *input)
{
	int i = 0;
	int n_pipes = 0;
	while (input[i])
	{
		if (input[i] == '|')
			n_pipes++;
		i++;
	}
	char **commands = (char **)malloc(sizeof(char *) * (n_pipes + 1));
	if (!commands)
		exit (1);
	i = 0;
	char *tmp = input;
	while (i < n_pipes + 1)
	{
		if (ft_strchr(tmp, '|') != NULL)
		{
			commands[i] = ft_substr(tmp, 0, strchr(tmp, '|') - tmp);
			if (!commands[i])
				exit (1);
			tmp = strchr(tmp, '|') + 2;
		}
		else if (strchr(tmp, '|') == NULL)
		{
			commands[i] = strdup(tmp);
			if (!commands[i])
				exit (1);
		}
		i++;
	}
	int last_cmd_len = strlen(commands[n_pipes]);
	if (last_cmd_len > 0 && commands[n_pipes][last_cmd_len - 1] == '\n')
		commands[n_pipes][last_cmd_len - 1] = '\0';
	commands[i] = NULL;
	return (commands);
}

void	ft_free(char *input, char **cmds)
{
	free(input);
	int i = 0;
	while (cmds[i])
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

int main(void)
{
	char *input;
	char **cmds;

	input = NULL;
	cmds = NULL;
	while (1)
	{
		input = readline("ms> ");
		printf("input: %s\n", input);
		if (!input)
			exit (1);
		add_history(input);
		cmds = ft_command_creator(input);
		int last = 0;
		while (cmds[last])
			last++;
		for (int i = 0; cmds[i]; i++)
		{
			ft_pipes_executer(cmds[i], i, last);
		}
	}
	ft_free(input, cmds);
	rl_clear_history();
}
