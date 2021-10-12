/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:21:49 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/07 17:46:55 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../../libft/includes/libft.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

typedef enum e_bool
{
  FALSE,
  TRUE,
} t_bool;

typedef enum e_result
{
  SUCCESS,
  FAILURE,
} t_result;

#endif
