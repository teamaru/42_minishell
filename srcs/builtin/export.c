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

void	add_declear_pwd(char **split, t_bool *is_declear, char *key)
{
	free(split[1]);
	if (!ft_strcmp(key, "PWD"))
		split[1] = stringify_pwd(g_request.pwd);
	else
		split[1] = ft_strdup(g_request.oldpwd);
	*is_declear = FALSE;
}

t_bool handle_export(char *cmd_arg)
{
	t_bool flg;
	t_bool is_declear;
	char **split;

	flg = TRUE;
	is_declear = FALSE;
	split = split_key_value(cmd_arg, &is_declear);
	if (!split || !ft_strcmp(split[0], ""))
		return (print_err_msg(ERR_MSG_NOT_VLD_IDNTFR, GNRL_ERR));
	if (!is_valid_identifier(split[0]))
		flg = print_err_msg(ERR_MSG_NOT_VLD_IDNTFR, GNRL_ERR);
	flg = set_environ(split, flg, is_declear);
	multi_free(split);
	return (flg);
}

t_exit_cd	execute_export(const char **cmd_args, t_bool is_child_process)
{
	int		i;
	int		flg;

	if (!cmd_args[1])
		return (declare_env(is_child_process));
	i = 0;
	flg = TRUE;
	while (cmd_args[++i])
		flg = handle_export((char *)cmd_args[i]);
	if (!flg)
		return (return_or_exit(GNRL_ERR, is_child_process));
	return (return_or_exit(SCCSS, is_child_process));
}
