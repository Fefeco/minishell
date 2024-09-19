/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:31:44 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/31 12:11:00 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/ft_printf.h"

int	ft_printhex_fd(unsigned long long n, int fd, char format)
{
	if (n >= 16)
	{
		if (ft_printhex_fd(n / 16, fd, format) == -1
			|| ft_printhex_fd(n % 16, fd, format) == -1)
			return (-1);
	}
	else
	{
		if (n < 10)
		{
			if (ft_printchar_fd(n + '0', fd) == -1)
				return (-1);
		}
		else if (format == 'X')
		{
			if (ft_printchar_fd(n - 10 + 'A', fd) == -1)
				return (-1);
		}
		else
		{
			if (ft_printchar_fd(n - 10 + 'a', fd) == -1)
				return (-1);
		}
	}
	return (ft_hexlen(n, format));
}
