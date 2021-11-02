/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:51:41 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/11/02 21:51:41 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

int	keylen(char *s)
{
	int	len;

	len = 0;
	while (s && s[len] && !is_env_end(s[len]))
		len++;
	return (len);
}

void	move_token_pointer(char **token, int i)
{
	if ((*token)[i])
		i++;
	*token += i;
}

void append_doll(char **token, t_token **expanded_tokens, int i)
{
	append_token(expanded_tokens,
		new_token(ft_strndup((*token + i - 1), 1)));
	*token += i;
}
