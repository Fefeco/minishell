/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:31:44 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/31 12:09:24 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/ft_printf.h"

size_t	ft_nbrunsiglen(unsigned int nb)
{
	unsigned long int	i;

	i = 0;
	while (nb / 10 != 0)
	{
		i++;
		nb /= 10;
	}
	i++;
	return (i);
}
