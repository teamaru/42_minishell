/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:51:50 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/18 10:37:24 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request g_request;

t_bool print_err_msg(char *msg)
{
  printf(MSG_HEADER);
  printf("%s\n", msg);
  return (FALSE);
}

void my_exit(t_exit_cd exit_cd)
{
  free_all(TRUE);
  exit(exit_cd);
}

void	print_err_and_exit(char *msg, t_exit_cd exit_cd)
{
	if (!msg)
		perror("mini_shell");
	else
	{
		printf(MSG_HEADER);
		printf("%s\n", msg);
	}
	free_all(TRUE);
	exit(exit_cd);
}
