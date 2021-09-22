/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:43:46 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/22 23:47:45 by jnakahod         ###   ########.fr       */
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
	return (0);
}
