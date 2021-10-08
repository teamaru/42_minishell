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

t_bool execute_cd(const char **cmd_args)
{
  char pwd[BUFSIZ];
  char* path;

  pwd[0] = '0';
  getcwd(pwd, BUFSIZ);
  replace_env_value("OLDPWD", pwd);
  path = (char *)cmd_args[1];
  if (!path)
    path = ROOT;
  if (chdir(path) == -1)
    print_err_msg(strerror(errno));
  getcwd(pwd, BUFSIZ);
  replace_env_value("PWD", pwd);
  return (TRUE);
}
