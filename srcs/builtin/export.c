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

#include <mini_shell.h>

extern t_request g_request;

t_bool is_key_exist(char *key)
{
  t_environ *environ;

  environ = g_request.environs;
  while (environ)
  {
    if (!ft_strcmp(environ->key, key))
      return (TRUE);
    environ = environ->next;
  }
  return (FALSE);
}

t_bool replace_duplicated_environ(char *key, char *value)
{
  t_environ *environ;

  environ = g_request.environs;
  while (environ)
  {
    if (!ft_strcmp(environ->key, key))
    {
      free(environ->value);
      environ->value = ft_strdup(value);
      return (TRUE);
    }
    environ = environ->next;
  }
  return (FALSE);
}

t_bool execute_export(const char **cmd_args)
{
  char **split;

  if (!cmd_args[1])
    return (TRUE);
  split = ft_split(cmd_args[1], '=');
  if (!replace_duplicated_environ(split[0], split[1]))
    append_environ(&g_request.environs, new_environ(ft_strdup(split[0]), ft_strdup(split[1])));
  multi_free(split);
  return (TRUE);
}
