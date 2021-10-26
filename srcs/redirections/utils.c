/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:44:49 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/26 21:47:03 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_bool	is_last_heredoc(t_redirection_list *node)
{
	if (node->type == HEREDOC && node->demi_heredoc->last_heredoc)
		return (TRUE);
	return (FALSE);
}

t_bool	is_heredoc(t_redirection_list *node)
{
	if (node->type == HEREDOC)
		return (TRUE);
	return (FALSE);
}
