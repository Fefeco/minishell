/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:21:43 by davifer2          #+#    #+#             */
/*   Updated: 2024/08/30 13:05:34 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_cd(t_env *env_list, char *arg)
{
	t_env	*home;

	home = ft_get_env_from_list(env_list, "HOME");
	if (!home || !home->value)
	{
		printf("mini: cd: HOME not set\n");
		return (1);
	}
	ch_path(env_list, arg, "HOME");
	return (0);
}

static int	handle_cd_minus(t_env *env_list, char *arg)
{
	if (!arg[1])
		ch_path(env_list, arg, "OLDPWD");
	else
	{
		printf("mini: cd: -%c: invalid option\n", arg[1]);
		return (2);
	}
	return (0);
}

int	ft_cd(t_utils *utils, t_cmd *cmd)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	if (!cmd->cmd_array[1])
		return (handle_cd(utils->envs, cmd->cmd_array[1]));
	else if (cmd->cmd_array[1][0] == '-')
		return (handle_cd_minus(utils->envs, cmd->cmd_array[1]));
	else
		return (ch_path(utils->envs, cmd->cmd_array[1], NULL));
}
