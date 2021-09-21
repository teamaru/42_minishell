/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:49:34 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/29 15:49:34 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_bool	is_white(int c)
{
	return (c == ' ' || ('\t' <= c && c <= '\r'));
}

void	clear_char(char **line, int c)
{
	while (**line == c)
		(*line)++;
}

void clear_white(char **line)
{
  while (is_white(**line))
    (*line)++;
}

void multi_free(char **target)
{
	int i;

	i = -1;
	while (target[++i])
		free(target[i]);
	free(target);
}

void free_all(t_request *request)
{
	free_arguments(&request->arguments);
	free_tokens(&request->tokens);
  free_cmd_list(&request->cmds);
	free(request->cmd);
}
