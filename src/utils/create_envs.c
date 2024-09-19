/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:07:06 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/01 15:07:08 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_create_envs(t_utils *utils)
{
	char	path[PATH_MAX];
	char	**envs;

	utils->custom_envs = 1;
	envs = (char **)malloc(sizeof(char *) * 5);
	if (!envs)
		exit(EXIT_FAILURE);
	if (!getcwd(path, sizeof(path)))
		return (NULL);
	envs[0] = ft_strjoin(ft_strdup("PWD="), ft_strdup(path));
	envs[1] = ft_strdup("LS_COLORS=");
	envs[2] = ft_strdup("SHLVL=1");
	envs[3] = ft_strdup("_=/usr/bin/env");
	envs[4] = NULL;
	return (envs);
}
