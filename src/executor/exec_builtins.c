/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:41:25 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/03 12:41:27 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_builtin(t_cmd *parser_nodes, t_utils *utils, int pipe)
{
	if (parser_nodes->next)
		exec_builtins(parser_nodes, utils, pipe);
	else
		exec_builtins(parser_nodes, utils, 1);
}

int	ft_is_builtin(t_cmd *parser_nodes, t_utils *utils)
{
	int	i;

	i = 0;
	while (utils->builtins[i])
	{
		if (!ft_strncmp(parser_nodes->cmd_array[0],
				utils->builtins[i], ft_strlen(utils->builtins[i]) + 1))
			return (1);
		++i;
	}
	return (0);
}

void	exec_builtins(t_cmd *parser_nodes, t_utils *utils, int fd)
{
	if (parser_nodes->redir_out)
		fd = parser_nodes->redir_out->fd;
	if (!ft_strncmp("pwd", parser_nodes->cmd_array[0], 4))
		utils->exit_status = ft_pwd(utils->envs);
	else if (!ft_strncmp("cd", parser_nodes->cmd_array[0], 3))
		utils->exit_status = ft_cd(utils, parser_nodes);
	else if (!ft_strncmp("env", parser_nodes->cmd_array[0], 4))
		utils->exit_status = ft_env(utils->envs, fd);
	else if (!ft_strncmp("export", parser_nodes->cmd_array[0], 7))
		utils->exit_status = ft_export(&utils->envs,
				parser_nodes->cmd_array + 1, fd);
	else if (!ft_strncmp("unset", parser_nodes->cmd_array[0], 6))
		ft_unset(&utils->envs, parser_nodes->cmd_array + 1);
	else if (!ft_strncmp("echo", parser_nodes->cmd_array[0], 5))
		utils->exit_status = ft_echo(parser_nodes->cmd_array, fd);
	else if (!ft_strncmp("exit", parser_nodes->cmd_array[0], 5))
		utils->exit_status = ft_exit(parser_nodes->cmd_array, fd, utils);
}
