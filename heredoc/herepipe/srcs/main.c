/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:16:19 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/07 23:04:41 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <heredoc.h>

void	free_set(void **dst, void *src)
{
	free(*dst);
	*dst = src;
}

char	*update_heredoc(char **old, char *input)
{
	char *joined_input;
	char *new_heredoc;

	joined_input = NULL;
	new_heredoc = NULL;
	joined_input = ft_strjoin(*old, input);
	free_set((void **)old, NULL);
	if (!joined_input)
		return (NULL);
	new_heredoc = ft_strjoin(joined_input, "\n");
	free_set((void **)&joined_input, NULL);
	if (!new_heredoc)
		return (NULL);
	return (new_heredoc);
}

void	init_pipefd(int pipefd[2])
{
	pipefd[0] = -1;
	pipefd[1] = -1;
}

t_result	create_herepipe(int herepipe[2])
{
	if (pipe(herepipe) < 0)
	{
		perror("pipe");
		return (FAILURE);
	}
	return (SUCCESS);
}

void	child_read_herepipe(int herepipe[2])
{
	char *cmd[2] = {"cat", NULL};
	close(herepipe[1]);

	close(0);
	dup2(herepipe[0], 0);
	close(herepipe[0]);

	if (execve("/bin/cat", cmd, NULL) < 0)
	{
		perror("execve");
		exit(1);
	}
}

pid_t	handle_heredocument(int herepipe[2], char *heredoc)
{
	pid_t	child_pid;
	int		status;

	write(herepipe[1], heredoc, ft_strlen(heredoc));
	status = -1;
	child_pid = fork();
	if (child_pid < 0)
	{
		perror("fork");
		return (child_pid);
	}
	else if (child_pid == 0)
		child_read_herepipe(herepipe);
	else
		close(herepipe[0]);
		close(herepipe[1]);
	return (child_pid);
}

void	wait_process(pid_t child_pid)
{
	int	status;

	if (waitpid(child_pid, &status, 0) < 0)
		perror("waitpid");
}

int	main(int ac, char **av)
{
	char	*input;
	char	*heredoc;
	int		herepipe[2];
	pid_t	child_pid;

	if (ac != 2)
		return (-1);
	heredoc = NULL;
	while (1)
	{
		input = readline("> ");
		if (!input || !ft_strncmp(input, av[1], ft_strlen(av[1]) + 1))
		{
			free_set((void **)&input, NULL);
			init_pipefd(herepipe);
			if (create_herepipe(herepipe) == SUCCESS)
			{
				child_pid = handle_heredocument(herepipe, heredoc);
				if (child_pid < 0)
					break;
				wait_process(child_pid);
			}
			free_set((void **)&heredoc, NULL);
		}
		else
		{
			heredoc = update_heredoc(&heredoc, input);
			add_history(input);
			free_set((void **)&input, NULL);
		}
	}
	free_set((void **)&heredoc, NULL);
	return (0);
}
