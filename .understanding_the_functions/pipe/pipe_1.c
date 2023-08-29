/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:16:18 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 15:52:02 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../../libft/libft.h"

/*
	this is my pipex project, but simplified. it is a good example of how to use pipes.

	i am going to skip the parts about validation of arguments and error handling, because they are not relevant to the pipe concept.

	it is recommended to look at the subject to understand what was expected of us.

	reminder: when using forks, it is usual that valgrind does not work properly.

	example:
	ccf pipe_1.c ../../libft/libft.a
	./a.out a.txt ls "grep p" b.txt
*/

void child_process(char **av, char **envp, int file1, int pipefd[2]);
void parent_process(char **av, char **envp, int file2, int pipefd[2]);
char **ft_get_path(char **envp);
void ft_execute(char *cmd, char **envp);

int main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		printf("Usage: ./a.out file1 cmd1 cmd2 file2\n");
		exit(EXIT_FAILURE);
	}

	// First, we open the files related to the commands
	int file1 = open(argv[1], O_RDONLY);
	int file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);

	// We will then create the pipe
	int pipefd[2];
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	// After creating the pipe, we will fork the process
	int pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		child_process(argv, envp, file1, pipefd);
	}
	else
	{
		waitpid(pid, NULL, 0);
		parent_process(argv, envp, file2, pipefd);
	}
}

void child_process(char **av, char **envp, int file1, int pipefd[2])
{
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(file1, STDIN_FILENO);
	close(pipefd[0]);
	ft_execute(av[2], envp);
}

void parent_process(char **av, char **envp, int file2, int pipefd[2])
{
	dup2(pipefd[0], STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	close(pipefd[1]);
	ft_execute(av[3], envp);
}

char	**ft_get_path(char **envp)
{
	int		i;
	char	**paths_possible;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			paths_possible = ft_split(envp[i] + 5, ':');
		i++;
	}
	return (paths_possible);
}

void	ft_execute(char *cmd, char **envp)
{
	int		i;
	char	*tmp;
	char	*cmd_path;
	char	**paths_possible;
	char	**cmd_args;

	paths_possible = ft_get_path(envp);
	cmd_args = ft_split(cmd, ' ');
	i = 0;
	while (paths_possible[i++])
	{
		tmp = ft_strjoin(paths_possible[i], "/");
		cmd_path = ft_strjoin(tmp, cmd_args[0]);
		free(tmp);
		if (!cmd_path || !tmp)
			break ;
		if (access(cmd_path, F_OK | X_OK) == 0)
			execve(cmd_path, cmd_args, envp);
		free(cmd_path);
	}
	perror("Error");
	exit(2);
}
