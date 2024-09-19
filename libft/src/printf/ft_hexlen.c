/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:31:44 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/31 12:08:48 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/ft_printf.h"

size_t	ft_hexlen(unsigned long long nbr, char format)
{
	unsigned long long	len;

	len = 0;
	while (nbr / 16 != 0)
	{
		len++;
		nbr /= 16;
	}
	len++;
	if (format == 'p')
		return (len + 2);
	return (len);
}
