/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:51:50 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/29 15:51:50 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request g_request;

t_bool print_err_msg(char *msg)
{
  g_request.exit_cd = GNRL_ERR;
  printf(MSG_HEADER);
  printf("%s\n", msg);
  return (FALSE);
}

void my_exit(t_exit_cd exit_cd)
{
  free_all(TRUE);
  exit(exit_cd);
}
