/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 16:43:16 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/30 17:23:07 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

void	wait_processes(t_pipe_list *pipe_list)
{
	pid_t			changed_pid;
	t_pipe_list		*tmp_node;
	int				status;

	tmp_node = pipe_list;
	while (tmp_node)
	{
		changed_pid = waitpid(tmp_node->pid, &status, 0);
		g_request.exit_cd = WEXITSTATUS(status);
		if (changed_pid < 0)
		{
			perror("waitpid");
			return ;
		}
		tmp_node = tmp_node->next;
	}
}
