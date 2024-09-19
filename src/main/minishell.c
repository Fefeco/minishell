/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:36:12 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/28 14:08:39 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_utils(t_utils *utils, char **envs)
{
	int	i;

	i = 0;
	if (!utils)
		return ;
	if (utils->envs)
		ft_clear_env_list(utils->envs);
	if (utils->homedir)
		free(utils->homedir);
	if (utils->custom_envs)
	{
		while (envs[i])
			free (envs[i++]);
		free (envs);
	}
	free(utils);
}

int	main(int argc, char **argv, char **envs)
{
	t_utils	*utils;
	int		exit_status;

	if (!isatty(STDIN_FILENO))
	{
		perror("mini");
		exit(EXIT_FAILURE);
	}
	utils = malloc(sizeof(t_utils));
	if (!utils)
	{
		perror("Error al asignar memoria para utils\n");
		return (1);
	}
	if (!*envs)
		envs = ft_create_envs(utils);
	else
		utils->custom_envs = 0;
	(void)argc;
	(void)argv;
	init_utils(utils, envs);
	ft_shloop(utils);
	exit_status = utils->exit_status;
	free_utils(utils, envs);
	return (exit_status);
}
