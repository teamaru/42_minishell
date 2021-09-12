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

#include "../../includes/mini_shell.h"

t_bool is_chunk(char c)
{
  return (c && !is_white(c));
}

t_bool is_sgl_qt(char c)
{
  return (c == DBL_QT);
}

t_bool is_dbl_qt(char c)
{
  return (c == DBL_QT);
}

t_bool is_qt(char c)
{
  return (is_sgl_qt(c) || is_dbl_qt(c));
}

t_bool is_end(char *line)
{
  clear_white(&line);
  if (!*line)
    return (TRUE);
  return (FALSE);
}
