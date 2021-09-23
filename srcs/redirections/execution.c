/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 21:22:45 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/23 23:30:04 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <redirect.h>


void	exec_command(char *command)
{
	char	*arg[2];

	arg[0] = ft_strjoin("/bin/", command);
	arg[1] = NULL;
	if (execve(arg[0], arg, NULL) < 0)
	{
		printf("end in execuve\n");
		perror("execve");
		exit(1);
	}
}
