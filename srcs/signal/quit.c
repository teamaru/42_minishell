/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:55:42 by jnakahod          #+#    #+#             */
/*   Updated: 2021/11/06 19:12:06 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

void	quit_in_execution(int sig_id)
{
	g_request.exit_cd = sig_id + 128;
	printf("Quit: %d\n", sig_id);
}

void	quit_act_in_execution(void)
{
	struct sigaction	quit_act;

	ft_bzero(&quit_act, sizeof(quit_act));
	quit_act.sa_handler = quit_in_execution;
	if (sigaction(SIGQUIT, &quit_act, NULL) != 0)
		exit(FAILURE);
}

void	quit_in_pipe_execution(int sig_id)
{
	g_request.exit_cd = sig_id + 128;
	if (g_request.pid <= 0)
		printf("Quit: %d\n", sig_id);
	else
		rl_redisplay();
}

void	quit_act_in_pipe_execution(void)
{
	struct sigaction	quit_act;

	ft_bzero(&quit_act, sizeof(quit_act));
	quit_act.sa_handler = quit_in_pipe_execution;
	if (sigaction(SIGQUIT, &quit_act, NULL) != 0)
		exit(FAILURE);
}
