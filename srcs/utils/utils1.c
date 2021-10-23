/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:49:34 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/19 22:51:59 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

t_bool	is_white(int c)
{
	return (c == ' ' || ('\t' <= c && c <= '\r'));
}

void	clear_char(char **line, int c)
{
	while (**line == c)
		(*line)++;
}

void	clear_white(char **line)
{
	while (is_white(**line))
		(*line)++;
}

void	multi_free(char **target)
{
	int	i;

	i = -1;
	while (target[++i])
		free(target[i]);
	free(target);
}

void	free_all(t_bool is_exit)
{
	free_tokens(&g_request.tokens);
	free_cmd_list(&g_request.cmds);
	if (is_exit)
	  free_environs(&g_request.environs);
}
