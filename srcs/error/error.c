/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:51:50 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/23 19:07:07 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

t_bool	print_err_msg(char *msg, t_exit_cd exit_cd)
{
	if (!msg)
		perror(MSG_HEADER);
	else
	{
		ft_putstr_fd(MSG_HEADER, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	g_request.exit_cd = exit_cd;
	return (FALSE);
}

void	my_exit(t_exit_cd exit_cd)
{
	ft_putendl_fd(MSG_EXIT, STDERR);
	free_all(TRUE);
	exit(exit_cd);
}

t_exit_cd	builtin_err(char *msg, t_exit_cd exit_cd, t_bool is_child_process)
{
	print_err_msg(msg, exit_cd);
	if (is_child_process)
		exit(exit_cd);
	return (exit_cd);
}

void	print_err_and_exit(char *msg, t_exit_cd exit_cd)
{
	print_err_msg(msg, exit_cd);
	free_all(TRUE);
	exit(exit_cd);
}
