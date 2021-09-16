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

#include "../../includes/mini_shell.h"

t_bool is_valid_option(char *option)
{
  return (ft_strlen(option) == 2 && option[1] == N);
}

void parse_option(t_request *request, char **line)
{
  char *option;

  if (request->cmd_id != ECHO)
    return ;
  clear_white(line);
  if (**line != HYPHEN)
    return ;
  option = get_chunk(line);
  if (!is_valid_option(option))
    request->option = INVLD_OPT;
  else
    request->option = N;
  free(option);
}
