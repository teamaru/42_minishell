/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:51:50 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/29 15:51:50 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_bool print_err_msg(char *msg)
{
  printf(MSG_HEADER);
  printf("%s", msg);
  return (FALSE);
}

void my_exit(int exit_cd)
{
  free_all();
  exit(exit_cd);
}
