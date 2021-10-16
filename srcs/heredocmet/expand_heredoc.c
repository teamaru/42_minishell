/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:44:05 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/16 12:57:09 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static t_bool	is_env_end_in_heredoc(char c)
{
	return (c == '\0' || c == '\n' || c == DLL
		|| c == SPC || c == SLSH || c == QSTN || is_quote(c));
}

static char	*get_env_key_in_heredoc(char **heredoc)
{
	int		env_index;
	char	*key;

	if (!**heredoc)
		return (NULL);
	env_index = 0;
	key = NULL;
	while (!is_env_end_in_heredoc((*heredoc)[env_index]))
		env_index++;
	if ((*heredoc)[env_index] == QSTN)
		env_index++;
	if (env_index > 0)
		key = ft_strndup(*heredoc, env_index);
	*heredoc += env_index;
	return (key);
}

static void	expand_single_env_in_heredoc(char **heredoc,
	int *i, char **expanded_heredoc)
{
	char	*pre_dollar;
	char	*key;
	char	*value;

	pre_dollar = ft_strndup(*heredoc, *i);
	free_set((void **)expanded_heredoc,
		(void *)ft_strjoin(*expanded_heredoc, pre_dollar));
	free_set((void **)&pre_dollar, NULL);
	*i += 1;
	*heredoc += *i;
	key = get_env_key_in_heredoc(heredoc);
	value = get_env_value(key);
	if (value)
		free_set((void **)expanded_heredoc,
			(void *)ft_strjoin(*expanded_heredoc, value));
	free_set((void **)&key, NULL);
	free_set((void **)&value, NULL);
}

static void	join_end_str(char *heredoc, char **expanded_heredoc, int i)
{
	char	*end_str;

	end_str = ft_strndup(heredoc, i);
	free_set((void **)expanded_heredoc,
		(void *)ft_strjoin(*expanded_heredoc, end_str));
	free_set((void **)&end_str, NULL);
}

t_result	expand_heredoc(char **contents)
{
	int		i;
	char	*heredoc;
	char	*expanded_heredoc;

	if (!*contents)
		return (SUCCESS);
	i = 0;
	heredoc = *contents;
	expanded_heredoc = NULL;
	while (heredoc[i])
	{
		if (is_dollar(heredoc[i]))
		{
			expand_single_env_in_heredoc(&heredoc, &i, &expanded_heredoc);
			i = -1;
		}
		i++;
	}
	if (i > 0)
		join_end_str(heredoc, &expanded_heredoc, i);
	free_set((void **)contents, (void *)expanded_heredoc);
	return (SUCCESS);
}
