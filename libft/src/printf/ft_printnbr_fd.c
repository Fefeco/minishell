/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:02:46 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/31 12:11:35 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/ft_printf.h"

static int	ft_printnbr_max(int nb)
{
	if (nb == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
	}
	return (11);
}

int	ft_printnbr_fd(int n, int fd)
{
	unsigned int	nbr;

	nbr = n;
	if (n == -2147483648)
		return (ft_printnbr_max(n));
	else
	{
		if (n < 0)
		{
			if (ft_printchar_fd('-', fd) == -1)
				return (-1);
			n = -n;
		}
		if (n > 9)
			if (ft_printnbr_fd(n / 10, fd) == -1)
				return (-1);
		if (ft_printchar_fd(n % 10 + '0', fd) == -1)
			return (-1);
	}
	return (ft_nbrlen(nbr));
}
/*
int main()
{
	ft_printnbr_fd(-2147483648, 1);
	return (0);
}*/
