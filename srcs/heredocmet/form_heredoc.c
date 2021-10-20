/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:20:29 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/20 19:14:54 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static t_bool	is_str_has_closed_quarts(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (is_quote(str[i]))
			if (find_closing_qt(str, &i))
				return (TRUE);
	}
	return (FALSE);
}

static t_bool	can_expand_heredoc(char *delimiter)
{
	if (is_str_has_closed_quarts(delimiter))
		return (FALSE);
	else
		return (TRUE);
}

void	form_heredocument(char *delimiter, char **heredoc)
{
	t_bool	expantable_heredoc;
	char	*delimiter_without_quotes;

	expantable_heredoc = can_expand_heredoc(delimiter);
	delimiter_without_quotes = rm_quotes(delimiter);
	/*signal_in_heredoc*/
	
	readline_input_heredoc(heredoc, delimiter_without_quotes);
	init_signal();
	if (expantable_heredoc)
		expand_heredoc(heredoc);
	free_set((void **)&delimiter_without_quotes, NULL);
}
