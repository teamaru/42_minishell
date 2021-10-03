/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:29:47 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/03 23:12:41 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static void	child_exec_cmd(t_pipe_list *pipe_list)
{
	const char	**cmd_args;

	//t_redirection_listがあれば参照先変更
	if (change_multi_references(pipe_list) < 0)
	{
		perror("in change_multi_references");
		exit(1);
	}
	cmd_args = pipe_list->cmd_args;
	if (execve(cmd_args[0], (char *const *)cmd_args, NULL) < 0)
	{
		perror("execve");
		exit(1);
	}
}

t_bool	is_pipe(t_pipe_list *pipe_list)
{
	if (!pipe_list->next)
		return (FALSE);
	return (TRUE);
}

t_bool	is_buildin(const char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6)
		|| !ft_strncmp(cmd, "env", 3)
		|| !ft_strncmp(cmd, "exit", 5))
		return (TRUE);
	return (FALSE);
}

void	exec_buildin(t_pipe_list *pipe_list)
{
	(void)pipe_list;
	printf("exec_buildin\n");
}

void	exec_simple_cmd(t_pipe_list *pipe_list)
{
	pid_t	changed_pid;
	int		status;

	pipe_list->pid = fork();
	if (pipe_list->pid == -1)
		perror("fork");
	else if (pipe_list->pid == 0)
		child_exec_cmd(pipe_list);
	else
	{
		changed_pid = waitpid(pipe_list->pid, &status, 0);
		if (changed_pid == -1)
			perror("waitpid");
	}
}

void	execution_part(t_pipe_list *pipe_list)
{
	if (!is_pipe(pipe_list))
	{
		/* buildinを親プロセスで実行 */
		if (is_buildin(pipe_list->cmd_args[0]))
			exec_buildin(pipe_list);
		/* buildin以外は子プロセスで実行 */
		else
			exec_simple_cmd(pipe_list);
	}
}
