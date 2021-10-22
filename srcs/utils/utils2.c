/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 21:36:24 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/06/06 21:36:24 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_bool is_chunk(char c)
{
  return (c && !is_white(c));
}

t_bool is_quote(char c)
{
  return (c == SGL_QT || c == DBL_QT);
}

t_bool is_end(char *line)
{
  clear_white(&line);
  if (!*line)
    return (TRUE);
  return (FALSE);
}

t_bool	is_path_part(char *path)
{
	return (*path != PERIOD && *path != SLSH);
}
