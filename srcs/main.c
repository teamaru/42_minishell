/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:26:12 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/22 23:13:03 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_request	g_request;

void	shell_loop(void)
{
	char	*line;
	t_bool	flg;

	flg = TRUE;
	make_environ_hash();
	g_request.exit_cd = SCCSS;
	while (flg)
	{
		line = readline(PRMPT);
		if (!line)
			my_exit(SCCSS);
		if (ft_strlen(line) > 0)
			add_history(line);
		init_request();
		flg = process_request(line);
		free_all(FALSE);
		free(line);
	}
}

int	main(void)
{
	init_signal();
	shell_loop();
	return (g_request.exit_cd);
}
