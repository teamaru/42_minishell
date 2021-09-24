/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:43:46 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/24 21:36:43 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./redirect.h"

void	free_t_redirection_list(t_redirection_list **node)
{
	t_redirection_list	*tmp;

	while (*node)
	{
		free_set((void **)&(*node)->file_path, NULL);
		tmp = (*node)->next;
		free_set((void **)node, NULL);
		*node = tmp;
	}
}

void	free_cmd(t_command *cmd)
{

	free_t_redirection_list(&cmd->output_rd);
	free_t_redirection_list(&cmd->input_rd);
}

int	main(int ac, char **av)
{
	char		*command;
	char		*redirection_list;
	char		*file_name;
	t_command	cmd;

	(void)ac;

	command = av[1];
	redirection_list = av[2];
	file_name = av[3];

	/*
	** リダイレクション単位でfdの設定
	*/
	cmd.output_rd = NULL;
	cmd.input_rd = NULL;
	if (create_t_redirection_list(av[2], &cmd))
	{
		printf("create_t_redirection_list error\n");
		return (-1);
	}

	// redirection list出力
	test_print_t_command(&cmd);
	// 複数リダイレクト(<, >, >>)実行部分
	if (change_multi_references(&cmd) < 0)
	{
		printf("error\n");
		free_cmd(&cmd);
	}

	free_cmd(&cmd);
	exec_command(command);
	return (0);
}
