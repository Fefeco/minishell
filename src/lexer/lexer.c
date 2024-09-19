/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:58:05 by fcarranz          #+#    #+#             */
/*   Updated: 2024/06/27 16:20:19 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	ft_get_token_type(char *value)
{
	if (!ft_strncmp(value, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(value, "<", 1))
	{
		if (!ft_strncmp(value, "<<", 2))
			return (H_DOC);
		return (STHAN);
	}
	else if (!ft_strncmp(value, ">", 1))
	{
		if (!ft_strncmp(value, ">>", 2))
			return (APPEND);
		return (GTHAN);
	}
	else
		return (WORD);
}

t_tokens	*ft_create_node(char **line)
{
	t_tokens	*new_node;

	new_node = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new_node)
		return (NULL);
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->value = ft_get_value(line);
	if (!new_node->value)
	{
		free (new_node);
		return (NULL);
	}
	new_node->token = ft_get_token_type(new_node->value);
	return (new_node);
}

t_tokens	*ft_lexer(char *line)
{
	t_tokens	*lexer;
	t_tokens	*node;

	lexer = NULL;
	if (!line)
		return (NULL);
	while (*line)
	{
		if (ft_isspace(*line))
		{
			++line;
			continue ;
		}
		node = ft_create_node(&line);
		if (!node || (node && ft_addlast(&lexer, node)))
		{
			ft_free_lexer(&lexer);
			return (NULL);
		}
	}
	return (lexer);
}
