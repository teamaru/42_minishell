/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:26:12 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/25 20:26:12 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char *delete_qt()
{
  return (NULL);
}

char *extract_string(char **line)
{
  int i;
  char *chunk;
  char qt;

  qt = **line;
  (*line)++;
  i = 1;
  while ((*line)[i] != qt)
    i++;
  chunk = ft_strndup(*line, i++);
  *line += i;
  return (chunk);
}

char *extract_chunk(char **line)
{
  int i;
  char *chunk;

  i = 0;
  while (is_chunk((*line)[i]))
    i++;
  chunk = ft_strndup(*line, i);
  *line += i;
  return (chunk);
}

char *get_chunk(char **line)
{
  char *chunk;

  if (is_qt(**line))
    chunk = extract_string(line);
  else
    chunk = extract_chunk(line);
  return (chunk);
}

void shell_loop(t_request *request)
{
  char *line;
  t_bool flg;

  flg = TRUE;
  while (flg)
  {
    line = readline(PRMPT);
    if (ft_strlen(line) > 0)
      add_history(line);
    flg = process_request(request, line);
    free(line);
  }
}

int main()
{
  t_request request;

  shell_loop(&request);
  return (request.exit_cd);
}
