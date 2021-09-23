/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:43:46 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/23 18:14:39 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./redirect.h"

void	exec_command(char *command)
{
	char	*arg[2];

	arg[0] = ft_strjoin("/bin/", command);
	arg[1] = NULL;
	if (execve(arg[0], arg, NULL) < 0)
	{
		perror("execve");
		exit(1);
	}
}

static char	*get_rd(int type)
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

void	print_t_command(t_command *cmd)
{
	t_redirection_list	*tmp;

	tmp = cmd->output_rd;
	printf("----OUTPUT----\n");
	while (tmp)
	{
		printf("fd       | %d\n", tmp->fd);
		printf("type     | %s\n", get_rd(tmp->type));
		printf("filepath | %s\n", tmp->file_path);
		printf("--------------\n");
		tmp = tmp->next;
	}
	tmp = cmd->input_rd;
	printf("----INPUT----\n");
	while (tmp)
	{
		printf("fd       | %d\n", tmp->fd);
		printf("type     | %s\n", get_rd(tmp->type));
		printf("filepath | %s\n", tmp->file_path);
		printf("--------------\n");
		tmp = tmp->next;
	}
}

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
	// int			i;
	// int			fd;

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
	print_t_command(&cmd);


	/*
	** < (input)
	*/
	// if (!ft_strncmp(redirection, "<", 2) || !ft_strncmp(redirection, "0<", 3))
	// 	redirecting_input(file_name);

	/*
	** > (output)
	*/
	// if (!ft_strncmp(redirection, ">", 2))
	// 	redirecting_output(file_name);

	/*
	** >> (appending output)
	*/
	// if (!ft_strncmp(redirection, ">>", 3))
	// 	redirecting_append(file_name);

	// exec_command(command);
	free_cmd(&cmd);
	return (0);
}
