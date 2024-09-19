/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:43:47 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:32:08 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*s;
	size_t	len_dst;
	size_t	res;
	size_t	len_src;
	size_t	i;

	s = (char *)src;
	len_dst = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(s);
	res = 0;
	i = 0;
	if (size <= len_dst)
		res = len_src + size;
	else
		res = len_src + len_dst;
	while (s[i] && (len_dst + 1) < size)
	{
		dst[len_dst] = s[i];
		len_dst++;
		i++;
	}
	if (len_dst < size)
		dst[len_dst] = '\0';
	return (res);
}
/*
int	main(void)
{
	char dest[10] = "Hello";
	char src[] = " World";
	//int	result = ft_strlcat(dest, src, sizeof(dest));
	int	result2 = strlcat(dest, src, sizeof(dest));

	printf("%s\n", dest);
	//printf("Resultado mock: %d\n", result);
	printf("Resultado original: %d", result2);
}*/
