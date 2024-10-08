/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>        +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:28:45 by davifer2           #+#    #+#            */
/*   Updated: 2024/07/07 14:29:28 by davifer2          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_line(char **line, t_utils *utils)
{
	t_exp	*exp_node;
	char	*tmp;
	int		tot_len;

	exp_node = ft_scan_expansions(*line, utils->envs, utils->exit_status);
	if (exp_node)
	{
		tot_len = ft_get_new_str_len(*line, exp_node);
		tmp = ft_expand(*line, &exp_node, tot_len);
		if (tmp)
		{
			free (*line);
			*line = tmp;
		}
	}
}

void	ft_remove_newline(char **line)
{
	int		len;
	char	*tmp;

	len = ft_strlen(*line);
	if ((*line)[len - 1] == '\n')
	{
		tmp = ft_substr(*line, 0, len - 1);
		free (*line);
		*line = tmp;
	}
}

static void	ft_expand_hdoc(t_redir *redir_node, t_utils *utils,	int new_fd)
{
	char			*line;

	line = get_next_line(redir_node->fd);
	while (line)
	{
		ft_remove_newline(&line);
		ft_expand_line(&line, utils);
		write(new_fd, line, ft_strlen(line));
		write(new_fd, "\n", 1);
		free (line);
		line = get_next_line(redir_node->fd);
	}
}

static void	ft_close_fds_exp_hdoc(int new_fd, int redir_node_fd)
{
	close(new_fd);
	close(redir_node_fd);
}

void	ft_exp_hd(t_redir *redir_node, t_utils *utils)
{
	char			*new_filename;
	int				new_fd;

	new_filename = ft_random_filename();
	if (!new_filename)
		return ;
	new_fd = open_fd(new_filename, O_WRONLY | O_CREAT);
	redir_node->fd = open_fd(redir_node->filename, O_RDONLY);
	if (new_fd < 0 || redir_node->fd < 0)
	{
		free (new_filename);
		return ;
	}
	ft_expand_hdoc(redir_node, utils, new_fd);
	ft_close_fds_exp_hdoc(new_fd, redir_node->fd);
	unlink(redir_node->filename);
	free (redir_node->filename);
	redir_node->filename = new_filename;
}
