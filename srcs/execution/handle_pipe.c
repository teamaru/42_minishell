/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:33:31 by jnakahod          #+#    #+#             */
/*   Updated: 2021/11/06 18:18:13 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

static t_result	preparation_fork(t_pipe_list *node, int pipe_fd[2])
{
	if (has_pipe(node) && pipe(pipe_fd) < 0)
		return (FAILURE);
	if (write_heredoc(node->heredoc) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static pid_t	do_pipe(t_pipe_list *first,
	t_pipe_list *node, int last_pipe_fd[2])
{
	int		new_pipe_fd[2];
	pid_t	child_pid;

	if (preparation_fork(node, new_pipe_fd) < 0)
		return (-1);
	child_pid = fork();
	if (child_pid < 0)
	{
		close_and_unlink(&node->heredoc, TRUE);
		return (child_pid);
	}
	if (child_pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		child_operate_pipe_fd(first, node, last_pipe_fd, new_pipe_fd);
		child_exec_cmd(node);
	}
	else
	{
		close_and_unlink(&node->heredoc, FALSE);
		parent_operate_pipe_fd(node, last_pipe_fd, new_pipe_fd);
	}
	return (child_pid);
}

pid_t	handle_pipelines(t_pipe_list *pipe_list)
{
	t_pipe_list	*tmp_node;
	int			last_pipe_fd[2];
	pid_t		last_child_pid;

	tmp_node = pipe_list;
	init_pipe_fd(last_pipe_fd);
	while (tmp_node)
	{
		last_child_pid = do_pipe(pipe_list, tmp_node, last_pipe_fd);
		tmp_node->pid = last_child_pid;
		tmp_node = tmp_node->next;
	}
	return (last_child_pid);
}
