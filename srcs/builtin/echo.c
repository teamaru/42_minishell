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

t_bool	is_valid_opt(const char *opt)
{
	int i;

	i = 0;
	while (opt[++i])
		if (opt[i] != 'n')
			return (FALSE);
	return (TRUE);
}

t_exit_cd	execute_echo(const char **cmd_args, t_bool is_child_process)
{
	int		i;
	t_bool	has_opt;

	i = 1;
	if (cmd_args[i] && cmd_args[i][0] == '-')
		has_opt = is_valid_opt(cmd_args[i]);
	else
		has_opt = FALSE;
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
	return (return_or_exit(SCCSS, is_child_process));
}
