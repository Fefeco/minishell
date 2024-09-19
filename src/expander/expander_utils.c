/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:58:55 by fedeito           #+#    #+#             */
/*   Updated: 2024/08/28 16:16:57 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exp	*ft_free_one_expand_node(t_exp *expand_values)
{
	t_exp	*tmp;

	tmp = NULL;
	if (expand_values)
	{
		tmp = expand_values->next;
		free (expand_values->old_value);
		if (expand_values->new_value)
			free (expand_values->new_value);
		free (expand_values);
	}
	return (tmp);
}

void	*ft_free_all_expand_nodes(t_exp *expand_values)
{
	while (expand_values)
		expand_values = ft_free_one_expand_node(expand_values);
	return (NULL);
}

t_exp	*ft_append_exp_node(t_exp *expand_nodes, t_exp *new_node)
{
	t_exp	*head;

	if (!expand_nodes)
		return (new_node);
	head = expand_nodes;
	while (expand_nodes->next)
		expand_nodes = expand_nodes->next;
	expand_nodes->next = new_node;
	return (head);
}

t_exp	*ft_build_exp_node(char *env, t_env *env_node)
{
	t_exp	*new_node;

	new_node = (t_exp *)malloc(sizeof(t_exp));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->old_value = ft_strdup(env);
	if (!env_node)
		new_node->new_value = NULL;
	else
	{
		if (!env_node->value)
			new_node->new_value = ft_strdup("");
		else
			new_node->new_value = ft_strdup(env_node->value);
	}
	return (new_node);
}

char	ft_update_quote_state(char c, char status)
{
	if (c == '\'' && !status)
		return ('\'');
	else if (c == '\"' && !status)
		return ('\"');
	else if (c == status)
		return (0);
	else
		return (status);
}
