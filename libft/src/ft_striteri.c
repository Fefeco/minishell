/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:13:18 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:29:31 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}
/*
	void uppercase(unsigned int index, char *ch)
	{
		printf("index: %d\n", index);
		printf("char: %c\n", *ch);
	}
	int main()
	{
		char *str = "hola";
		ft_striteri(str, uppercase);
		return (0);
	}
*/
