/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 19:12:21 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/22 21:46:48 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

t_exit_cd	execute_echo(const char **cmd_args, t_bool is_child_process)
{
	int		i;
	t_bool	has_opt;

	i = 1;
	has_opt = (cmd_args[i] && !ft_strcmp(cmd_args[i], "-n"));
	if (has_opt)
		i++;
	while (cmd_args[i])
	{
		ft_putstr_fd((char *)cmd_args[i++], STDOUT);
		if (cmd_args[i])
			ft_putstr_fd(" ", STDOUT);
	}
	if (!has_opt)
		ft_putstr_fd("\n", STDOUT);
	if (is_child_process)
		exit(SCCSS);
	return (SCCSS);
}
