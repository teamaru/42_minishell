/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 11:50:33 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/06/05 11:50:33 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_bool execute_env(t_request *request)
{
  extern char **environ;
  char **env;

  (void)request;
  env = environ;
  while (*env)
    printf("%s\n", *env++);
  return (TRUE);
}
