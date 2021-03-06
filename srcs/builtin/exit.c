/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 11:51:25 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/25 23:37:20 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

t_bool	is_all_digits(const char *s)
{
	int		i;
	char	*trimmed;
	t_bool	flg;

	if (!s)
		return (FALSE);
	i = -1;
	flg = TRUE;
	trimmed = ft_strtrim(s, " ");
	if (trimmed[0] == '+' || trimmed[0] == '-')
		i++;
	if (!trimmed[i + 1])
		flg = FALSE;
	while (trimmed[++i])
		if (!ft_isdigit(trimmed[i]))
			flg = FALSE;
	free(trimmed);
	return (flg);
}

int	str_arr_size(const char **strs)
{
	int	size;

	size = 0;
	while (strs[size])
		size++;
	return (size);
}

t_exit_cd	execute_exit(const char **cmd_args, t_bool is_child_process)
{
	(void)is_child_process;
	if (!cmd_args[1])
		my_exit(g_request.exit_cd);
	else if (!is_all_digits(cmd_args[1]))
		my_exit(builtin_err(ERR_MSG_INVLD_EXIT_CD,
				OUT_OF_EXT_STS, is_child_process));
	else if (str_arr_size(cmd_args) > 2)
		return (builtin_err(ERR_MSG_TOO_MANY_ARGS, GNRL_ERR, is_child_process));
	else
		g_request.exit_cd = ft_atoi((char *)cmd_args[1]);
	my_exit(g_request.exit_cd);
	return (SCCSS);
}
