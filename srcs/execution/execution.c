/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:48:24 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/06/08 14:48:24 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_bool is_execution(t_request *request, char **line)
{
  if (**line == PERIOD || **line == SLSH)
  {
    request->excution = TRUE;
    return (TRUE);
  }
  return (FALSE);
}

t_bool execute_executable(t_request *request)
{
  char **args;
  extern char **environ;

  args = list_to_array(request->arguments);
  if (execve(request->arguments->arg, args, environ) == -1)
  {
    print_err_msg(request, strerror(errno));
    exit(FAILURE);
  }
  multi_free(args);
  return (TRUE);
}
