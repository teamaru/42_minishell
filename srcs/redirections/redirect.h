/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 22:51:46 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/16 21:02:05 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
** open
*/
#include <fcntl.h>

void	redirecting_input(char *file_path);

#endif
