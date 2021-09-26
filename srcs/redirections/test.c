/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 21:32:46 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/26 14:09:41 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <redirect.h>

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

void test_print_t_complete_cmd(t_complete_cmd *cmd)
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
