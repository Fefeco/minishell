/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:10:00 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:34:14 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"

char	*ft_strnstr(char *str, char *needle, size_t max_length)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[i] == '\0')
	{
		return (str);
	}
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == needle[j] && needle[j] != '\0'
			&& i + j < max_length)
		{
			j++;
		}
		if (needle[j] == '\0')
		{
			return (str + i);
		}
		i++;
	}
	return (0);
}
/*
int main() {
	char *haystack = "Hola, esto es una cadena de prueba.";
	char *needle = "es";
	size_t max_length = 9;

	char *result = ft_strnstr(haystack, needle, max_length);
	char *result2 = strnstr(haystack, needle, max_length);

	if (result != 0) {
		printf("Subcadena encontrada en la posición: %ld\n", result - haystack);
		printf("Subcadena encontrada en la posición: %ld\n", result2 - haystack);
	} else {
		printf("Subcadena no encontrada. %s\n", result);
		printf("Subcadena no encontrada. %s\n", result2);
	}

	return 0;
}*/
