/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:05:49 by davifer2          #+#    #+#             */
/*   Updated: 2024/08/28 14:05:59 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_and_close(int fd_from, int fd_to)
{
	dup2(fd_from, fd_to);
	close (fd_from);
}

void	ft_dup_fds(t_cmd *parser_nodes, int prev_read, int *pipe_fd)
{
	if (parser_nodes->prev)
		dup_and_close(prev_read, STDIN_FILENO);
	if (parser_nodes->redir_in)
		dup_and_close(parser_nodes->redir_in->fd, STDIN_FILENO);
	if (parser_nodes->next)
		dup_and_close(pipe_fd[WR_END], STDOUT_FILENO);
	if (parser_nodes->redir_out)
		dup_and_close(parser_nodes->redir_out->fd, STDOUT_FILENO);
}
