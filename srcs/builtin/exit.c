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

t_bool is_all_digits(const char *s)
{
  if (!s)
    return (FALSE);
  while (*s)
    if (!ft_isdigit(*s++))
      return (FALSE);
  return (TRUE);
}

int str_arr_size(const char **strs)
{
  int size;

  size = 0;
  while (strs[size])
    size++;
  return (size);
}

t_bool execute_exit(const char **cmd_args, t_bool is_child_process)
{
  (void)is_child_process;
  printf(MSG_EXIT);
  if (!cmd_args[1])
    g_request.exit_cd = SCCSS;
  else if (str_arr_size(cmd_args) > 2)
  {
    g_request.exit_cd = GNRL_ERR;
    print_err_msg(ERR_MSG_TOO_MANY_ARGS);
    return (TRUE);
  }
  else if (!is_all_digits(cmd_args[1]))
  {
    g_request.exit_cd = OUT_OF_EXT_STS;
    print_err_msg(ERR_MSG_INVLD_EXIT_CD);
  }
  my_exit(g_request.exit_cd);
  return (TRUE);
}
