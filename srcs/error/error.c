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

#include "../../includes/mini_shell.h"

t_bool print_err_msg(t_request *request, char *msg)
{
  printf(MSG_HEADER);
  if (request->cmd)
    printf("%s: ", request->cmd);
  if (request->arguments)
    printf("%s: ", request->arguments->arg);
  printf("%s", msg);
  return (FALSE);
}

void my_exit(t_request *request, int exit_cd)
{
  free_all(request);
  exit(exit_cd);
}
