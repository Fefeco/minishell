/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:13:32 by fcarranz          #+#    #+#             */
/*   Updated: 2024/07/03 19:16:08 by fedeito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_shlvl(t_env *node_shlvl)
{
	int		new_value;
	char	*val_str;

	val_str = NULL;
	if (!ft_strncmp(node_shlvl->value, "1", 2))
		ft_update_env_value(node_shlvl, "2");
	else
	{
		new_value = ft_atoi(node_shlvl->value) + 1;
		if (new_value > 999)
		{
			printf("minishell: warning: shell level (");
			printf("%d) too high, resetting to 1\n", new_value);
			new_value = 1;
			ft_update_env_value(node_shlvl, ft_itoa(new_value));
		}
		val_str = ft_itoa(new_value);
		if (val_str)
		{
			ft_update_env_value(node_shlvl, val_str);
			free (val_str);
		}
	}
}

void	init_utils(t_utils *utils, char **envs)
{
	t_env	*node_shlvl;

	utils->envs = ft_init_envs(envs);
	node_shlvl = ft_get_env_from_list(utils->envs, "SHLVL");
	utils->exit_status = 0;
	utils->status = -1;
	utils->cmds_amount = 0;
	utils->homedir = NULL;
	utils->builtins[0] = "cd";
	utils->builtins[1] = "echo";
	utils->builtins[2] = "env";
	utils->builtins[3] = "export";
	utils->builtins[4] = "pwd";
	utils->builtins[5] = "unset";
	utils->builtins[6] = "exit";
	utils->builtins[7] = NULL;
	ft_init_shlvl(node_shlvl);
}
