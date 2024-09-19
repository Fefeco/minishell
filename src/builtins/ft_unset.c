/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:33:20 by fcarranz          #+#    #+#             */
/*   Updated: 2024/07/03 16:33:22 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_env **env_list, char **array_keys)
{
	t_env	*node_to_remove;
	t_env	*head;
	int		i;

	if (!*env_list || !array_keys)
		return (0);
	i = 0;
	head = *env_list;
	while (array_keys[i])
	{
		node_to_remove = ft_get_env_from_list(head, array_keys[i]);
		if (node_to_remove)
			head = ft_clear_env_node(node_to_remove);
		++i;
	}
	*env_list = head;
	return (0);
}
