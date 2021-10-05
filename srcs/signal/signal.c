/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 12:38:09 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/03 12:38:09 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void init_signal(void)
{
  struct sigaction	int_act;

  ft_bzero(&int_act, sizeof(int_act));
  int_act.sa_handler = interrupt;
  if (sigaction(SIGINT, &int_act, NULL) != 0)
    exit(FAILURE);
  if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
    exit(FAILURE);
}

void interrupt(int sig_id)
{
  (void)sig_id;
  rl_replace_line("", 0);
  ft_putstr_fd("\n", 1);
  rl_on_new_line();
  rl_redisplay();
}
