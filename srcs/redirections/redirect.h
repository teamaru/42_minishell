/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 22:51:46 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/26 14:09:38 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
#define REDIRECT_H

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
} t_type_rd;

typedef struct s_redirection_list
{
	int fd;
	int type;
	char *file_path;
	struct s_redirection_list *next;
} t_redirection_list;

typedef struct s_complete_cmd
{
	t_redirection_list *output_rd;
	t_redirection_list *input_rd;
} t_complete_cmd;

/*
** open
*/
#include <fcntl.h>

int create_t_redirection_list(char *rd_str, t_complete_cmd *cmd);

/*
** change_reference.
*/
int change_multi_references(t_complete_cmd *cmd);

/*
** utils.c
*/
void free_set(void **dst, void *src);

/*
** execution.c
*/
void exec_command(char *command);

/*
** test.c
*/
void test_print_t_complete_cmd(t_complete_cmd *cmd);

#endif
