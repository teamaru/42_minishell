/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:29:47 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/18 20:40:53y jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request g_request;

void	exec_path_cmd(t_pipe_list *pipe_list)
{
	const char	**cmd_args;
	char **environs;

	environs = env_list_to_array(g_request.environs);
	cmd_args = pipe_list->cmd_args;
	if (is_path_part((char *)cmd_args[0]))
	{
		if (!search_path((char **)cmd_args))
			print_err_and_exit(ERR_MSG_INVLD_CMD, CMD_NOT_FND);
	}
	if (access(cmd_args[0], X_OK) == -1)
		print_err_and_exit(NULL, DENIED);
	if (execve(cmd_args[0], (char *const *)cmd_args, environs) < 0)
		print_err_and_exit(NULL, GNRL_ERR);
}

void	child_exec_cmd(t_pipe_list *pipe_list)
{
	t_builtin_id builtin_id;

	if (change_multi_references(pipe_list) < 0)
		print_err_and_exit(NULL, GNRL_ERR);
	if (!pipe_list->cmd_args)
		exit(0);
	builtin_id = get_builtin_id(pipe_list->cmd_args[0]);
	if (builtin_id != NON_BUILTIN)
		g_request.builtin_funcs[builtin_id](pipe_list->cmd_args, TRUE);
	else
		exec_path_cmd(pipe_list);
}

void	wait_processes(t_pipe_list *pipe_list)
{
	pid_t		changed_pid;
	t_pipe_list	*tmp_node;
	int			status;

	tmp_node = pipe_list;
	while(tmp_node)
	{
		changed_pid = waitpid(tmp_node->pid, &status, 0);
		g_request.exit_cd = WEXITSTATUS(status);
		if (changed_pid < 0)
		{
			perror("waitpid");
			return;
		}
		tmp_node = tmp_node->next;
	}
}

void	execute_cmds(t_pipe_list *pipe_list)
{
	t_builtin_id builtin_id;

	if (pipe_list->cmd_args)
		builtin_id = get_builtin_id(pipe_list->cmd_args[0]);
	else
		builtin_id = NON_BUILTIN;
	if (!has_pipe(pipe_list) && builtin_id != NON_BUILTIN)
		exec_simple_buitin(pipe_list, builtin_id);
	else if (!has_pipe(pipe_list) && builtin_id == NON_BUILTIN)
		exec_simple_cmd(pipe_list);
	else
	{
		handle_pipelines(pipe_list);
		wait_processes(pipe_list);
	}
}
