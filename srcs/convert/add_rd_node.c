/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_rd_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:00:33 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/19 16:05:47 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static void	set_rd_fd(t_redirection_list **node, t_token_type type)
{
	if (type == TYPE_R_RDRCT || type == TYPE_RR_RDRCT)
		(*node)->fd = 1;
	else
		(*node)->fd = 0;
}

static void	set_rd_type(t_redirection_list **node, t_token_type type)
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

static t_redirection_list	*new_rd_list_node(t_token_type type)
{
	t_redirection_list	*res;

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

static void	add_node_to_rd_list(t_redirection_list **first,
	t_redirection_list *node)
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

t_redirection_list	*add_new_rd_node(t_token_type token_type,
	t_redirection_list **input, t_redirection_list **output)
{
	t_redirection_list	*rd_node;

	rd_node = new_rd_list_node(token_type);
	if (!rd_node)
		return (NULL);
	if (rd_node->type == INPUT || rd_node->type == HEREDOC)
		add_node_to_rd_list(input, rd_node);
	else if (rd_node->type == OUTPUT || rd_node->type == APPEND)
		add_node_to_rd_list(output, rd_node);
	return (rd_node);
}
