/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:07:08 by jnakahod          #+#    #+#             */
/*   Updated: 2021/11/07 22:34:58 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

void	cmd_set_exit_cd(int status, pid_t changed_pid)
{
	t_exit_cd	exit_cd;

	exit_cd = g_request.exit_cd;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			rl_replace_line("", 0);
			ft_putstr_fd("\n", 1);
		}
	}
	if (changed_pid > 0
		|| (!WIFSIGNALED(status) && exit_cd != 130 && exit_cd != 131))
		g_request.exit_cd = WEXITSTATUS(status);
}

void	nothing(int sig_no)
{
	(void)sig_no;
}

void	exec_simple_cmd(t_pipe_list *pipe_list)
{
	pid_t	changed_pid;
	int		status;

	if (write_heredoc(pipe_list->heredoc) == FAILURE)
		return ;
	signal(SIGINT, nothing);
	pipe_list->pid = fork();
	if (pipe_list->pid == -1)
	{
		print_err_msg(NULL, GNRL_ERR);
		close_and_unlink(&pipe_list->heredoc, TRUE);
		return ;
	}
	else if (pipe_list->pid == 0)
		child_exec_cmd(pipe_list);
	else
	{
		close_and_unlink(&pipe_list->heredoc, FALSE);
		if (kill(pipe_list->pid, 0) == -1)
			print_err_msg(NULL, GNRL_ERR);
		// printf("ps id = %d\n", pipe_list->pid);
		changed_pid = waitpid(pipe_list->pid, &status, 0);
		cmd_set_exit_cd(status, changed_pid);
	}
	g_request.pid = 0;
}
