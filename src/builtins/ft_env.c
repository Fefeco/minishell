/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:23:11 by davifer2          #+#    #+#             */
/*   Updated: 2024/07/03 19:14:54 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env_list, int fd)
{
	while (env_list)
	{
		if (env_list->exported)
		{
			ft_putstr_fd(env_list->key, fd);
			ft_putchar_fd('=', fd);
			ft_putstr_fd(env_list->value, fd);
			ft_putchar_fd('\n', fd);
		}
		env_list = env_list->next;
	}
	return (0);
}
