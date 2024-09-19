/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:51:12 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:25:26 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"

int	ft_memcmp(const void *p1, const void *p2, size_t n)
{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)p1;
	str2 = (unsigned char *)p2;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
/*
int main()
{
	int result = ft_memcmp("hola2", "holai", 6);
	int result2 = memcmp("hola2", "holai", 6);
	printf("%d\n", result);
	printf("%d\n", result2);
	return (0);
}
*/
