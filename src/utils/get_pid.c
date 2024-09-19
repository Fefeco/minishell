/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:36:37 by fcarranz          #+#    #+#             */
/*   Updated: 2024/07/30 12:36:42 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

int	get_pid(void)
{
	int		fd;
	int		pid;
	char	*line;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		handle_error("Error opening /proc/self/stat");
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		handle_error("Error reading from /proc/self/stat");
	}
	pid = ft_atoi(line);
	free (line);
	if (close (fd) < 0)
		handle_error("Error closing /proc/self/stat");
	return (pid);
}
