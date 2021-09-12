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

#include "../../includes/mini_shell.h"


t_bool is_all_digits(char *s)
{
  if (!s)
    return (FALSE);
  while (*s)
  {
    if (!ft_isdigit(*s))
      return (FALSE);
    s++;
  }
  return (TRUE);
}

t_bool execute_exit(t_request *request)
{
  printf(MSG_EXIT);
  if (!request->arguments)
    request->exit_cd = 0;
  else if (listsize(request->arguments) > 1)
  {
    request->exit_cd = 1;
    print_err_msg(request, ERR_MSG_TOO_MANY_ARGS);
    return (TRUE);
  }
  else if (!is_all_digits(request->arguments->arg))
  {
    request->exit_cd = 1;
    print_err_msg(request, ERR_MSG_INVLD_EXIT_CD);
  }
  free_all(request);
  return (FALSE);
}
