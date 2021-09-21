/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:45:50 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/06/08 14:45:50 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_bool process_request(t_request *request, char *line)
{
  init_request(request);
  tokenize(request, line);
  if (!is_valid_syntax(request))
    return (TRUE);
  parse(request);
  /*
  if (!exec_request(request))
    return (FALSE);
    */
  free_all(request);
  return (TRUE);
}

t_bool is_valid_request(t_request *request)
{
  if (request->cmd_id == INVLD_CMD)
    return (print_err_msg(request, ERR_MSG_INVLD_CMD));
  if (request->option == INVLD_OPT)
    return (print_err_msg(request, ERR_MSG_INVLD_OPT));
  return (TRUE);
}

void execute_child_process(t_request *request)
{
  t_cmd_func cmd_funcs[CMD_NUM];

  if (request->excution)
    execute_executable(request);
  if (!is_valid_request(request))
    my_exit(request, FAILURE);
  init_cmd_funcs(cmd_funcs);
  cmd_funcs[request->cmd_id](request);
  my_exit(request, SUCCESS);
}

t_bool exec_request(t_request *request)
{
  pid_t c_pid;

  if (request->cmd_id == EXIT)
    return (execute_exit(request));
  c_pid = fork();
  if (c_pid == -1)
    print_err_msg(request, strerror(errno));
  if (c_pid == 0)
    execute_child_process(request);
  if (c_pid > 0)
    wait(NULL);
  return (TRUE);
}

void init_request(t_request *request)
{
  request->tokens = NULL;
  request->cmds = NULL;
  request->cmd = NULL;
  request->cmd_id = INVLD_CMD;
  request->option = NON;
  request->arguments = NULL;
  request->excution = FALSE;
  request->exit_cd = 0;
}
