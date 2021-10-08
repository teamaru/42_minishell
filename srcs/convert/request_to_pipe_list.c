/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_to_pipe_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:11:45 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/04 15:53:19 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request g_request;

static char *test_get_rd(int type)
{
	if (type == INPUT)
		return ("<");
	else if (type == OUTPUT)
		return (">");
	else if (type == APPEND)
		return (">>");
	else
		return ("<<");
}

void	print_cmd_args(const char **args)
{
	int	i;
	i = -1;
	printf("\n>>> ARGS INFO >>>\n");
	while (args[++i])
		printf("arg[%d]: %s\n", i, args[i]);
	printf("<<<<<<<<<<<<<<<<\n\n");
}

void test_print_rd_info(t_pipe_list *cmd)
{
	t_redirection_list *tmp;

	tmp = cmd->output_rd;
	printf("----OUTPUT----\n");
	while (tmp)
	{
		printf("fd       | %d\n", tmp->fd);
		printf("type     | %s\n", test_get_rd(tmp->type));
		printf("filepath | %s\n", tmp->file_path);
		printf("--------------\n");
		tmp = tmp->next;
	}
	tmp = cmd->input_rd;
	printf("----INPUT----\n");
	while (tmp)
	{
		printf("fd       | %d\n", tmp->fd);
		printf("type     | %s\n", test_get_rd(tmp->type));
		printf("filepath | %s\n", tmp->file_path);
		printf("--------------\n");
		tmp = tmp->next;
	}
}


void	print_pipe_node_info(t_pipe_list *node)
{
	print_cmd_args(node->cmd_args);
	test_print_rd_info(node);
}

void	add_pipe_list(t_pipe_list **list, t_pipe_list *node)
{
	t_pipe_list	*tmp;

	if (!(*list))
		*list = node;
	else
	{
		tmp = *list;
		while (tmp->next)
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

t_pipe_list	*create_pipe_list()
{
	t_pipe_list	*node;
	t_pipe_list	*list;
	t_cmd		*cmd;

	cmd = g_request.cmds;
	list = NULL;
	while (cmd)
	{
		node = (t_pipe_list *)malloc(sizeof(t_pipe_list));
		if (!node)
			return (NULL);
		init_pipe_list_node(&node);
		node->cmd_args = create_cmd_args(cmd->args);
		set_redirection_lists(&node, cmd->rds);
		// print_pipe_node_info(node);
		add_pipe_list(&list, node);
		cmd = cmd->next;
	}
	return (list);
}
