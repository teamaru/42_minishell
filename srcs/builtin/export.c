/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 15:25:38 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/26 12:17:08 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

t_bool	replace_duplicated_environ(char *key, char *value)
{
	t_environ	*environ;

	environ = g_request.environs;
	while (environ)
	{
		if (!ft_strcmp(environ->key, key))
		{
			free(environ->value);
			environ->value = ft_strdup(value);
			return (TRUE);
		}
		environ = environ->next;
	}
	return (FALSE);
}

char	**split_key_value(char *arg)
{
	int		i;
	char	**split;

	split = malloc(sizeof(char *) * 3);
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	split[0] = ft_strndup(arg, i);
	if (ft_strlen(arg) == ft_strlen(split[0]))
	{
		free(split[0]);
		free(split);
		return (NULL);
	}
	split[1] = ft_strdup(arg + i + 1);
	split[2] = NULL;
	return (split);
}

t_exit_cd	declare_env(t_bool is_child_process)
{
	t_environ	*environ;

	environ = g_request.environs;
	while (environ)
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putstr_fd(environ->key, STDOUT);
		ft_putstr_fd("=", STDOUT);
		ft_putstr_fd(environ->value, STDOUT);
		ft_putstr_fd("\n", STDOUT);
		environ = environ->next;
	}
	return (return_or_exit(SCCSS, is_child_process));
}

t_bool	set_environ(char **split, t_bool flg)
{
	if (!is_valid_identifier(split[0]))
		flg = FALSE;
	if (!replace_duplicated_environ(split[0], split[1]))
		append_environ(&g_request.environs,
			new_environ(ft_strdup(split[0]), ft_strdup(split[1])));
	return (flg);
}

t_exit_cd	execute_export(const char **cmd_args, t_bool is_child_process)
{
	char	**split;
	int		i;
	int		flg;

	if (!cmd_args[1])
		return (declare_env(is_child_process));
	i = 0;
	flg = TRUE;
	while (cmd_args[++i])
	{
		split = split_key_value((char *)cmd_args[i]);
		if (!split)
		{
			if (!is_valid_identifier(cmd_args[i]))
				flg = FALSE;
			continue ;
		}
		flg = set_environ(split, flg);
		multi_free(split);
	}
	if (!flg)
		return (builtin_err(ERR_MSG_NOT_VLD_IDNTFR,
				GNRL_ERR, is_child_process));
	return (return_or_exit(SCCSS, is_child_process));
}
