/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:25:40 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/18 14:26:49 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_bool is_match_str(char *input, char *delimiter)
{
	if (!ft_strncmp(input, delimiter, ft_strlen(delimiter) + 1))
		return (TRUE);
	return (FALSE);
}

t_bool	is_dollar(char c)
{
	if (c == DLL)
		return (TRUE);
	else
		return (FALSE);
}

t_bool has_heredoc(t_heredoc_to_fd *heredoc)
{
	if (heredoc)
		return (TRUE);
	else
		return (FALSE);
}
