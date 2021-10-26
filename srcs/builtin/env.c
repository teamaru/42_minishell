/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 11:50:33 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/22 21:47:12 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

t_exit_cd	execute_env(const char **cmd_args, t_bool is_child_process)
{
	t_environ	*environ;

	(void)cmd_args;
	environ = g_request.environs;
	while (environ)
	{
		ft_putstr_fd(environ->key, STDOUT);
		ft_putstr_fd("=", STDOUT);
		ft_putstr_fd(environ->value, STDOUT);
		ft_putstr_fd("\n", STDOUT);
		environ = environ->next;
	}
	return (return_or_exit(SCCSS, is_child_process));
}
