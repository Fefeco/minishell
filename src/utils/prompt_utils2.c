/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils2.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:57:30 by davifer2          #+#    #+#             */
/*   Updated: 2024/08/19 20:00:15 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_call_child(char *path_file)
{
	pid_t	pid;
	char	*args[4];
	int		fd;

	args[0] = "/usr/bin/tail";
	args[1] = "-n30";
	args[2] = "/proc/self/mounts";
	args[3] = NULL;
	pid = fork();
	if (pid == 0)
	{
		fd = open(path_file, O_CREAT | O_WRONLY, 0664);
		dup2(fd, STDOUT_FILENO);
		close (fd);
		execve(args[0], args, NULL);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
}

char	*ft_search_passwd(char *line, char *uid_str)
{
	char	**fields;
	char	*username;

	username = NULL;
	fields = ft_split(line, ':');
	if (fields && ft_strncmp(fields[2], uid_str, sizeof(uid_str)) == 0)
		username = ft_strdup(fields[0]);
	free_split(fields);
	return (username);
}

char	*ft_search_mount(char *line)
{
	char	**fields;
	char	**tmp;
	char	*username;

	username = NULL;
	if (!ft_strnstr(line, "/home", ft_strlen(line)))
		return (username);
	fields = ft_split(line, ' ');
	if (fields)
	{
		tmp = fields;
		while (!ft_strnstr(*tmp, "/home", ft_strlen(line)))
			++tmp;
		username = ft_substr(*tmp, 6, (ft_strlen(*tmp) - 5));
	}
	free_split(fields);
	return (username);
}
