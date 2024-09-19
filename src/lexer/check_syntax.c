/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:38:01 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/04 12:38:06 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_lex_error(t_tokens *node, char *line, int newline_error)
{
	ft_putstr_fd("mini: syntax error near unexpected token `", 2);
	if (newline_error)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(node->value, 2);
	ft_putstr_fd("'\n", 2);
	ft_free_lexer(&node);
	add_history(line);
	return (1);
}

static int	ft_wait_new_node(t_tokens *last_node, char **old_line)
{
	char		*new_line;
	t_tokens	*new_nodes;

	new_line = readline("> ");
	if (!new_line)
		return (1);
	new_nodes = ft_lexer(new_line);
	if (!new_nodes)
	{
		free (new_line);
		return (1);
	}
	last_node->next = new_nodes;
	new_nodes->prev = last_node;
	new_line = ft_strjoin(ft_strdup(" "), new_line);
	(*old_line) = ft_strjoin(*old_line, new_line);
	return (0);
}

static int	ft_check_pipe_cases(t_tokens *current, char **line)
{
	if (!current->prev)
		return (ft_lex_error(current, *line, 0));
	if (current->prev->token == PIPE)
		return (ft_lex_error(current, *line, 0));
	if (!current->next && ft_wait_new_node(current, line))
		return (ft_free_lexer(&current));
	return (0);
}

int	ft_check_syntax(t_tokens *lexer_nodes, char **line)
{
	t_tokens	*current;

	if (!lexer_nodes)
		return (1);
	current = lexer_nodes;
	while (current)
	{
		if (current->token != WORD)
		{
			if (current->token == PIPE && ft_check_pipe_cases(current, line))
				return (1);
			if (current->prev)
				if (current->prev->token != WORD
					&& current->prev->token != PIPE)
					return (ft_lex_error(current, *line, 0));
			if (!current->next)
				return (ft_lex_error(current, *line, 1));
		}
		current = current->next;
	}
	return (0);
}
