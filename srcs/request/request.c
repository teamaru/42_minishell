/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:45:50 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/12 14:44:33 by jnakahod         ###   ########.fr       */
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
  if (!request_convert_to_pipe_list())
    return (TRUE);
  return (TRUE);
}

t_bool	request_convert_to_pipe_list()
{
	t_pipe_list	*pipe_list;

	pipe_list = create_pipe_list();
	if (!pipe_list)
		return (FALSE);
	execute_cmds(pipe_list);
	free_pipe_list(pipe_list);
  return (TRUE);
}

void init_request()
{
  g_request.tokens = NULL;
  g_request.cmds = NULL;
  g_request.builtin_id = NON_BUILTIN;
  init_builtin_funcs();
  g_request.excution = FALSE;
  g_request.pid = 0;
}
