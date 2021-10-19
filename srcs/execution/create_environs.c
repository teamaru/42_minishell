/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_environs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 17:56:21 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/19 15:16:38 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

static int	env_listsize(t_environ *environs)
{
	int			size;
	t_environ	*environ;

	environ = environs;
	size = 0;
	while (environ)
	{
		size++;
		environ = environ->next;
	}
	return (size);
}

static char	*join_env(t_environ *environ)
{
	char	*env;
	char	*tmp;

	tmp = ft_strjoin(environ->key, "=");
	env = ft_strjoin(tmp, environ->value);
	free(tmp);
	return (env);
}

char	**env_list_to_array(t_environ *environs)
{
	int			i;
	char		**array;
	t_environ	*environ;

	array = malloc(sizeof(char *) * (env_listsize(environs) + 1));
	if (!array)
		return (NULL);
	environ = environs;
	i = -1;
	while (environ)
	{
		array[++i] = join_env(environ);
		environ = environ->next;
	}
	array[i + 1] = NULL;
	return (array);
}
