/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_homedir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 10:16:30 by davifer2          #+#    #+#             */
/*   Updated: 2024/08/28 14:04:13 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_from_file(t_utils *utils)
{
	char	*home;
	char	*user;
	int		total_len;

	user = get_username();
	total_len = ft_strlen("/home/") + ft_strlen(user) + 1;
	home = (char *)malloc(sizeof(char) * total_len + 1);
	if (!home)
	{
		free (user);
		return ;
	}
	ft_strlcpy(home, "/home/", total_len);
	if (user)
	{
		ft_strlcat(home, user, total_len);
		free (user);
	}
	utils->homedir = home;
}

void	get_homedir(t_utils *utils)
{
	t_env	*node;

	if (utils->homedir)
		return ;
	node = ft_get_env_from_list(utils->envs, "HOME");
	if (node && node->value)
		utils->homedir = ft_strdup(node->value);
	else
		get_from_file(utils);
}
