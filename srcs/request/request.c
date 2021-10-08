/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:45:50 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/05 14:47:54 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request g_request;

t_bool process_request(char *line)
{
  tokenize(&g_request.tokens, line);
  if (!is_valid_syntax())
    return (TRUE);
  parse();
  if (!expand())
    return (TRUE);
  if (!exec_request())
    return (FALSE);
  free_all();
  return (TRUE);
}

t_bool is_valid_request()
{
  if (g_request.cmd_id == INVLD_CMD)
    return (print_err_msg(ERR_MSG_INVLD_CMD));
  if (g_request.option == INVLD_OPT)
    return (print_err_msg(ERR_MSG_INVLD_OPT));
  return (TRUE);
}

void execute_child_process()
{
  t_cmd_func cmd_funcs[CMD_NUM];

  if (g_request.excution)
    execute_executable();
  if (!is_valid_request())
    my_exit(FAILURE);
  init_cmd_funcs(cmd_funcs);
  cmd_funcs[g_request.cmd_id]();
  my_exit(SUCCESS);
}

t_bool exec_request()
{
	t_pipe_list	*pipe_list;
	//   pid_t c_pid;

	pipe_list = create_pipe_list();
	if (!pipe_list)
		return (FALSE);
	execute_cmds(pipe_list);
	free_pipe_list(pipe_list);
//   if (request->cmd_id == EXIT)
//     return (execute_exit(request));
//   c_pid = fork();
//   if (c_pid == -1)
//     print_err_msg(request, strerror(errno));
//   if (c_pid == 0)
//     execute_child_process(request);
//   if (c_pid > 0)
//     wait(NULL);
  return (TRUE);
}

void init_request()
{
  g_request.tokens = NULL;
  g_request.cmds = NULL;
  make_environ_hash();
  g_request.cmd = NULL;
  g_request.cmd_id = INVLD_CMD;
  g_request.option = NON;
  g_request.arguments = NULL;
  g_request.excution = FALSE;
  g_request.exit_cd = 0;
}
