/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:10:31 by davifer2          #+#    #+#             */
/*   Updated: 2024/07/02 22:40:05 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env *env_list)
{
	t_env	*pwd;
	char	path[PATH_MAX];

	pwd = ft_get_env_from_list(env_list, "PWD");
	if (!getcwd(path, sizeof(path)))
		return (1);
	printf("%s\n", path);
	ft_update_env_value(pwd, path);
	return (0);
}
