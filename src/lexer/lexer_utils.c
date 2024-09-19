/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedeito <fcarranz@student.42barcel>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 18:20:26 by fedeito           #+#    #+#             */
/*   Updated: 2024/06/26 16:23:40 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	ft_addlast(t_tokens **lexer, t_tokens *current_node)
{
	t_tokens	*tmp_node;

	if (!*lexer)
	{
		*lexer = current_node;
		return (0);
	}
	tmp_node = *lexer;
	while (tmp_node->next)
		tmp_node = tmp_node->next;
	tmp_node->next = current_node;
	current_node->prev = tmp_node;
	return (0);
}

int	ft_is_metacharacter(int c)
{
	if (!ft_isspace(c) && !ft_strchr("<>|", c))
		return (1);
	return (0);
}
