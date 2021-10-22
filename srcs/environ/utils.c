/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:29:18 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/22 22:29:18 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

t_bool	is_env_end(char c)
{
	return (c == '\0' || c == DLL || c == SPC
		|| c == SLSH || c == QSTN || is_quote(c));
}

char	*get_env_key(char *token)
{
	int		i;
	char	*key;

	if (!*token)
		return (NULL);
	i = 0;
	key = NULL;
	while (!is_env_end(token[i]))
		i++;
	if (token[i] == QSTN)
		i++;
	if (i > 0)
		key = ft_strndup(token, i);
	return (key);
}

char	*get_env_value(char *key)
{
	t_environ	*environ;

	if (!key)
		return (NULL);
	if (*key == QSTN)
		return (ft_itoa(g_request.exit_cd));
	environ = g_request.environs;
	while (environ)
	{
		if (!ft_strcmp(environ->key, key))
			return (ft_strdup(environ->value));
		environ = environ->next;
	}
	return (NULL);
}

int	get_env_len(char *token)
{
	int	len;

	len = 0;
	while (!is_env_end(token[len]))
		len++;
	if (token[len] == QSTN)
		len++;
	return (len);
}
