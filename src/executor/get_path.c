/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:16:17 by fcarranz          #+#    #+#             */
/*   Updated: 2024/05/06 11:50:27 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_array(void **array)
{
	int	i;

	i = 0;
	while (array[i])
		free (array[i++]);
	free (array);
}

static char	*ft_get_path(char *path, char *cmd)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!path || !cmd || !ft_strlen(cmd))
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(ft_strdup(paths[i]), ft_strdup("/"));
		full_path = ft_strjoin(full_path, ft_strdup(cmd));
		if (access(full_path, F_OK | X_OK) == 0)
			break ;
		free (full_path);
		full_path = NULL;
		++i;
	}
	ft_free_array((void *)paths);
	return (full_path);
}

void	ft_search_path(t_cmd *parser_nodes, t_utils *utils)
{
	char	*cmd;
	t_env	*path;

	path = ft_get_env_from_list(utils->envs, "PATH");
	while (parser_nodes)
	{
		if (!(parser_nodes->cmd_array && parser_nodes->cmd_array[0]))
			parser_nodes->full_path = NULL;
		else if (ft_is_builtin(parser_nodes, utils)
			|| ft_strchr(parser_nodes->cmd_array[0], '/'))
			parser_nodes->full_path = ft_strdup(parser_nodes->cmd_array[0]);
		else if (path)
		{
			cmd = ft_get_path(path->value, parser_nodes->cmd_array[0]);
			parser_nodes->full_path = cmd;
		}
		else
			parser_nodes->full_path = NULL;
		parser_nodes = parser_nodes->next;
	}
}
