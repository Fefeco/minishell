/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:04:36 by davifer2          #+#    #+#             */
/*   Updated: 2024/08/28 11:13:53 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_child_hdoc(t_tokens **l_nodes, t_cmd *p_nodes, t_utils *utils)
{
	free_loop(*l_nodes, p_nodes);
	ft_clear_env_list(utils->envs);
	free (utils);
}

void	*exit_redir(int error, t_redir *redir_node, t_utils *utils)
{
	if (!redir_node)
		return (NULL);
	if (redir_node->filename)
		free (redir_node->filename);
	if (redir_node->fd >= 0 && redir_node->fd <= 100)
		close (redir_node->fd);
	free (redir_node);
	if (error == 1)
		utils->exit_status = 2;
	else if (error == 3)
		utils->exit_status = 3;
	return (NULL);
}

int	open_fd(char *file_name, int mode)
{
	int	fd;

	if (mode & O_CREAT)
		fd = open(file_name, mode, 0664);
	else
		fd = open(file_name, mode);
	if (fd < 0)
		return (-1);
	return (fd);
}

void	ft_child_hdoc(t_tokens **lexer_nodes, t_cmd *parser_nodes,
	t_redir *redir_node, t_utils *utils)
{
	char	*stop;
	int		cmds_amount;
	char	f_name[15];

	ft_bzero(f_name, 15);
	ft_strlcpy(f_name, redir_node->filename,
		ft_strlen(redir_node->filename) + 1);
	cmds_amount = utils->cmds_amount;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	stop = ft_strdup((*lexer_nodes)->next->value);
	if (utils->homedir)
		free (utils->homedir);
	free_child_hdoc(lexer_nodes, parser_nodes, utils);
	free (redir_node->filename);
	free (redir_node);
	if (ft_read_to_file(stop, cmds_amount, f_name) == -1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int	ft_fork_hdoc(t_tokens **lexer_nodes, t_cmd *parser_nodes,
	t_redir *redir_node, t_utils *utils)
{
	pid_t	pid;
	char	*n_stop;
	int		expand;

	expand = 1;
	pid = fork();
	if (pid == -1)
		return (1);
	n_stop = ft_remove_quotes((*lexer_nodes)->next->value);
	if (n_stop != (*lexer_nodes)->next->value)
	{
		free ((*lexer_nodes)->next->value);
		(*lexer_nodes)->next->value = n_stop;
		expand = 0;
	}
	if (pid == 0)
		ft_child_hdoc(lexer_nodes, parser_nodes, redir_node, utils);
	ft_wait_for_childs(1, &utils->exit_status);
	if (expand)
		ft_exp_hd(redir_node, utils);
	return (0);
}
