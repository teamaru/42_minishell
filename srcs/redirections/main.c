/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:43:46 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/16 21:03:34 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./redirect.h"
#include "../../libft/includes/libft.h"

void	exec_command(char *command)
{
	char	*arg[2];

	arg[0] = ft_strjoin("/usr/bin/", command);
	arg[1] = NULL;
	if (execve(arg[0], arg, NULL) < 0)
	{
		perror("execve");
		exit(1);
	}
}

int	main(int ac, char **av)
{
	char *command;
	char *redirection;
	char *file_name;

	(void)ac;

	command = av[1];
	redirection = av[2];
	file_name = av[3];

	/*
	** < (input)
	*/
	if (!ft_strncmp(redirection, "<", 2) || !ft_strncmp(redirection, "0<", 3))
		redirecting_input(file_name);

	exec_command(command);
	return (0);
}
