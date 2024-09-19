/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:13:48 by davifer2          #+#    #+#             */
/*   Updated: 2024/07/03 22:40:05 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args, int fd)
{
	int	flag;
	int	i;

	flag = 0;
	args++;
	while (*args && ft_strncmp(*args, "-n", 2) == 0)
	{
		i = 2;
		while ((*args)[i] && (*args)[i] == 'n')
			++i;
		if ((*args)[i])
			break ;
		flag = 1;
		args++;
	}
	while (*args)
	{
		ft_putstr_fd(*args, fd);
		if (*(args + 1))
			ft_putchar_fd(' ', fd);
		args++;
	}
	if (!flag)
		ft_putchar_fd('\n', fd);
	return (0);
}
