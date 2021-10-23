/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:34:02 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/22 22:34:02 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_bool	is_type_heredoc(t_token *token)
{
	return (token->type == TYPE_LL_RDRCT);
}

t_bool	is_type_redirect(t_token *token)
{
	return (token->type == TYPE_R_RDRCT
		|| token->type == TYPE_RR_RDRCT
		|| token->type == TYPE_L_RDRCT
		|| token->type == TYPE_LL_RDRCT);
}

t_bool	is_type_meta(t_token *token)
{
	return (token->type == TYPE_PIPE);
}

t_bool	is_quote_closed(t_token *token)
{
	int		i;
	t_bool	is_quote_closed;

	i = -1;
	is_quote_closed = TRUE;
	while (token->token[++i])
		if (is_quote(token->token[i]))
			is_quote_closed = find_closing_qt(token->token, &i);
	return (is_quote_closed);
}

t_bool	is_valid_token_pair(t_token *token)
{
	return (!((is_type_meta(token) && is_type_meta(token->next))
			|| (is_type_redirect(token) && is_type_meta(token->next))
			|| (is_type_redirect(token) && is_type_redirect(token->next))));
}
