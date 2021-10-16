/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:29:47 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/12 14:31:37 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request g_request;

void replace_path(char **cmd, char *path)
{
	free(cmd[0]);
	cmd[0] = ft_strdup(path);
}

t_bool search_path(char **cmd)
{
  t_environ *path;
  char **paths;
  int i;

  path = get_target_environ("PATH");
  paths = ft_split(path->value, ':');
  i = -1;
  while (paths[++i])
  {
    paths[i] = add_slash(paths[i]);
    paths[i] = join_path(paths[i], cmd[0]);
		if (access(paths[i], 0) == -1)
			continue;
		replace_path(cmd, paths[i]);
		multi_free(paths);
		return (TRUE);
  }
  multi_free(paths);
	return (FALSE);
}

int env_listsize(t_environ *environs)
{
  int size;
  t_environ *environ;

  environ = environs;
  size = 0;
  while (environ)
  {
    size++;
    environ = environ->next;
  }
  return (size);
}

char *join_env(t_environ *environ)
{
	char *env;
	char *tmp;

	tmp = ft_strjoin(environ->key, "=");
	env = ft_strjoin(tmp, environ->value);
	free(tmp);
	return (env);
}

char **env_list_to_array(t_environ *environs)
{
  int i;
  char **array;
  t_environ *environ;

  array = malloc(sizeof(char*) * (env_listsize(environs) + 1));
  if (!array)
    return (NULL);
  environ = environs;
  i = -1;
  while (environ)
  {
		array[++i] = join_env(environ);
    environ = environ->next;
  }
  array[i + 1] = NULL;
  return (array);
}

static void	child_exec_cmd(t_pipe_list *pipe_list)
{
	const char	**cmd_args;
	/* 環境変数追加 */
	char **environs;

	//t_redirection_listがあれば参照先変更
	if (change_multi_references(pipe_list) < 0)
	{
		perror("in change_multi_references");
		exit(1);
	}
	environs = env_list_to_array(g_request.environs);
	cmd_args = pipe_list->cmd_args;
	if (!search_path((char **)cmd_args))
	{
		perror("execve");
		exit(CMD_NOT_FND);
	}
	if (execve(cmd_args[0], (char *const *)cmd_args, environs) < 0)
	{
		perror("execve");
		exit(GNRL_ERR);
	}
}

t_bool	has_pipe(t_pipe_list *pipe_list)
{
	if (pipe_list->next)
		return (TRUE);
	return (FALSE);
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

void	exec_buildin(t_pipe_list *pipe_list, t_builtin_id builtin_id)
{
	t_builtin_func builtin_funcs[BUILTIN_NUM];

	init_builtin_funcs(builtin_funcs);
  builtin_funcs[builtin_id](pipe_list->cmd_args, FALSE);
}

t_bool	has_heredoc(t_heredoc_to_fd *heredoc)
{
	if (heredoc)
		return (TRUE);
	else
		return (FALSE);
}

int	heredoc_to_fd(char *heredoc)
{
	int	tmp_file_fd;

	tmp_file_fd = open(TMPFILE, O_RDWR | O_CREAT | O_EXCL, 0666);
	if (tmp_file_fd < 0)
		return (-1);
	if (write(tmp_file_fd, heredoc, ft_strlen(heredoc)) < 0)
	{
		close(tmp_file_fd);
		unlink(TMPFILE);
		return (-1);
	}
	return (tmp_file_fd);
}

t_result write_heredoc(t_heredoc_to_fd *heredoc)
{
	if (!has_heredoc(heredoc))
		return (SUCCESS);
	heredoc->tmp_fd = heredoc_to_fd(heredoc->contents);
	if (heredoc->tmp_fd < 0)
		return (FAILURE);
	else
		return (SUCCESS);
}

void	exec_simple_cmd(t_pipe_list *pipe_list)
{
	pid_t	changed_pid;
	int		status;

	if (write_heredoc(pipe_list->heredoc) == FAILURE)
		return ;
	pipe_list->pid = fork();
	if (pipe_list->pid == -1)
	{
		perror("fork");
		if (has_heredoc(pipe_list->heredoc))
		{
			close(pipe_list->heredoc->tmp_fd);
			unlink(TMPFILE);
		}
		return ;
	}
	else if (pipe_list->pid == 0)
		child_exec_cmd(pipe_list);
	else
	{
		if (has_heredoc(pipe_list->heredoc))
			close(pipe_list->heredoc->tmp_fd);
		changed_pid = waitpid(pipe_list->pid, &status, 0);
		g_request.exit_cd = WEXITSTATUS(status);
		if (changed_pid == -1)
			perror("waitpid");
	}
}

void	init_pipe_fd(int pipe_fd[2])
{
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
}

t_bool	is_pipe_open(int pipe_fd[2])
{
	if (pipe_fd[0] == -1 && pipe_fd[1] == -1)
		return (FALSE);
	return (TRUE);
}

void	read_pipe(int pipe_fd[2])
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
}

void	write_pipe(int pipe_fd[2])
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
}

void	child_operate_pipe_fd(t_pipe_list *first, t_pipe_list *node, int last_pipe_fd[2], int new_pipe_fd[2])
{
	if (!has_pipe(node))
		read_pipe(last_pipe_fd);
	else if (first == node)
		write_pipe(new_pipe_fd);
	else
	{
		read_pipe(last_pipe_fd);
		write_pipe(new_pipe_fd);
	}
}

void	parent_operate_pipe_fd(t_pipe_list *node, int last_pipe_fd[2], int new_pipe_fd[2])
{
	if (is_pipe_open(last_pipe_fd))
	{
		close(last_pipe_fd[0]);
		close(last_pipe_fd[1]);
	}
	if (has_pipe(node))
	{
		last_pipe_fd[0] = new_pipe_fd[0];
		last_pipe_fd[1] = new_pipe_fd[1];
	}
}

pid_t do_pipe(t_pipe_list *first, t_pipe_list *node, int last_pipe_fd[2])
{
	int	new_pipe_fd[2];
	pid_t	child_pid;

	if (has_pipe(node))
	{
		if (pipe(new_pipe_fd) < 0)
			return (-1);
	}
	if (write_heredoc(node->heredoc) == FAILURE)
		return (-1);
	child_pid = fork();
	if (child_pid < 0)
	{
		if (has_heredoc(node->heredoc))
		{
			close(node->heredoc->tmp_fd);
			unlink(TMPFILE);
		}
		return (child_pid);
	}
	/* 子プロセスで実行 */
	if (child_pid == 0)
	{
		child_operate_pipe_fd(first, node, last_pipe_fd, new_pipe_fd);
		child_exec_cmd(node);
	}
	/* 親プロセスで実行 */
	else
	{
		if (has_heredoc(node->heredoc))
			close(node->heredoc->tmp_fd);
		parent_operate_pipe_fd(node, last_pipe_fd, new_pipe_fd);
	}
	return (child_pid);
}

void	handle_pipelines(t_pipe_list *pipe_list)
{
	t_pipe_list	*tmp_node;
	int			last_pipe_fd[2];
	pid_t		child_pid;

	tmp_node = pipe_list;
	init_pipe_fd(last_pipe_fd);
	while (tmp_node)
	{

		child_pid = do_pipe(pipe_list, tmp_node, last_pipe_fd);
		if (child_pid < 0)
		{
			perror("do_pipe");
			return;
		}
		tmp_node->pid = child_pid;
		tmp_node = tmp_node->next;
	}
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

	if (!has_pipe(pipe_list))
	{
		/* buildinを親プロセスで実行 */
		if (!pipe_list->cmd_args[0])
			return ;
		builtin_id = get_builtin_id(pipe_list->cmd_args[0]);
		if (builtin_id != NON_BUILTIN)
			g_request.builtin_funcs[builtin_id](pipe_list->cmd_args, FALSE);
		/* buildin以外は子プロセスで実行 */
		else
			exec_simple_cmd(pipe_list);
	}
	else
	{
		handle_pipelines(pipe_list);
		wait_processes(pipe_list);
	}
}
