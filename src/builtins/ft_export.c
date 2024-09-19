/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:04:28 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/28 21:16:47 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_env_value(t_env *node, char *new_value)
{
	if (!new_value || !node)
		return (0);
	if (*new_value != '+')
	{
		if (node->value)
			free (node->value);
		if (*new_value == '=')
			node->value = ft_strdup(++new_value);
		else
			node->value = ft_strdup(new_value);
	}
	else
	{
		if (node->value)
			node->value = ft_strjoin(ft_strdup(node->value),
					ft_strdup(new_value + 2));
		else
			node->value = ft_strdup(new_value + 2);
	}
	if (!node->value)
		return (1);
	if (!*node->value)
		node->value = free_and_null(&(node->value));
	node->exported = 1;
	return (0);
}

char	*ft_get_identifier(char *str)
{
	char	*limit;
	int		i;

	if (!str)
		return (NULL);
	limit = ft_strchr(str, '=');
	i = 0;
	while (str[i] && (str + i) != limit)
	{
		if (i == 0 && (!ft_isalpha(str[i]) && str[i] != '_'))
			return (ft_print_stderr(str));
		if (str[i] == '+' && (str + i + 1) == limit)
		{
			limit -= 1;
			break ;
		}
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (ft_print_stderr(str));
		++i;
	}
	if (limit == str)
		return (ft_print_stderr(str));
	if (!limit)
		return (ft_strdup(str));
	return (ft_substr(str, 0, limit - str));
}

char	*ft_get_env_value(char *key_value)
{
	int	i;

	if (!key_value)
		return (NULL);
	i = 0;
	while (key_value[i])
	{
		if (key_value[i] == '=')
		{
			if (i != 0 && key_value[i - 1] == '+')
				--i;
			break ;
		}
		++i;
	}
	if (!key_value[i])
		return (NULL);
	return (key_value + i);
}

int	create_and_add_env_to_list(t_env **env_list, char *key_and_value)
{
	t_env	*node;

	node = ft_create_env_node(key_and_value);
	if (!node)
		return (1);
	ft_add_env_to_list(env_list, node);
	return (0);
}

int	ft_export(t_env **env_list, char **cmd_array, int fd)
{
	t_env	*node;
	char	*key;
	int		i;

	i = 0;
	node = NULL;
	if (!cmd_array[0])
		return (ft_print_env(*env_list, fd));
	while (cmd_array[i])
	{
		key = ft_get_identifier(cmd_array[i]);
		if (key)
		{
			node = ft_get_env_from_list(*env_list, key);
			if (node)
				ft_update_env_value(node, ft_get_env_value(cmd_array[i]));
			else if (create_and_add_env_to_list(env_list, cmd_array[i]))
				return (ft_clear_env_list(*env_list));
			free (key);
			key = NULL;
		}
		++i;
	}
	return (0);
}
