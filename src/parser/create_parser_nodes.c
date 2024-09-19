/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_parser_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:10:54 by davifer2          #+#    #+#             */
/*   Updated: 2024/08/28 11:05:02 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*ft_fill_redirections(t_tokens **lex_nodes, t_cmd *parser_nodes,
	t_utils *utils)
{
	t_redir		*new_node;

	new_node = NULL;
	if (!(*lex_nodes)->next || (*lex_nodes)->next->token != WORD)
	{
		ft_putstr_fd("mini: syntax error\n", 2);
		utils->exit_status = 2;
		return (NULL);
	}
	if ((*lex_nodes)->token == H_DOC)
		new_node = hdoc_redir(lex_nodes, parser_nodes, utils);
	else if ((*lex_nodes)->token == STHAN)
		new_node = sthan_redir((*lex_nodes)->next->value, utils, parser_nodes);
	else if ((*lex_nodes)->token == APPEND || (*lex_nodes)->token == GTHAN)
		new_node = append_gthan_redir((*lex_nodes)->next->value,
				(*lex_nodes)->token, utils, parser_nodes);
	return (new_node);
}

static void	gthan_append_nodes(t_tokens **lex_nodes, t_cmd *cmd_node)
{
	if (cmd_node->redir_out)
		cmd_node->redir_out = ft_free_redir(cmd_node->redir_out);
	cmd_node->redir_out = ft_fill_redirections(lex_nodes, cmd_node, NULL);
}

static void	sthan_hdoc_nodes(t_tokens **lex_nodes, t_cmd *cmd_node,
	t_utils *utils)
{
	if (cmd_node->redir_in)
		cmd_node->redir_in = ft_free_redir(cmd_node->redir_in);
	cmd_node->redir_in = ft_fill_redirections(lex_nodes, cmd_node, utils);
}

void	ft_create_parser_nodes(t_tokens **lex_nodes, t_cmd *cmd_node,
	t_utils *utils)
{
	int	i;

	i = 0;
	while (*lex_nodes && (*lex_nodes)->token != PIPE)
	{
		if ((*lex_nodes)->token == WORD)
		{
			cmd_node->cmd_array[i] = ft_strdup((*lex_nodes)->value);
			if (!cmd_node->cmd_array[i++])
			{
				ft_free_parser(cmd_node);
				return ;
			}
			*lex_nodes = (*lex_nodes)->next;
			continue ;
		}
		if ((*lex_nodes)->token == GTHAN || (*lex_nodes)->token == APPEND)
			gthan_append_nodes(lex_nodes, cmd_node);
		else if ((*lex_nodes)->token == STHAN || (*lex_nodes)->token == H_DOC)
			sthan_hdoc_nodes(lex_nodes, cmd_node, utils);
		*lex_nodes = (*lex_nodes)->next->next;
	}
}
