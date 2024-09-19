/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:11:43 by davifer2          #+#    #+#             */
/*   Updated: 2024/08/13 14:29:38 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_create_oldpwd(t_env **env_list)
{
	t_env	*node;

	node = ft_create_env_node("OLDPWD");
	if (!node)
		return (NULL);
	ft_add_env_to_list(env_list, node);
	return (node);
}

static int	handle_chdir_spec(t_env *env_list, char *arg, char *cwd, t_env *tmp)
{
	char	*new_value;
	t_env	*oldpwd;
	t_env	*pwd;

	new_value = ft_strdup(tmp->value);
	oldpwd = ft_get_env_from_list(env_list, "OLDPWD");
	if (arg && !ft_strncmp(arg, "-", 1))
		printf("%s\n", new_value);
	if (chdir(new_value) != 0)
	{
		printf("mini: cd: %s: %s\n", arg, strerror(errno));
		return (1);
	}
	else
	{
		if (!oldpwd)
			oldpwd = ft_create_oldpwd(&env_list);
		ft_update_env_value(oldpwd, cwd);
		pwd = ft_get_env_from_list(env_list, "PWD");
		ft_update_env_value(pwd, new_value);
		free(new_value);
	}
	return (0);
}

static int	handle_chdir_all(t_env *env_list, char *arg, char *cwd)
{
	char	*new_value;
	t_env	*oldpwd;
	t_env	*pwd;

	new_value = cwd;
	oldpwd = ft_get_env_from_list(env_list, "OLDPWD");
	if (chdir(arg) != 0)
	{
		printf("mini: cd: %s: %s\n", arg, strerror(errno));
		return (1);
	}
	else
	{
		if (!oldpwd)
			oldpwd = ft_create_oldpwd(&env_list);
		ft_update_env_value(oldpwd, new_value);
		if (!getcwd(cwd, PATH_MAX))
			return (1);
		pwd = ft_get_env_from_list(env_list, "PWD");
		ft_update_env_value(pwd, cwd);
	}
	return (0);
}

int	ch_path(t_env *env_list, char *arg, char *str)
{
	t_env	*tmp;
	int		ret;
	char	cwd[PATH_MAX];

	ret = 1;
	tmp = ft_get_env_from_list(env_list, str);
	if (!getcwd(cwd, sizeof(cwd)))
		return (ret);
	if (str)
		ret = handle_chdir_spec(env_list, arg, cwd, tmp);
	else
	{
		ret = handle_chdir_all(env_list, arg, cwd);
	}
	return (ret);
}
