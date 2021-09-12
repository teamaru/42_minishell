/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 22:00:28 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/06/06 22:00:28 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	init_cmds(char **cmds)
{
	cmds[ECHO] = ft_strdup("echo");
	cmds[CD] = ft_strdup("cd");
	cmds[PWD] = ft_strdup("pwd");
	cmds[EXPORT] = ft_strdup("export");
	cmds[UNSET] = ft_strdup("unset");
	cmds[ENV] = ft_strdup("env");
	cmds[EXIT] = ft_strdup("exit");
}

void free_cmds(char **cmds)
{
  int i;

  i = -1;
  while (++i < CMD_NUM)
    free(cmds[i]);
}

void parse_cmd(t_request *request, char **line)
{
  char *cmds[CMD_NUM];

  clear_white(line);
  if (is_execution(request, line))
    return ;
  init_cmds(cmds);
  request->cmd = get_chunk(line);
  request->cmd_id = get_cmd_id(cmds, request->cmd);
  free_cmds(cmds);
}

void init_cmd_funcs(t_cmd_func *cmd_funcs)
{
  cmd_funcs[ECHO] = execute_echo;
  cmd_funcs[CD] = execute_cd;
  cmd_funcs[PWD] = execute_pwd;
  cmd_funcs[EXPORT] = execute_export;
  cmd_funcs[UNSET] = execute_exit;
  cmd_funcs[ENV] = execute_env;
  cmd_funcs[EXIT] = execute_exit;
}

t_cmd_id get_cmd_id(char **cmds, char *cmd)
{
  t_cmd_id cmd_id;

  cmd_id = -1;
  while (++cmd_id < CMD_NUM)
    if (!ft_strcmp(cmds[cmd_id], cmd))
      break;
  return (cmd_id);
}
