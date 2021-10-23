/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:36:40 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/22 22:36:40 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_bool	is_redirect(char c)
{
	return (c == R_RDRCT || c == L_RDRCT);
}

t_bool	is_doble_redirect(char *line)
{
	return (is_redirect(line[0]) && line[0] == line[1]);
}

t_bool	is_eos_token(t_token *token)
{
	t_token	*prev;

	prev = token->prev;
	if (!prev)
		return (FALSE);
	return (is_type_heredoc(prev));
}

t_bool	is_delimiter(int c)
{
	return (ft_strchr_i(DELIMITERS, c) != -1);
}

void	print_tokens(t_token *head)
{
	t_token	*token;

	token = head;
	while (token)
	{
		printf("token token:%s\n", token->token);
		printf("token type:%u\n", token->type);
		token = token->next;
	}
}
