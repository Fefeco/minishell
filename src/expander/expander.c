/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:21:17 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/02 13:53:12 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_new_str_len(char *str, t_exp *expand_values)
{
	int	tot_len;

	tot_len = ft_strlen(str);
	while (expand_values)
	{
		tot_len -= ft_strlen(expand_values->old_value);
		if (expand_values->new_value)
			tot_len += ft_strlen(expand_values->new_value);
		expand_values = expand_values->next;
	}
	return (tot_len);
}

char	*ft_expand(char *str, t_exp **expand, int tot_len)
{
	char	*new_str;
	char	*start;
	int		i;
	int		j;

	new_str = (char *)ft_calloc(sizeof(char), (tot_len + 1));
	if (!new_str || (ft_strlen((*expand)->new_value) == 0 && tot_len == 0))
		return (free_and_null(&new_str));
	i = 0;
	j = 0;
	while (j < tot_len)
	{
		if (*expand)
			start = ft_strnstr(str + i, (*expand)->old_value,
					ft_strlen(str + i));
		while (str[i] && str + i != start)
			new_str[j++] = str[i++];
		if (str + i != start)
			continue ;
		if ((*expand)->new_value)
			j += ft_strlcat(new_str + j, (*expand)->new_value, tot_len - j + 1);
		i += ft_strlen((*expand)->old_value);
		*expand = ft_free_one_expand_node(*expand);
	}
	return (new_str);
}

char	*ft_expand_tilde(char *str, t_utils *utils)
{
	char	*ret;

	ret = NULL;
	ret = ft_expand_tilde_aux(str, utils);
	if (!ret)
		return (str);
	else
		free (str);
	return (ret);
}

void	ft_expand_value(char **str, t_exp *exp_node)
{
	char	*tmp;
	int		tot_len;

	tot_len = ft_get_new_str_len(*str, exp_node);
	tmp = ft_expand(*str, &exp_node, tot_len);
	if (tmp)
	{
		free (*str);
		*str = tmp;
	}
	else
	{
		free (*str);
		*str = NULL;
	}
	if (exp_node)
		exp_node = ft_free_one_expand_node(exp_node);
}

void	ft_expander(t_cmd *cmds, t_utils *utils, int exit_status)
{
	int		i;
	t_exp	*exp_node;

	if (!utils->envs)
		return ;
	while (cmds)
	{
		i = 0;
		while (cmds->cmd_array && cmds->cmd_array[i])
		{
			exp_node = ft_scan_expansions(cmds->cmd_array[i], utils->envs,
					exit_status);
			if (exp_node)
			{
				ft_expand_value(&cmds->cmd_array[i], exp_node);
				if (ft_strlen(cmds->cmd_array[i]))
					cmds->cmd_array = ft_word_splitting(cmds->cmd_array, i);
			}
			if (cmds->cmd_array[i])
				cmds->cmd_array[i] = ft_expand_tilde(cmds->cmd_array[i], utils);
			++i;
		}
		cmds = cmds->next;
	}
}
