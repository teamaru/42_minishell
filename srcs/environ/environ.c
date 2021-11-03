/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:23:01 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/11/02 21:41:11 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

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

void	replace_env_value(char *target_key, char *new_value)
{
	t_environ	*target_environ;

	target_environ = get_target_environ(target_key);
	if (!target_environ)
		return ;
	free(target_environ->value);
	target_environ->value = ft_strdup(new_value);
	target_environ->is_declear = FALSE;
}

t_environ	*get_target_environ(const char *key)
{
	t_environ	*environ;

	environ = g_request.environs;
	while (environ)
	{
		if (!ft_strcmp(environ->key, key))
			return (environ);
		environ = environ->next;
	}
	return (NULL);
}

void	print_environ(t_environ *head)
{
	t_environ	*environ;

	environ = head;
	while (environ)
	{
		printf("environ key :%s\n", environ->key);
		printf("environ value :%s\n", environ->value);
		environ = environ->next;
	}
}

void	make_environ_hash(void)
{
	extern char	**environ;
	char		**env;
	char		**split;
	t_environ	*oldpwd;

	env = environ;
	g_request.environs = NULL;
	while (*env)
	{
		split = ft_split(*env++, '=');
		append_environ(&g_request.environs,
			new_environ(ft_strdup(split[0]), ft_strdup(split[1]), FALSE));
		multi_free(split);
	}
	oldpwd = get_target_environ("OLDPWD");
	free(oldpwd->value);
	oldpwd->value = NULL;
	oldpwd->is_declear = TRUE;
}
