/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:26:47 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/28 14:05:34 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(t_cmd *parser_nodes)
{
	struct stat	path_stat;

	stat(parser_nodes->full_path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("mini: ", 2);
		ft_putstr_fd(parser_nodes->cmd_array[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (1);
	}
	return (0);
}

size_t	ft_node_len(t_env *envs)
{
	size_t	size;

	size = 0;
	while (envs)
	{
		if (envs->exported)
			++size;
		envs = envs->next;
	}
	return (size);
}

char	**ft_node_to_char(t_env *envs)
{
	size_t	size;
	char	**new_envs;
	char	*env;

	size = ft_node_len(envs);
	new_envs = (char **)malloc(sizeof(char *) * (size + 1));
	new_envs[size] = NULL;
	while (envs)
	{
		if (envs->exported)
		{
			env = ft_strjoin(ft_strdup(envs->key), ft_strdup("="));
			if (envs->value)
				env = ft_strjoin(env, ft_strdup(envs->value));
			*new_envs = env;
			++new_envs;
		}
		envs = envs->next;
	}
	return (new_envs - size);
}

void	ft_close_fds(t_cmd *parser_nodes, int prev_read, int *pipe_fd)
{
	if (parser_nodes->redir_in && parser_nodes->redir_in->fd > 0)
		close(parser_nodes->redir_in->fd);
	if (parser_nodes->redir_out && parser_nodes->redir_out->fd > 0)
		close(parser_nodes->redir_out->fd);
	if (parser_nodes->next)
		close(pipe_fd[WR_END]);
	if (parser_nodes->prev)
		close(prev_read);
}
