/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 22:16:45 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/22 22:00:23 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	get_delimiter(t_token **head, char **line)
{
	int	n;

	clear_white(line);
	if (!**line || !is_delimiter(**line))
		return ;
	n = 1;
	if (is_doble_redirect(*line))
		n++;
	append_token(head, new_token(ft_strndup(*line, n)));
	*line += n;
}

void	get_token(t_token **head, char **line)
{
	int	i;

	i = -1;
	clear_white(line);
	while ((*line)[++i] && !is_delimiter((*line)[i]))
		if (is_quote((*line)[i]))
			find_closing_qt(*line, &i);
	if (i != 0)
		append_token(head, new_token(ft_strndup(*line, i)));
	*line += i;
}

t_bool	split_token(t_token **head, t_token **token)
{
	t_token	*new_tokens;
	t_token	*prev;

	new_tokens = NULL;
	split_word(&new_tokens, (*token)->token);
	if (is_file_path(*token) && token_listsize(new_tokens) != 1)
		return (print_err_msg(ERR_MSG_AMBGS_RDRCT));
	insert_tokens(head, new_tokens, *token);
	prev = (*token)->prev;
	delete_token(head, *token);
	*token = prev;
	return (TRUE);
}

void	insert_token(t_token **head, t_token *new_token, t_token *target_token)
{
	t_token	*prev;

	if (!head)
		return (free_tokens(&new_token));
	if (!*head)
		return (append_token(head, new_token));
	if (!target_token)
		return (free_tokens(&new_token));
	prev = target_token->prev;
	target_token->prev = new_token;
	new_token->next = target_token;
	new_token->prev = prev;
	if (prev)
		prev->next = new_token;
	else
		*head = new_token;
}

void	tokenize(t_token **head, char *line)
{
	while (*line)
	{
		get_token(head, &line);
		get_delimiter(head, &line);
	}
}
