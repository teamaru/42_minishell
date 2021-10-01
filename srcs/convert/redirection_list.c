/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:26:45 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/01 12:45:44 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>
#include <convert.h>

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

t_bool	set_redirection_lists(t_pipe_list **pipe_node, t_token *rds)
{
	t_token			*tmp_token;
	t_token_type	token_type;
	t_redirection_list	*rd_node;

	tmp_token = rds;
	//rdsがNULLになるまでループ
	while(tmp_token)
	{
		token_type = tmp_token->type;
		// new redirection_list_node作成
		if (token_type == TYPE_R_RDRCT || token_type == TYPE_RR_RDRCT || token_type == TYPE_L_RDRCT || token_type == TYPE_LL_RDRCT)
		{
			rd_node = new_rd_list_node(token_type);
			if (!rd_node)
				return (FALSE);
			//リストに追加
			if (rd_node->type == INPUT || rd_node->type == HEREDOC)
				add_node_to_rd_list(&(*pipe_node)->input_rd, rd_node);
			else if (rd_node->type == OUTPUT || rd_node->type == APPEND)
				add_node_to_rd_list(&(*pipe_node)->output_rd, rd_node);
		}
		else if (token_type == TYPE_STR)
		{
			rd_node->file_path = ft_strdup(tmp_token->token);
			if (!rd_node->file_path)
				return (FALSE);
		}
		tmp_token = tmp_token->next;
	}
	return (TRUE);
}
