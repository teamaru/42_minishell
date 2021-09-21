/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 23:12:29 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/29 23:12:29 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_bool execute_pwd(t_request *request)
{
  char path[BUFSIZ];

  (void)request;
  path[0] = '0';
  getcwd(path, BUFSIZ);
  printf("%s\n", path);
  return (TRUE);
}
