/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:26:45 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/19 16:06:35 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_result	set_demi_heredoc_or_file_path(t_redirection_list **node,
	char *token)
{
	t_demi_for_heredoc	*demi;

	if ((*node)->type == HEREDOC)
	{
		(*node)->demi_heredoc = (t_demi_for_heredoc *)
			malloc(sizeof(t_demi_for_heredoc) * 1);
		if (!(*node)->demi_heredoc)
			return (FAILURE);
		demi = (*node)->demi_heredoc;
		demi->delimiter = ft_strdup(token);
		if (!demi->delimiter)
			return (FAILURE);
		demi->last_heredoc = FALSE;
	}
	else
	{
		(*node)->file_path = ft_strdup(token);
		if (!(*node)->file_path)
			return (FAILURE);
	}
	return (SUCCESS);
}

t_result	set_redirection_lists(t_pipe_list **pipe_node, t_token *rds)
{
	t_token				*tmp_token;
	t_token_type		token_type;
	t_redirection_list	*rd_node;

	tmp_token = rds;
	while (tmp_token)
	{
		token_type = tmp_token->type;
		if (is_type_redirect(tmp_token))
		{
			rd_node = add_new_rd_node(token_type,
					&(*pipe_node)->input_rd, &(*pipe_node)->output_rd);
			if (!rd_node)
				return (FAILURE);
		}
		else if (token_type == TYPE_STR || token_type == TYPE_EXPDBL)
		{
			if (set_demi_heredoc_or_file_path(&rd_node, tmp_token->token))
				return (FAILURE);
		}
		tmp_token = tmp_token->next;
	}
	return (SUCCESS);
}
