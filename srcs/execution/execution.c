/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:48:24 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/06/08 14:48:24 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request g_request;

t_bool is_execution(char **line)
{
  if (**line == PERIOD || **line == SLSH)
  {
    g_request.excution = TRUE;
    return (TRUE);
  }
  return (FALSE);
}
