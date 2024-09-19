/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:04:36 by davifer2          #+#    #+#             */
/*   Updated: 2024/09/02 13:14:42 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file(t_redir *node)
{
	if (!node->filename)
		return (1);
	if (access(node->filename, F_OK | R_OK))
	{
		ft_putstr_fd("mini: ", 2);
		perror(node->filename);
		return (1);
	}
	return (0);
}

void	*hdoc_error_handler(t_redir *redir_node, t_cmd *parser_nodes)
{
	unlink(redir_node->filename);
	free(redir_node->filename);
	free(redir_node);
	if (g_signal == 1)
		parser_nodes->error_fd = 1;
	return (NULL);
}

t_redir	*hdoc_redir(t_tokens **lexer_nodes, t_cmd *parser_nodes, t_utils *utils)
{
	t_redir	*redir_node;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (parser_nodes && parser_nodes->error_fd)
		return (NULL);
	redir_node = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_node)
		return (NULL);
	redir_node->here_doc = 1;
	redir_node->filename = ft_random_filename();
	if (ft_fork_hdoc(lexer_nodes, parser_nodes, redir_node, utils) || g_signal)
		return (hdoc_error_handler(redir_node, parser_nodes));
	redir_node->fd = open_fd(redir_node->filename, O_RDONLY);
	if (redir_node->fd < 0)
		return (exit_redir(1, redir_node, utils));
	return (redir_node);
}

t_redir	*append_gthan_redir(char *file_name, int token, t_utils *utils,
	t_cmd *parser_nodes)
{
	t_redir	*redir_node;
	int		mode;

	if (parser_nodes && parser_nodes->error_fd)
		return (NULL);
	redir_node = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_node)
		return (NULL);
	redir_node->here_doc = 0;
	redir_node->filename = ft_strdup(file_name);
	if (!redir_node->filename)
		return (exit_redir(3, redir_node, NULL));
	mode = (O_WRONLY | O_CREAT);
	if (token == APPEND)
		redir_node->fd = open_fd(redir_node->filename, mode | O_APPEND);
	else
		redir_node->fd = open_fd(redir_node->filename, mode | O_TRUNC);
	if (redir_node->fd < 0)
		return (exit_redir(1, redir_node, utils));
	return (redir_node);
}

t_redir	*sthan_redir(char *file_name, t_utils *utils, t_cmd *parser_nodes)
{
	t_redir	*redir_node;

	if (parser_nodes && parser_nodes->error_fd)
		return (NULL);
	redir_node = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_node)
		return (NULL);
	redir_node->here_doc = 0;
	redir_node->filename = ft_strdup(file_name);
	redir_node->fd = -1;
	if (!redir_node->filename)
		return (exit_redir(3, redir_node, utils));
	if (check_file(redir_node))
		parser_nodes->error_fd = 1;
	else
		redir_node->fd = open_fd(redir_node->filename, O_RDONLY);
	return (redir_node);
}
