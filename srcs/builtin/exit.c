/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 11:51:25 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/30 11:51:25 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request g_request;

t_bool is_all_digits(char *s)
{
  if (!s)
    return (FALSE);
  while (*s)
    if (!ft_isdigit(*s++))
      return (FALSE);
  return (TRUE);
}

t_bool execute_exit(const char **cmd_args, t_bool is_child_process)
{
  (void)is_child_process;
  printf(MSG_EXIT);
  if (!cmd_args[1])
    g_request.exit_cd = 0;
  else if (listsize(g_request.arguments) > 1)
  {
    g_request.exit_cd = 1;
    print_err_msg(ERR_MSG_TOO_MANY_ARGS);
    return (TRUE);
  }
  else if (!is_all_digits(g_request.arguments->arg))
  {
    g_request.exit_cd = 1;
    print_err_msg(ERR_MSG_INVLD_EXIT_CD);
  }
  free_all(TRUE);
  exit(0);
}
