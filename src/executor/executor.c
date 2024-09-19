/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:16:35 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/02 12:46:09 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fork(t_cmd *parser_nodes, int prev_read, int *pipe_fd, t_env *envs)
{
	int		pid;
	char	**new_envs;

	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		set_signals(INTERACTIVE);
		new_envs = ft_node_to_char(envs);
		ft_dup_fds(parser_nodes, prev_read, pipe_fd);
		pid = 3;
		while (pid < 100)
			close(pid++);
		execve(parser_nodes->full_path, parser_nodes->cmd_array, new_envs);
		exit(EXIT_FAILURE);
	}
	return (1);
}

int	ft_check_process(t_cmd *parser_nodes, t_utils *utils)
{
	if (!parser_nodes->full_path)
	{
		write_error_fd(parser_nodes->cmd_array[0], ": command not found\n", 2);
		utils->exit_status = 127;
		return (1);
	}
	else if (access(parser_nodes->full_path, F_OK) == 0
		&& is_directory(parser_nodes))
	{
		utils->exit_status = 126;
		return (1);
	}
	if (!ft_is_builtin(parser_nodes, utils)
		&& access(parser_nodes->full_path, F_OK))
	{
		write_error_fd(parser_nodes->cmd_array[0],
			": No such file or directory\n", 2);
		utils->exit_status = 127;
		return (1);
	}
	if (parser_nodes->redir_in && parser_nodes->redir_in->fd == -1)
		return (1);
	if (parser_nodes->redir_out && isatty(parser_nodes->redir_out->fd))
		parser_nodes->redir_out = exit_redir(2, parser_nodes->redir_out, utils);
	return (0);
}

void	ft_wait_for_childs(int i, int *exit_status)
{
	int	exit;

	exit = 0;
	while (i-- > 0)
	{
		wait(&exit);
		if (WIFSIGNALED(exit))
		{
			*exit_status = 128 + WTERMSIG(exit);
			if (WTERMSIG(exit) == SIGQUIT)
				ft_putstr_fd("Quit (core dumped)\n", 2);
			else if (WTERMSIG(exit) == SIGINT)
			{
				g_signal = 1;
				ft_putstr_fd("\n", 2);
			}
		}
		else if (WIFEXITED(exit))
		{
			*exit_status = WEXITSTATUS(exit);
		}
	}
}

void	close_fd_and_swap_pipe(t_cmd *parser_nodes, int *prev_read,
		int *pipe_fd)
{
	ft_close_fds(parser_nodes, *prev_read, pipe_fd);
	if (parser_nodes && parser_nodes->next)
		*prev_read = pipe_fd[RD_END];
}

void	ft_executor(t_cmd *parser_nodes, t_utils *utils)
{
	int		i;
	int		pipe_fd[2];
	int		prev_read;

	prev_read = -1;
	i = 0;
	signal(SIGINT, SIG_IGN);
	while (parser_nodes && utils->status)
	{
		if (parser_nodes->next && pipe(pipe_fd) == -1)
			return ;
		if (parser_nodes->cmd_array && parser_nodes->cmd_array[0])
		{
			if (!ft_check_process(parser_nodes, utils))
			{
				if (ft_is_builtin(parser_nodes, utils))
					ft_exec_builtin(parser_nodes, utils, pipe_fd[WR_END]);
				else
					i += ft_fork(parser_nodes, prev_read, pipe_fd, utils->envs);
			}
		}
		close_fd_and_swap_pipe(parser_nodes, &prev_read, pipe_fd);
		parser_nodes = parser_nodes->next;
	}
	ft_wait_for_childs(i, &utils->exit_status);
}
