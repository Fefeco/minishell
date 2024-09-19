/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:53:29 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:19:54 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"

static int	ft_len_nbr(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static void	ft_fill_str(int size, int offset, int n, char *str)
{
	while (size > offset)
	{
		str[size - 1] = n % 10 + '0';
		n = n / 10;
		size--;
	}
}

char	*ft_itoa(int n)
{
	int		offset;
	int		size;
	char	*str;

	offset = 0;
	size = ft_len_nbr(n);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (!(str))
		return (0);
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		n = 147483648;
		offset = 2;
	}
	if (n < 0)
	{
		str[0] = '-';
		offset = 1;
		n = -n;
	}
	ft_fill_str(size, offset, n, str);
	str[size] = '\0';
	return (str);
}
/*
	int main(void)
	{
		char *result1 = ft_itoa(12345);
		char *result2 = ft_itoa(-456);
		char *result3 = ft_itoa(0);
		char *result4 = ft_itoa(10);
		char *result5 = ft_itoa(2147483647);
		char *result6 = ft_itoa(-2147483648);

		printf("El resultado de 12345 es: %s\n", result1);
		printf("El resultado de -456 es: %s\n", result2);
		printf("El resultado de 0 es: %s\n", result3);
		printf("El resultado de 10 es: %s\n", result4);
		printf("El resultado de 2147483647 es: %s\n", result5);
		printf("El resultado de -2147483648 es: %s\n", result6);
		return (0);
	}
*/
