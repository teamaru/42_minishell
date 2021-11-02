/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 15:25:38 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/11/02 21:39:20 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

t_bool	replace_duplicated_environ(char *key, char *value, t_bool is_declear)
{
	t_environ	*environ;

	environ = g_request.environs;
	while (environ)
	{
		if (!ft_strcmp(environ->key, key))
		{
			if (!is_declear)
			{
				free(environ->value);
				environ->value = ft_strdup(value);
				environ->is_declear = is_declear;
			}
			return (TRUE);
		}
		environ = environ->next;
	}
	return (FALSE);
}

char	**split_key_value(char *arg, t_bool *is_declear)
{
	int		i;
	char	**split;

	split = malloc(sizeof(char *) * 3);
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (i == 0)
	{
		free(split);
		return (NULL);
	}
	split[0] = ft_strndup(arg, i);
	if (ft_strlen(arg) != ft_strlen(split[0]))
		split[1] = ft_strdup(arg + i + 1);
	else
	{
		*is_declear = TRUE;
		split[1] = NULL;
	}
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
		if (!environ->is_declear)
		{
			ft_putstr_fd("=\"", STDOUT);
			ft_putstr_fd(environ->value, STDOUT);
			ft_putstr_fd("\"", STDOUT);
		}
		ft_putstr_fd("\n", STDOUT);
		environ = environ->next;
	}
	return (return_or_exit(SCCSS, is_child_process));
}

void	add_declear_pwd(char **split, t_bool *is_declear, char *key)
{
	free(split[1]);
	if (!ft_strcmp(key, "PWD"))
		split[1] = stringify_pwd();
	else
		split[1] = ft_strdup(g_request.oldpwd);
	*is_declear = FALSE;
}

t_bool	set_environ(char **split, t_bool flg, t_bool is_declear)
{
	if (!is_valid_identifier(split[0]))
		return (FALSE);
	if (!ft_strcmp(split[0], "PWD") && is_declear)
		add_declear_pwd(split, &is_declear, "PWD");
	else if (!ft_strcmp(split[0], "OLDPWD") && g_request.oldpwd && is_declear)
		add_declear_pwd(split, &is_declear, "OLD");
	if (!replace_duplicated_environ(split[0], split[1], is_declear))
		append_environ(&g_request.environs,
			new_environ(ft_strdup(split[0]), ft_strdup(split[1]), is_declear));
	return (flg);
}

t_exit_cd	execute_export(const char **cmd_args, t_bool is_child_process)
{
	char	**split;
	int		i;
	int		flg;
	t_bool	is_declear;

	if (!cmd_args[1])
		return (declare_env(is_child_process));
	i = 0;
	flg = TRUE;
	while (cmd_args[++i])
	{
		is_declear = FALSE;
		split = split_key_value((char *)cmd_args[i], &is_declear);
		if (!split || !ft_strcmp(split[0], ""))
		{
			if (!is_valid_identifier(cmd_args[i]))
				flg = print_err_msg(ERR_MSG_NOT_VLD_IDNTFR, GNRL_ERR);
			continue ;
		}
		flg = set_environ(split, flg, is_declear);
		multi_free(split);
	}
	if (!flg)
		return (return_or_exit(GNRL_ERR, is_child_process));
	return (return_or_exit(SCCSS, is_child_process));
}
