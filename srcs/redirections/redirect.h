/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 22:51:46 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/22 23:47:30 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../../libft/includes/libft.h"

typedef enum e_type_rd
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
}	t_type_rd;

typedef struct s_redirection_list
{
	int							fd;
	int							type;
	char						*file_path;
	struct s_redirection_list	*next;
}	t_redirection_list;

typedef struct s_command
{
	t_redirection_list	*output_rd;
	t_redirection_list	*input_rd;
}	t_command;

/*
** open
*/
#include <fcntl.h>

void	redirecting_input(char *file_path);
void	redirecting_output(char *file_path);
void	redirecting_append(char *file_path);
int		create_t_redirection_list(char *rd_str, t_command *cmd);

#endif
