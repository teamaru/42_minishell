/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 13:05:15 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 22:11:53 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "./libft.h"

static int	find_line(char **line, char **memory)
{
	int		new_line;

	new_line = ft_strchr_i(*memory, '\n');
	if (new_line >= 0)
	{
		free(*line);
		*line = ft_strndup(*memory, new_line);
		if (!*line)
			return (-1);
		return (add_memory(memory, *memory + new_line + 1, NULL));
	}
	return (0);
}

int	check_file(char **line, char **memory, int fd, int flg)
{
	ssize_t		bc;
	char		*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	bc = 0;
	if (!flg)
		bc = read(fd, buf, BUFFER_SIZE);
	while (!flg && bc > 0)
	{
		buf[bc] = '\0';
		if (!add_memory(memory, *memory, buf))
			return (-1);
		flg = find_line(line, memory);
		if (!flg)
			bc = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (bc < 0)
		return (-1);
	return (flg);
}

static int	read_file(char **line, char **memory, int fd)
{
	int			flg;

	flg = 0;
	if (*memory)
		flg = find_line(line, memory);
	flg = check_file(line, memory, fd, flg);
	return (flg);
}

int	get_next_line(int fd, char **line)
{
	int			flg;
	static char	*memory[MAX_FD];

	if (!line || fd < 0 || fd > MAX_FD)
		return (-1);
	*line = malloc(1);
	if (!*line)
		return (-1);
	*line[0] = 0;
	flg = read_file(line, &memory[fd], fd);
	if (memory[fd] && flg == 0)
	{
		free(*line);
		*line = ft_strjoin(NULL, memory[fd]);
		if (!*line)
			flg = -1;
		renew_memory(&memory[fd], NULL);
	}
	if (flg == -1)
		renew_memory(&memory[fd], NULL);
	return (flg);
}
