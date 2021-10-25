/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 22:00:28 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/25 23:34:30 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

void	init_builtins(char **builtins)
{
	builtins[ECHO] = ft_strdup("echo");
	builtins[CD] = ft_strdup("cd");
	builtins[PWD] = ft_strdup("pwd");
	builtins[EXPORT] = ft_strdup("export");
	builtins[UNSET] = ft_strdup("unset");
	builtins[ENV] = ft_strdup("env");
	builtins[EXIT] = ft_strdup("exit");
}

void	free_builtins(char **builtins)
{
	int	i;

	i = -1;
	while (++i < BUILTIN_NUM)
		free(builtins[i]);
}

void	init_builtin_funcs(void)
{
	g_request.builtin_funcs[ECHO] = execute_echo;
	g_request.builtin_funcs[CD] = execute_cd;
	g_request.builtin_funcs[PWD] = execute_pwd;
	g_request.builtin_funcs[EXPORT] = execute_export;
	g_request.builtin_funcs[UNSET] = execute_unset;
	g_request.builtin_funcs[ENV] = execute_env;
	g_request.builtin_funcs[EXIT] = execute_exit;
}

t_builtin_id	get_builtin_id(const char *token)
{
	t_builtin_id	builtin_id;
	char			*builtins[BUILTIN_NUM];

	if (!token)
		return (NON_BUILTIN);
	builtin_id = -1;
	init_builtins(builtins);
	while (++builtin_id < BUILTIN_NUM)
		if (!ft_strcmp(builtins[builtin_id], token))
			break ;
	free_builtins(builtins);
	return (builtin_id);
}
