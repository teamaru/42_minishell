/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 22:06:27 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/06/06 22:06:27 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request g_request;

t_bool is_valid_option(char *option)
{
  return (ft_strlen(option) == 2 && option[1] == N);
}

void parse_option(char **line)
{
  char *option;

  if (g_request.builtin_id != ECHO)
    return ;
  clear_white(line);
  if (**line != HYPHEN)
    return ;
  option = get_chunk(line);
  if (!is_valid_option(option))
    g_request.option = INVLD_OPT;
  else
    g_request.option = N;
  free(option);
}
