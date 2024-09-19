/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:58:55 by fedeito           #+#    #+#             */
/*   Updated: 2024/08/28 14:07:37 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_expand_tilde_pwd(t_env *env_list)
{
	t_env	*pwd;

	pwd = ft_get_env_from_list(env_list, "PWD");
	if (pwd)
		return (ft_strdup("$PWD"));
	return (NULL);
}

static char	*ft_expand_tilde_oldpwd(t_env *env_list)
{
	t_env	*oldpwd;

	oldpwd = ft_get_env_from_list(env_list, "OLDPWD");
	if (oldpwd)
		return (ft_strdup("$OLDPWD"));
	return (NULL);
}

char	*ft_expand_tilde_aux(char *str, t_utils *utils)
{
	char	*ret;

	ret = NULL;
	if (!ft_strncmp(str, "~", 2))
		ret = ft_strdup(utils->homedir);
	else if (!ft_strncmp(str, "~+", 3))
		ret = ft_expand_tilde_pwd(utils->envs);
	else if (!ft_strncmp(str, "~-", 3))
		ret = ft_expand_tilde_oldpwd(utils->envs);
	else if (!ft_strncmp(str, "~/", 2))
	{
		ret = ft_strdup(str + 1);
		if (!ret)
			return (str);
		ret = ft_strjoin(ft_strdup(utils->homedir), ret);
	}
	return (ret);
}

void	write_error_fd(char *target, char *error, int fd)
{
	ft_putstr_fd(target, fd);
	ft_putstr_fd(error, fd);
}
