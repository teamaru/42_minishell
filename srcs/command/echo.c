/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 19:12:21 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/30 19:12:21 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request g_request;

t_bool execute_echo(void)
{
  t_argument *argument;

  argument = g_request.arguments;
  while (argument)
  {
    ft_putstr_fd(argument->arg, STDOUT);
    argument = argument->next;
    if (argument)
      ft_putstr_fd(" ", STDOUT);
  }
  if (g_request.option != N)
    ft_putstr_fd("\n", STDOUT);
  return (TRUE);
}
