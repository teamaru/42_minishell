/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:45:55 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/27 16:59:46 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_H
#define CONVERT_H

#include <mini_shell.h>

typedef enum e_type_rd
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
} t_type_rd;

typedef struct s_redirection_list
{
	int							fd;
	int							type;
	char						*file_path;
	struct s_redirection_list	*next;
} t_redirection_list;

typedef struct s_pipe_list
{
	t_redirection_list			*output_rd;
	t_redirection_list			*input_rd;
	const char					**cmd_args;
	struct s_pipe_list			*next;
	pid_t						pid;
} t_pipe_list;

t_pipe_list	*create_pipe_list(t_request *request);
void		free_pipe_list(t_pipe_list *list);
const char	**create_cmd_args(t_token *args);

#endif
