/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 15:25:44 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/26 12:16:12 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

t_exit_cd	execute_unset(const char **cmd_args, t_bool is_child_process)
{
	int		i;
	t_bool	flg;

	i = 0;
	flg = TRUE;
	while (cmd_args[++i])
	{
		if (!is_valid_identifier(cmd_args[i]))
			flg = FALSE;
		delete_environ(&g_request.environs, get_target_environ(cmd_args[i]));
	}
	if (!flg)
		return (builtin_err(ERR_MSG_NOT_VLD_IDNTFR,
				GNRL_ERR, is_child_process));
	return (return_or_exit(SCCSS, is_child_process));
}
