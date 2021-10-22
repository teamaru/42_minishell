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

extern t_request	g_request;

void init_signal(void)
{
  struct sigaction	int_act;
  struct sigaction	quit_act;

  ft_bzero(&int_act, sizeof(int_act));
  int_act.sa_handler = interrupt;
  ft_bzero(&quit_act, sizeof(quit_act));
  quit_act.sa_handler = quit;
  if (sigaction(SIGINT, &int_act, NULL) != 0)
    exit(FAILURE);
  if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
    exit(FAILURE);
  if (sigaction(SIGQUIT, &quit_act, NULL) != 0)
    exit(FAILURE);
}

void interrupt(int sig_id)
{
  (void)sig_id;
  rl_replace_line("", 0);
  ft_putstr_fd("\n", 1);
  if (g_request.pid != 0)
    return ;
  rl_on_new_line();
  rl_redisplay();
}

void quit(int sig_id)
{
  (void)sig_id;
  if (g_request.pid == 0)
  {
    rl_on_new_line();
    rl_redisplay();
  }
  else
    printf("Quit: %d\n", sig_id);
}
