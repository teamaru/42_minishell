/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_to_pipe_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:11:45 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/27 17:00:39 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>
#include <convert.h>

void	print_cmd_args(const char **args)
{
	int	i;
	i = -1;
	printf("\n>>>>>>>>>>>\n");
	while (args[++i])
		printf("arg[%d]: %s\n", i, args[i]);
	printf("<<<<<<<<<<<\n");
}

void	add_pipe_list(t_pipe_list **list, t_pipe_list *node)
{
	t_pipe_list	*tmp;

	if (!(*list))
		*list = node;
	else
	{
		tmp = (*list);
		while (tmp)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void	init_pipe_list_node(t_pipe_list **node)
{
	(*node)->output_rd = NULL;
	(*node)->input_rd = NULL;
	(*node)->cmd_args = NULL;
	(*node)->next = NULL;
}

t_pipe_list	*create_pipe_list(t_request *request)
{
	t_pipe_list	*node;
	t_pipe_list	*list;
	t_cmd		*cmd;


	cmd = request->cmds;
	list = NULL;
	while (cmd)
	{
		node = (t_pipe_list *)malloc(sizeof(t_pipe_list));
		if (!node)
			return (NULL);
		init_pipe_list_node(&node);
		node->cmd_args = create_cmd_args(cmd->args);
		print_cmd_args(node->cmd_args);
		add_pipe_list(&list, node);
		cmd = cmd->next;
	}
	return (list);
}
