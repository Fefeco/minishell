/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:15:07 by fcarranz          #+#    #+#             */
/*   Updated: 2024/06/27 15:09:57 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_get_env_from_list(t_env *env_list, char *key)
{
	if (!env_list || !key)
		return (NULL);
	while (env_list->prev)
		env_list = env_list->prev;
	while (env_list && ft_strncmp(env_list->key, key, ft_strlen(key) + 1))
		env_list = env_list->next;
	return (env_list);
}
