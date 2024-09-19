/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:09:27 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:34:59 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"

char	*ft_substr(const char *s, unsigned int start, int len)
{
	char	*substring;

	if (!s)
		return (0);
	if (ft_strlen(s) < (int)start)
		return (ft_calloc(1, sizeof(char)));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	substring = ft_calloc((len + 1), sizeof(char));
	if (!substring)
		return (0);
	ft_strlcpy(substring, (char *)s + start, len + 1);
	return (substring);
}

/* int	main(void)
{
	char	*str;
	char	*result;

	str = "Hola mundo";
	result = ft_substr(str, 5, 10);
	printf("El resultado es: %s", result);
	return (0);
} */
