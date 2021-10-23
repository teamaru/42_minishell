/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_in_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:25:10 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/21 16:33:17 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

void	exit_heredocument(int sig_no)
{
	(void)sig_no;
	g_request.interrupt_heredocument = TRUE;
	g_request.exit_cd = 1;
}

t_result	set_signal_in_heredocument(void)
{
	struct sigaction	int_act;

	ft_bzero(&int_act, sizeof(int_act));
	int_act.sa_handler = exit_heredocument;
	if (sigaction(SIGINT, &int_act, NULL) != 0)
		return (FAILURE);
	return (SUCCESS);
}
