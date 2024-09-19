/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:02:46 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/31 12:11:51 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/ft_printf.h"

int	ft_printnbrunsig_fd(unsigned int n, int fd)
{
	if (n < 10)
	{
		if (ft_printchar_fd(n + '0', fd) == -1)
			return (-1);
	}
	else
	{
		if (ft_printnbrunsig_fd(n / 10, fd) == -1)
			return (-1);
		if (ft_printnbrunsig_fd(n % 10, fd) == -1)
			return (-1);
	}
	return (ft_nbrunsiglen(n));
}
