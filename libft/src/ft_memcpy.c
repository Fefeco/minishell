/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:50:22 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:25:53 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dest_p;
	const char	*src_p;

	i = 0;
	dest_p = (char *)dst;
	src_p = (char *)src;
	while (dst == src || (!dst && !src))
	{
		return (dst);
	}
	while (i < n)
	{
		dest_p[i] = src_p[i];
		i++;
	}
	return (dst);
}
/*
int main() {
	const char origen[] = "Hola, mundo!";
	char destino[20];

	printf("Contenido original: %s\n", origen);

	ft_memcpy(destino, origen, sizeof(origen));

	printf("ft_memcpy: %s\n", destino);

	ft_memcpy(destino, origen, sizeof(origen));
	printf("memcpy: %s\n", destino);

	return 0;
}
*/
