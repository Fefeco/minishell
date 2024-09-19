/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:53:17 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/31 12:12:47 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/ft_printf.h"

int	ft_printstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
	{
		if (write(fd, "(null)", 6) != 6)
			return (-1);
		return (6);
	}
	while (s[i])
	{
		if (ft_printchar_fd(s[i], fd) == -1)
			return (-1);
		i++;
	}
	return (i);
}
/*
int	main(void)
{
	char	str[] = "Hola";
	int	fd = 1;
	ft_printstr_fd(str, fd);
}*/
