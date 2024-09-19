/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:15:56 by fcarranz          #+#    #+#             */
/*   Updated: 2024/07/01 14:36:08 by fedeito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_cmds_args(t_tokens *nodes, int len)
{
	len = 0;
	while (nodes && nodes->token != PIPE)
	{
		if (nodes->token == WORD
			&& (!nodes->prev || nodes->prev->token == WORD
				|| nodes->prev->token == PIPE))
		{
			len++;
		}
		nodes = nodes->next;
	}
	return (len);
}

void	ft_addlast_pnode(t_cmd **list, t_cmd *node)
{
	t_cmd	*current_node;

	if (!*list)
	{
		*list = node;
		return ;
	}
	current_node = *list;
	while (current_node->next)
		current_node = current_node->next;
	current_node->next = node;
	node->prev = current_node;
}

void	fn(char *name)
{
	int		fd;
	int		i;
	char	tmp;

	i = 0;
	while (i < 6)
	{
		fd = open("/dev/urandom", O_RDONLY);
		if (fd < 0)
			free (name);
		if (read(fd, &tmp, 1) != 1)
		{
			close (fd);
			free (name);
		}
		close (fd);
		name[i] = (tmp % 26) + 'a';
		i++;
	}
}

char	*ft_random_filename(void)
{
	char			*name;

	name = (char *)malloc(6 + 1 * sizeof(char));
	if (!name)
		return (NULL);
	fn(name);
	name[6] = '\0';
	if (!access((const char *)name, F_OK))
	{
		free(name);
		name = ft_random_filename();
	}
	name = ft_strjoin(ft_strdup("tmp_file"), name);
	return (name);
}
