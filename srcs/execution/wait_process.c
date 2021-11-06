/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 16:43:16 by jnakahod          #+#    #+#             */
/*   Updated: 2021/11/06 18:50:57 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

void	wait_processes(t_pipe_list *pipe_list, pid_t	last_child_pid)
{
	pid_t			changed_pid;
	t_pipe_list		*tmp_node;
	int				status;

	quit_act_in_pipe_execution();
	tmp_node = pipe_list;
	changed_pid = waitpid(last_child_pid, &status, 0);
	g_request.pid = changed_pid;
	while (wait(NULL) > 0)
		;
	cmd_set_exit_cd(status, changed_pid);
}
