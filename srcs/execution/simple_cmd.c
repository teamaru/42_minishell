/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:07:08 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/19 17:15:06 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

void	exec_simple_cmd(t_pipe_list *pipe_list)
{
	pid_t	changed_pid;
	int		status;

	if (write_heredoc(pipe_list->heredoc) == FAILURE)
		return ;
	pipe_list->pid = fork();
	if (pipe_list->pid == -1)
	{
		print_err_msg(NULL);
		close_and_unlink(&pipe_list->heredoc, TRUE);
		return ;
	}
	else if (pipe_list->pid == 0)
		child_exec_cmd(pipe_list);
	else
	{
		close_and_unlink(&pipe_list->heredoc, FALSE);
		if (kill(pipe_list->pid, 0) == -1)
			print_err_msg(NULL);
		g_request.pid = pipe_list->pid;
		changed_pid = waitpid(pipe_list->pid, &status, 0);
		g_request.exit_cd = WEXITSTATUS(status);
	}
	g_request.pid = 0;
}
