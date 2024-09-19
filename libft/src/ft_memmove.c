/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:07:08 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:26:13 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*dest_p;

	dest_p = dest;
	if ((!dest && !src) || dest == src)
		return (dest);
	if (dest > src)
		while (len--)
			((char *)dest)[len] = ((char *)src)[len];
	else
		while (len--)
			*(char *)dest++ = *(char *)src++;
	return (dest_p);
}
/*
int main() {

	char source[] = "Hello, ";
	char destination[] = "Mundo";
	char source2[] = "Hello, ";
	char destination2[] = "Mundo";

	ft_memmove(destination, source, 3);
	memmove(destination2, source2, 3);
	printf("Source: %s\n", source);
	printf("Destination: %s\n", destination);
	printf("Destination2: %s\n", destination2);

	return 0;
}
*/
