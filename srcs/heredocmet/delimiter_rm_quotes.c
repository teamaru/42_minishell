/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_rm_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:30:09 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/16 12:55:19 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static size_t	count_non_quotes(char *str)
{
	size_t	size_non_quotes;
	int		i;

	size_non_quotes = 0;
	i = -1;
	while (str[++i])
		if (!is_quote(str[i]))
			size_non_quotes += 1;
	return (size_non_quotes);
}

char	*rm_quotes(char *str)
{
	char	*str_without_quots;
	int		i;
	int		index;
	size_t	len;

	len = count_non_quotes(str);
	if (!len)
		return (ft_strdup(str));
	else
	{
		i = -1;
		index = -1;
		str_without_quots = (char *)ft_calloc(len + 1, sizeof(char));
		while (str[++i])
			if (!is_quote(str[i]))
				str_without_quots[++index] = str[i];
	}
	return (str_without_quots);
}
