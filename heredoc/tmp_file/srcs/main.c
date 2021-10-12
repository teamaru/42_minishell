/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:16:19 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/10 21:31:59by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <heredoc.h>
#include <unistd.h>
#define TMPFILE "/tmp/my_tmp_file"

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

void	child_exec_cat(int	file_fd)
{
	char *cmd[2] = {"cat", NULL};
	int	tmp_file_fd;

	close(file_fd);
	tmp_file_fd = open(TMPFILE, O_RDWR, 0666);
	if (tmp_file_fd < 0)
		exit(1);
	close(0);
	dup2(tmp_file_fd ,0);
	close(tmp_file_fd);
	unlink(TMPFILE);

	if (execve("/bin/cat", cmd, NULL) < 0)
	{
		perror("execve");
		exit(1);
	}
}

int	heredoc_to_fd(char *heredoc)
{
	int	tmp_file_fd;

	tmp_file_fd = open(TMPFILE, O_RDWR | O_CREAT | O_EXCL, 0666);
	if (tmp_file_fd < 0)
		return (-1);
	if (write(tmp_file_fd, heredoc, ft_strlen(heredoc)) < 0)
	{
		close(tmp_file_fd);
		unlink(TMPFILE);
		return (-1);
	}
	return (tmp_file_fd);
}

pid_t	do_cmd(int tmp_file_fd)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror("fork");
		close(tmp_file_fd);
		unlink(TMPFILE);
		return (child_pid);
	}
	else if (!child_pid)
		child_exec_cat(tmp_file_fd);
	else
		close(tmp_file_fd);
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
	pid_t	child_pid;
	int		tmp_file_fd;

	if (ac != 2)
		return (-1);
	heredoc = NULL;
	input = NULL;
	while (TRUE)
	{
		input = readline("> ");
		if (!input || !ft_strncmp(input, av[1], ft_strlen(av[1]) + 1))
		{
			free_set((void **)&input, NULL);
			tmp_file_fd = heredoc_to_fd(heredoc);
			if (tmp_file_fd < 0)
				break ;
			child_pid = do_cmd(tmp_file_fd);
			if (child_pid < 0)
				break;
			wait_process(child_pid);
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
