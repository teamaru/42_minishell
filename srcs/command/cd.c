/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 23:21:06 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/29 23:21:06 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request g_request;

t_bool execute_cd(void)
{
  char *path;

  path = g_request.arguments->arg;
  if (!*path)
    path = ROOT;
  if (chdir(path) == -1)
    print_err_msg(strerror(errno));
  return (TRUE);
}
