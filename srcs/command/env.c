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

t_bool execute_env(void)
{
  extern char **environ;
  char **env;

  env = environ;
  while (*env)
    printf("%s\n", *env++);
  return (TRUE);
}
