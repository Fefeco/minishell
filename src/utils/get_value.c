/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:15:07 by fcarranz          #+#    #+#             */
/*   Updated: 2024/06/27 15:09:57 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_exit_error(char quote)
{
	ft_putstr_fd("mini: Error! unclosed quote ", 2);
	ft_putchar_fd(quote, 2);
	ft_putchar_fd('\n', 2);
	return (NULL);
}

char	*ft_get_word(char **line)
{
	int		i;
	char	*value;
	char	quote;

	i = 0;
	quote = 0;
	while ((*line)[i] && (ft_is_metacharacter((*line)[i]) || quote != 0))
	{
		if ((*line)[i] == '"' || (*line)[i] == '\'')
		{
			if (quote == 0)
				quote = (*line)[i];
			else if ((*line)[i] == quote)
				quote = 0;
		}
		++i;
	}
	if (quote != 0)
		return (ft_exit_error(quote));
	value = ft_substr(*line, 0, i);
	*line = *line + i;
	return (value);
}

char	*ft_get_value(char **line)
{
	char	*value;
	int		i;

	i = 0;
	if (ft_strchr("<>|", **line))
	{
		++i;
		if (!ft_strncmp(*line, "<<", 2) || !ft_strncmp(*line, ">>", 2))
			++i;
		value = ft_substr(*line, 0, i);
		*line += i;
	}
	else
		value = ft_get_word(line);
	return (value);
}
