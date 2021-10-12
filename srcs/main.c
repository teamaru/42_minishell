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

#include <mini_shell.h>

t_request g_request;

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
  i = 1;
  while ((*line)[i] != qt)
    i++;
  chunk = ft_strndup(*line, ++i);
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

  if (is_quote(**line))
    chunk = extract_string(line);
  else
    chunk = extract_chunk(line);
  return (chunk);
}

void shell_loop()
{
  char *line;
  t_bool flg;

  flg = TRUE;
  make_environ_hash();
  while (flg)
  {
    line = readline(PRMPT);
    if (!line)
      my_exit(0);
    if (ft_strlen(line) > 0)
      add_history(line);
    init_request();
    flg = process_request(line);
    free_all(FALSE);
    free(line);
  }
}

int main()
{
  init_signal();
  shell_loop();
  return (g_request.exit_cd);
}
