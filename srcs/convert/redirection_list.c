/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:26:45 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/08 23:13:50 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	set_rd_fd(t_redirection_list **node, t_token_type type)
{
	if (type == TYPE_R_RDRCT || type == TYPE_RR_RDRCT)
		(*node)->fd = 1;
	else
		(*node)->fd = 0;
}

void	set_rd_type(t_redirection_list **node, t_token_type type)
{
	if (type == TYPE_R_RDRCT)
		(*node)->type = OUTPUT;
	else if (type == TYPE_RR_RDRCT)
		(*node)->type = APPEND;
	else if (type == TYPE_L_RDRCT)
		(*node)->type = INPUT;
	else
		(*node)->type = HEREDOC;
}

t_redirection_list	*new_rd_list_node(t_token_type type)
{
	t_redirection_list *res;

	res = (t_redirection_list *)malloc(sizeof(t_redirection_list));
	if (!res)
		return (NULL);
	set_rd_fd(&res, type);
	set_rd_type(&res, type);
	res->file_path = NULL;
	res->demi_heredoc = NULL;
	res->next = NULL;
	return (res);
}

void	add_node_to_rd_list(t_redirection_list **first, t_redirection_list *node)
{
	t_redirection_list	*tmp;

	if (!*first)
		*first = node;
	else
	{
		tmp = *first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

t_result	set_demi_heredoc_or_file_path(t_redirection_list **node, char *token)
{
	t_demi_for_heredoc	*demi;

	if ((*node)->type == HEREDOC)
	{
		(*node)->demi_heredoc = (t_demi_for_heredoc *)malloc(sizeof(t_demi_for_heredoc) * 1);
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
	t_token			*tmp_token;
	t_token_type	token_type;
	t_redirection_list	*rd_node;

	tmp_token = rds;
	while(tmp_token)
	{
		token_type = tmp_token->type;
		if (is_type_redirect(tmp_token))
		{
			rd_node = new_rd_list_node(token_type);
			if (!rd_node)
				return (FAILURE);
			if (rd_node->type == INPUT || rd_node->type == HEREDOC)
				add_node_to_rd_list(&(*pipe_node)->input_rd, rd_node);
			else if (rd_node->type == OUTPUT || rd_node->type == APPEND)
				add_node_to_rd_list(&(*pipe_node)->output_rd, rd_node);
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
