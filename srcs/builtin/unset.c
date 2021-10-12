/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 15:25:44 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/06/05 15:25:44 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request g_request;

t_bool execute_unset(const char **cmd_args, t_bool is_child_process)
{
  if (cmd_args[1])
    delete_environ(&g_request.environs, get_target_environ(cmd_args[1]));
  if (is_child_process)
    exit(0);
  return (TRUE);
}