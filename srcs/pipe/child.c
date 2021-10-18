/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:02:59 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/18 20:03:21 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	child_operate_pipe_fd(t_pipe_list *first, t_pipe_list *node, int last_pipe_fd[2], int new_pipe_fd[2])
{
	if (!has_pipe(node))
		read_pipe(last_pipe_fd);
	else if (first == node)
		write_pipe(new_pipe_fd);
	else
	{
		read_pipe(last_pipe_fd);
		write_pipe(new_pipe_fd);
	}
}
