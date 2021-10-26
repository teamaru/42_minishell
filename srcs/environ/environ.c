/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:23:01 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/22 22:23:01 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

void	replace_env_value(char *target_key, char *new_value)
{
	t_environ	*target_environ;

	target_environ = get_target_environ(target_key);
	if (!target_environ)
		return (append_environ(&g_request.environs,
			new_environ(ft_strdup(target_key), ft_strdup(new_value))));
	free(target_environ->value);
	target_environ->value = ft_strdup(new_value);
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

	env = environ;
	g_request.environs = NULL;
	while (*env)
	{
		split = ft_split(*env++, '=');
		append_environ(&g_request.environs,
			new_environ(ft_strdup(split[0]), ft_strdup(split[1])));
		multi_free(split);
	}
	delete_environ(&g_request.environs, get_target_environ("OLDPWD"));
}
