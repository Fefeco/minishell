/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 10:16:30 by davifer2          #+#    #+#             */
/*   Updated: 2024/08/28 13:40:41 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

char	*read_file_username(char *path_file)
{
	int		fd;
	int		bytes_read;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * 4096);
	if (!buffer)
		return (NULL);
	fd = open(path_file, O_RDONLY);
	if (fd == -1)
	{
		free(buffer);
		return (NULL);
	}
	bytes_read = read(fd, buffer, 4096);
	if (bytes_read == -1)
	{
		close(fd);
		free(buffer);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	close(fd);
	return (buffer);
}

char	*read_file_for_uid(int fd, char *uid, char *tmp)
{
	int		bytes_read;
	char	buffer[4096];
	char	*line;

	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read == -1)
		return (NULL);
	buffer[bytes_read] = '\0';
	line = ft_strnstr(buffer, "Uid:", bytes_read);
	if (line)
	{
		line += 4;
		while (*line == '\t' || *line == ' ')
			line++;
		while (*line >= '0' && *line <= '9')
			*uid++ = *line++;
		*uid = '\0';
	}
	return (tmp);
}

char	*find_username(char **lines, char *uid_str, int option)
{
	char	*username;
	int		i;

	i = 1;
	username = NULL;
	while (*lines)
	{
		if (option == 1)
			username = ft_search_passwd(*lines, uid_str);
		else if (option == 2)
			username = ft_search_mount(*lines);
		if (username)
			break ;
		lines++;
		++i;
	}
	return (username);
}

void	get_short_path(char *short_pathname, char *cwd, t_utils *utils)
{
	get_homedir(utils);
	if (ft_strncmp(cwd, utils->homedir, ft_strlen(utils->homedir)) == 0)
	{
		ft_strlcpy(short_pathname, "~", PATH_MAX);
		ft_strlcat(short_pathname, cwd + ft_strlen(utils->homedir), PATH_MAX);
	}
	else
		ft_strlcpy(short_pathname, cwd, PATH_MAX);
}
