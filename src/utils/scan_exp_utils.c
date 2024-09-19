/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_exp_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:40:37 by fedeito           #+#    #+#             */
/*   Updated: 2024/08/28 16:15:45 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_calc_new_str(char *str)
{
	int	len;
	int	new_len;
	int	space;

	len = 0;
	new_len = 0;
	space = 0;
	while (str[len])
	{
		if (ft_isspace(str[len]) && !space)
			space = 1;
		else if (!ft_isspace(str[len]))
		{
			if (space && new_len != 0)
			{
				++new_len;
				space = 0;
			}
			++new_len;
		}
		++len;
	}
	if (len == new_len)
		return (0);
	return (new_len);
}

void	ft_cp_to_new_str(char *dst, char *src, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] && j < len)
	{
		if (i == 0 && ft_isspace(src[i]))
			while (ft_isspace(src[i]))
				++i;
		if (i != 0 && ft_isspace(src[i]) && ft_isspace(src[i - 1]))
			while (ft_isspace(src[i]))
				++i;
		dst[j++] = src[i++];
	}
	dst[len] = '\0';
}

char	*ft_normalize_spaces(char *str)
{
	char	*new_str;
	int		len;

	if (!str)
		return (NULL);
	new_str = NULL;
	len = ft_calc_new_str(str);
	if (!len)
		return (str);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	ft_cp_to_new_str(new_str, str, len);
	free (str);
	return (new_str);
}

void	ft_norm_and_add(t_exp **expand_nodes, t_exp *node, char quote)
{
	char	*normalized;

	if (!quote && node->new_value)
	{
		normalized = ft_normalize_spaces(node->new_value);
		if (!normalized)
		{
			perror("mini: fail on ft_normalize_spaces()");
			return ;
		}
		node->new_value = normalized;
	}
	*expand_nodes = ft_append_exp_node(*expand_nodes, node);
}
