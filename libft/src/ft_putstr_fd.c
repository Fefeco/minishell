/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:53:17 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:27:54 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	len;
	int	i;

	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
/*
int	main(void)
{
	char	str[] = "Hola";
	int	fd = 1;
	ft_putstr_fd(str, fd);
}*/
