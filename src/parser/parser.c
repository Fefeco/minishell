/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:10:16 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/02 13:02:19 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_cmd_node(t_cmd *node, int nb)
{
	if (nb > 0)
	{
		node->cmd_array = (char **)calloc(nb + 1, sizeof(char *));
		if (!node->cmd_array)
			return (-1);
		node->cmd_array[nb] = NULL;
	}
	else
		node->cmd_array = NULL;
	node->error_fd = 0;
	node->full_path = NULL;
	node->prev = NULL;
	node->next = NULL;
	node->redir_in = NULL;
	node->redir_out = NULL;
	return (0);
}

static t_cmd	*ft_create_node(t_tokens **lex_nodes, int i, t_utils *utils)
{
	t_cmd	*new_node;
	int		len;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	len = ft_count_cmds_args(*lex_nodes, i);
	if (ft_init_cmd_node(new_node, len) == -1)
	{
		free(new_node);
		return (NULL);
	}
	ft_create_parser_nodes(lex_nodes, new_node, utils);
	if ((*lex_nodes) && (*lex_nodes)->next && (*lex_nodes)->token == PIPE)
		*lex_nodes = (*lex_nodes)->next;
	return (new_node);
}

static void	*free_cmd_array(char **cmd_array)
{
	int		i;

	if (cmd_array)
	{
		i = 0;
		while (cmd_array[i])
			free (cmd_array[i++]);
		free(cmd_array);
	}
	return (NULL);
}

t_cmd	*ft_parser(t_tokens *lex_nodes, t_utils *utils)
{
	t_cmd	*parser_nodes;
	t_cmd	*new_node;
	int		i;

	if (!lex_nodes)
		return (NULL);
	parser_nodes = NULL;
	while (lex_nodes)
	{
		i = 0;
		new_node = ft_create_node(&lex_nodes, i, utils);
		if (!new_node)
			return (ft_free_parser(parser_nodes), NULL);
		if (new_node && new_node->error_fd)
			new_node->cmd_array = free_cmd_array(new_node->cmd_array);
		ft_addlast_pnode(&parser_nodes, new_node);
	}
	return (parser_nodes);
}
