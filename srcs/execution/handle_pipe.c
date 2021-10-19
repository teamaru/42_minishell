/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:33:31 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/19 15:21:32 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static pid_t	do_pipe(t_pipe_list *first,
	t_pipe_list *node, int last_pipe_fd[2])
{
	int		new_pipe_fd[2];
	pid_t	child_pid;

	if (has_pipe(node) && pipe(new_pipe_fd) < 0)
		return (-1);
	if (write_heredoc(node->heredoc) == FAILURE)
		return (-1);
	child_pid = fork();
	if (child_pid < 0)
	{
		close_and_unlink(&node->heredoc, TRUE);
		return (child_pid);
	}
	if (child_pid == 0)
	{
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

void	handle_pipelines(t_pipe_list *pipe_list)
{
	t_pipe_list	*tmp_node;
	int			last_pipe_fd[2];
	pid_t		child_pid;

	tmp_node = pipe_list;
	init_pipe_fd(last_pipe_fd);
	while (tmp_node)
	{
		child_pid = do_pipe(pipe_list, tmp_node, last_pipe_fd);
		if (child_pid < 0)
		{
			perror("do_pipe");
			return ;
		}
		tmp_node->pid = child_pid;
		tmp_node = tmp_node->next;
	}
}
