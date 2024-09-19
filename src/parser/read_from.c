/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:01:10 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/02 12:11:30 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_on_file(int fd, char *read_line)
{
	if (fd < 0)
	{
		free (read_line);
		return (-1);
	}
	if (write(fd, read_line, ft_strlen(read_line)) == -1)
	{
		free (read_line);
		return (-1);
	}
	free (read_line);
	if (write(fd, "\n", 1) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	read_and_write(char *stop, int cmds_amount, char *f_name)
{
	char	*read_line;
	int		fd;

	while (1)
	{
		read_line = readline("> ");
		if (!read_line)
		{
			handle_error_ctrl_d(stop, cmds_amount);
			return (-1);
		}
		if (!ft_strncmp(read_line, stop, ft_strlen(stop) + 1))
			break ;
		fd = open_fd(f_name, O_WRONLY | O_APPEND | O_CREAT);
		if (write_on_file(fd, read_line) == -1)
			return (-1);
		close(fd);
	}
	free (read_line);
	return (0);
}

int	ft_read_to_file(char *stop, int cmds_amount, char *f_name)
{
	char	new_stop[4096];
	int		fd;

	if (!stop)
		return (-1);
	fd = open_fd(f_name, O_CREAT | O_TRUNC);
	if (fd != -1)
		close(fd);
	ft_bzero(new_stop, 4096);
	ft_strlcpy(new_stop, stop, 4096);
	free (stop);
	if (read_and_write(new_stop, cmds_amount, f_name) == -1)
		return (-1);
	return (0);
}
