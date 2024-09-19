/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:28:44 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/28 20:42:51 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_create_env_node(char *env)
{
	t_env	*env_node;

	env_node = (t_env *)malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	env_node->key = ft_get_identifier(env);
	env_node->value = ft_get_env_value(env);
	if (!env_node->value)
		env_node->exported = 0;
	else
	{
		env_node->exported = 1;
		if (*env_node->value == '+')
			env_node->value = ft_strdup(env_node->value + 2);
		else
			env_node->value = ft_strdup(env_node->value + 1);
	}
	env_node->prev = NULL;
	env_node->next = NULL;
	return (env_node);
}

t_env	*ft_clear_env_node(t_env *node)
{
	t_env	*tmp;

	if (!node)
		return (NULL);
	tmp = NULL;
	free (node->key);
	if (node->value)
		free (node->value);
	if (node->next)
	{
		node->next->prev = node->prev;
		tmp = node->next;
	}
	if (node->prev)
	{
		node->prev->next = node->next;
		if (!tmp)
			tmp = node->prev;
	}
	free (node);
	while (tmp->prev)
		tmp = tmp->prev;
	return (tmp);
}

int	ft_clear_env_list(t_env *envs)
{
	t_env	*tmp;

	while (envs)
	{
		tmp = envs->next;
		free (envs->key);
		if (envs->value)
			free (envs->value);
		free (envs);
		envs = tmp;
	}
	return (1);
}

void	ft_add_env_to_list(t_env **env_list, t_env *new_node)
{
	t_env	*tmp;

	tmp = NULL;
	if (!new_node)
		return ;
	if (!*env_list)
		*env_list = new_node;
	else
	{
		tmp = *env_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}

t_env	*ft_init_envs(char **envs)
{
	t_env	*new_node;
	t_env	*env_list;

	env_list = NULL;
	while (*envs)
	{
		new_node = ft_create_env_node(*envs);
		if (!new_node)
		{
			ft_clear_env_list(env_list);
			return (NULL);
		}
		ft_add_env_to_list(&env_list, new_node);
		envs++;
	}
	return (env_list);
}
