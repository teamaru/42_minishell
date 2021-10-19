/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_builin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:23:39 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/19 15:15:50 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

void	builtin_backup_fd(int backup_fd[3])
{
	backup_fd[0] = dup(STDIN);
	backup_fd[1] = dup(STDOUT);
	backup_fd[2] = dup(STDERR);
}

void	builtin_restore_fd(int backup_fd[3])
{
	dup2(backup_fd[0], STDIN);
	dup2(backup_fd[1], STDOUT);
	dup2(backup_fd[2], STDERR);
}

t_result	exec_simple_buitin(t_pipe_list *pipe_list, t_builtin_id builtin_id)
{
	int	backup_fd[3];

	if (write_heredoc(pipe_list->heredoc) == FAILURE)
		return (FAILURE);
	builtin_backup_fd(backup_fd);
	if (change_multi_references(pipe_list) < 0)
		print_err_and_exit(NULL, GNRL_ERR);
	g_request.builtin_funcs[builtin_id](pipe_list->cmd_args, FALSE);
	builtin_restore_fd(backup_fd);
	return (SUCCESS);
}
