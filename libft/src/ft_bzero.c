/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:16:10 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:17:42 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"

void	ft_bzero(void *str, size_t n)
{
	ft_memset(str, 0, n);
}
/*
int	main(void)
{
	char	buffer[10];

	ft_bzero(buffer, sizeof(buffer));
	printf("Buffer after ft_bzero: ");
	for (size_t i = 0; i < sizeof(buffer); i++) {
		printf("%d ", buffer[i]);
	}
	printf("\n");
	return (0);
}*/
