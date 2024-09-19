/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:56:54 by fedeito           #+#    #+#             */
/*   Updated: 2024/09/02 13:24:36 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_env(t_env *env_list, int fd)
{
	while (env_list)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(env_list->key, fd);
		if (env_list->exported)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(env_list->value, fd);
			ft_putchar_fd('\"', fd);
		}
		ft_putchar_fd('\n', fd);
		env_list = env_list->next;
	}
	return (0);
}

void	*ft_print_stderr(char *str)
{
	ft_putstr_fd("mini: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (NULL);
}

void	*free_and_null(char **str)
{
	if (str && *str)
	{
		free (*str);
		*str = NULL;
	}
	return (NULL);
}
