/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:31:17 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/22 22:31:17 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

char	*join_expanded_tokens(t_token *expanded_tokens)
{
	t_token	*tmp_token;
	char	*joined_token;
	char	*tmp;

	tmp_token = expanded_tokens;
	joined_token = NULL;
	while (tmp_token)
	{
		tmp = joined_token;
		joined_token = ft_strjoin(joined_token, tmp_token->token);
		free(tmp);
		tmp_token = tmp_token->next;
	}
	return (joined_token);
}

int	get_str_len(char *token)
{
	char	qt;
	int		len;

	if (!token || !is_quote(*token))
		return (0);
	len = 1;
	qt = *token;
	while (token[len] && token[len] != qt)
		len++;
	return (len - 1);
}

void	get_word(t_token **new_tokens, char **line)
{
	int	i;

	i = -1;
	clear_white(line);
	while ((*line)[++i] && !is_white((*line)[i]))
		if (is_quote((*line)[i]))
			find_closing_qt(*line, &i);
	if (i != 0)
		append_token(new_tokens, new_token(ft_strndup(*line, i)));
	*line += i;
}

void	split_word(t_token **new_tokens, char *token)
{
	while (token && *token)
		get_word(new_tokens, &token);
}

t_bool	is_file_path(t_token *token)
{
	t_token	*prev;

	prev = token->prev;
	if (!prev)
		return (FALSE);
	return (is_type_redirect(prev));
}
