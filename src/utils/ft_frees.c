/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:13:43 by davifer2          #+#    #+#             */
/*   Updated: 2024/07/02 20:13:43 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_lexer(t_tokens **lexer)
{
	t_tokens	*tmp;

	while ((*lexer)->prev)
		*lexer = (*lexer)->prev;
	while (*lexer)
	{
		tmp = (*lexer)->next;
		free((*lexer)->value);
		free(*lexer);
		*lexer = tmp;
	}
	*lexer = NULL;
	return (1);
}

void	*ft_free_redir(t_redir *node)
{
	if (node)
	{
		if (node->fd >= 0)
			close (node->fd);
		if (node->here_doc && !access(node->filename, F_OK))
			unlink(node->filename);
		free (node->filename);
		free (node);
		node = NULL;
	}
	return (NULL);
}

void	*ft_free_one_parser(t_cmd *parser)
{
	int		i;

	if (parser->cmd_array)
	{
		i = 0;
		while (parser->cmd_array[i])
			free (parser->cmd_array[i++]);
		free(parser->cmd_array);
		parser->cmd_array = NULL;
	}
	if (parser->full_path)
		free (parser->full_path);
	if (parser->redir_in)
		parser->redir_in = ft_free_redir(parser->redir_in);
	if (parser->redir_out)
		parser->redir_out = ft_free_redir(parser->redir_out);
	free(parser);
	return (NULL);
}

void	ft_free_parser(t_cmd *parser)
{
	t_cmd	*tmp;

	while (parser)
	{
		tmp = parser->next;
		ft_free_one_parser(parser);
		parser = tmp;
	}
}

void	free_loop(t_tokens *lexer_nodes, t_cmd *parser_nodes)
{
	ft_free_lexer(&lexer_nodes);
	ft_free_parser(parser_nodes);
}
