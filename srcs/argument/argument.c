/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 19:44:20 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/29 19:44:20 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void free_arguments(t_argument **top)
{
  t_argument	*argument;
	t_argument	*next;

	if (!top)
		return ;
	argument = *top;
	while (argument)
	{
		next = argument->next;
		free(argument->arg);
		free(argument);
		argument = next;
		next = NULL;
	}
	*top = NULL;
}

void parse_arguments(t_request *request, char **line)
{
  char *chunk;

  while (**line)
  {
    clear_white(line);
    chunk = get_chunk(line);
    append_argument(&request->arguments, new_argument(chunk));
    free(chunk);
  }
}
