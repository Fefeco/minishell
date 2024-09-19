/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:16:30 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/30 21:52:35 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_hostname(void)
{
	char	*hostname;
	char	*newline_pos;
	int		fd;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (NULL);
	hostname = get_next_line(fd);
	close(fd);
	if (hostname)
	{
		newline_pos = ft_strchr(hostname, '\n');
		if (newline_pos)
			*newline_pos = '\0';
	}
	return (hostname);
}

char	*search_username(char *uid_str, char *path_file, int option)
{
	char	*tmp;
	char	**lines;
	char	*username;

	if (option == 2)
		ft_call_child(path_file);
	tmp = read_file_username(path_file);
	if (!tmp)
		return (NULL);
	lines = ft_split(tmp, '\n');
	if (!lines)
	{
		free(tmp);
		return (NULL);
	}
	username = find_username(lines, uid_str, option);
	free_split(lines);
	free(tmp);
	return (username);
}

static char	*ft_get_uid(void)
{
	int		fd;
	char	*uid;
	char	*tmp;

	uid = (char *)malloc(sizeof(char) * 16);
	if (!uid)
		return (NULL);
	tmp = uid;
	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
	{
		free(uid);
		return (NULL);
	}
	tmp = read_file_for_uid(fd, uid, tmp);
	close(fd);
	if (tmp)
		return (uid);
	return (NULL);
}

char	*get_username(void)
{
	char	*uid_str;
	char	*username;

	username = NULL;
	uid_str = ft_get_uid();
	if (uid_str)
	{
		username = search_username(uid_str, "/etc/passwd", 1);
		if (!username)
		{
			username = search_username(uid_str, "/tmp/file-tmp", 2);
			unlink("/tmp/file-tmp");
			if (!username)
			{
				ft_putstr_fd("Can't obtain username.\n", 2);
				free(uid_str);
				return (username);
			}
		}
	}
	else
		return (NULL);
	free(uid_str);
	return (username);
}

void	get_user_and_hostname(char *info_machine, t_env *envs)
{
	char	*user;
	char	*hostname;
	t_env	*node;

	node = ft_get_env_from_list(envs, "USER");
	if (node && node->value)
		user = ft_strdup(node->value);
	else
		user = get_username();
	if (!user)
		user = ft_strdup("guest");
	hostname = get_hostname();
	if (hostname)
	{
		ft_strlcpy(info_machine, user, PATH_MAX);
		ft_strlcat(info_machine, "@", PATH_MAX);
		ft_strlcat(info_machine, hostname, PATH_MAX);
		free(hostname);
	}
	free(user);
}
