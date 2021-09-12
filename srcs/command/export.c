/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 15:25:38 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/06/05 15:25:38 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

t_bool execute_export(t_request *request)
{
  int i;
  extern char **environ;

  (void)request;
  i = 0;
  while (environ[i])
    i++;
//  environ[i] = ft_strdup("test=test");
  setenv("test", "test", 0);
  return (TRUE);
}
