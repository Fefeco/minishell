/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:10:53 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/01 12:10:55 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	total_array_size(char **array, char **splited)
{
	int		i;
	int		size;

	size = 0;
	if (array)
	{
		i = 0;
		while (array[i++])
			++size;
	}
	if (splited)
	{
		i = 0;
		while (splited[i++])
			++size;
	}
	return (size);
}

void	combine_ptrs(char ***new_array, char **array, char **splited, int pos)
{
	int		i;
	int		j;

	i = 0;
	while (i < pos)
	{
		(*new_array)[i] = array[i];
		++i;
	}
	free (array[pos]);
	j = 0;
	while (splited[j])
		(*new_array)[i++] = splited[j++];
	pos++;
	while (array[pos])
		(*new_array)[i++] = array[pos++];
	(*new_array)[i] = NULL;
	free (splited);
	free (array);
}

char	**ft_word_splitting(char **array, int pos)
{
	char	**splited;
	char	**new_array;
	int		size;

	if (!array || array[pos][0] == '\"' || array[pos][0] == '\'')
		return (array);
	splited = ft_split(array[pos], ' ');
	if (!splited)
		return (NULL);
	size = total_array_size(array, splited);
	new_array = (char **)malloc(sizeof(char *) * (size));
	if (!new_array)
		return (NULL);
	new_array[--size] = NULL;
	combine_ptrs(&new_array, array, splited, pos);
	return (new_array);
}
