/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 19:44:28 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/29 19:44:28 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_argument	*new_argument(char *arg)
{
	t_argument	*new;

	new = malloc(sizeof(t_argument));
	if (!new)
		return (NULL);
	new->arg = ft_strdup(arg);
	new->next = NULL;
	return (new);
}

int listsize(t_argument *arguments)
{
  int size;
  t_argument *argument;

  argument = arguments;
  size = 0;
  while (argument)
  {
    size++;
    argument = argument->next;
  }
  return (size);
}

char **list_to_array(t_argument *arguments)
{
  int i;
  char **array;
  t_argument *argument;

  array = malloc(sizeof(char*) * (listsize(arguments) + 1));
  if (!array)
    return (NULL);
  argument = arguments;
  i = -1;
  while (argument)
  {
    array[++i] = ft_strdup(argument->arg);
    argument = argument->next;
  }
  array[i + 1] = NULL;
  return (array);
}

void	append_argument(t_argument **top, t_argument *new)
{
	t_argument	*argument;

	if (!top || !new)
		return ;
	if (!*top)
	{
		*top = new;
		return ;
	}
	argument = *top;
	while (argument && argument->next)
		argument = argument->next;
	argument->next = new;
}
