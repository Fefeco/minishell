/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:28:53 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/31 12:10:28 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/ft_printf.h"

static int	ft_format(va_list args, const char format)
{
	if (format == 'c')
		return (ft_printchar_fd(va_arg(args, int), 1));
	else if (format == 's')
		return (ft_printstr_fd(va_arg(args, char *), 1));
	else if (format == 'd' || format == 'i')
		return (ft_printnbr_fd(va_arg(args, int), 1));
	else if (format == 'X' || format == 'x')
		return (ft_printhex_fd(va_arg(args, unsigned int), 1, format));
	else if (format == 'p')
	{
		if (write(1, "0x", 2) == -1)
			return (-1);
		return (ft_printhex_fd(va_arg(args, unsigned long long), 1, format));
	}
	else if (format == 'u')
		return (ft_printnbrunsig_fd(va_arg(args, unsigned int), 1));
	else if (format == '%')
		return (ft_printchar_fd('%', 1));
	else
		return (-1);
}

int	ft_printf_loop(const char *str, va_list args, int count)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			count += ft_format(args, str[i]);
			if (count == -1)
				return (-1);
		}
		else
		{
			count += ft_printchar_fd(str[i], 1);
			if (count == -1)
				return (-1);
		}
		i++;
	}
	return (count);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, str);
	count = ft_printf_loop(str, args, count);
	va_end(args);
	return (count);
}
/*
int main(void)
{
	//ft_printf("\nTiene: %i caracteres\n", ft_printf("%c", 'a'));
	//printf("\nTiene: %i caracteres\n", printf("%c", 'a'));
	//ft_printf("\nTiene: %i caracteres\n",
		ft_printf("\x01\x02\a\v\b\f\r\n"));
	//printf("\nTiene: %i caracteres\n",
		printf("\x01\x02\a\v\b\f\r\n"));
	//char s = 'a';
	ft_printf("Funcion propia\n\n");
	ft_printf("\nTiene: %i caracteres\n",
		ft_printf("\001\002\007\v\010\f\r\n"));
	ft_printf("\nFuncion original\n\n");
	printf("\nTiene: %i caracteres\n",
		printf("\001\002\007\v\010\f\r\n"));


	return (0);
}*/
/*
	// test empty and special characters
	ft_printf("");
	printf("");

	ft_printf("Own: \x01\x02\a\v\b\f\r\n");
	printf("Original: \x01\x02\a\v\b\f\r\n");

	// test with %%
	ft_printf("%%\n");
	printf("%%\n");
	ft_printf(" %%\n");
	printf(" %%\n");
	ft_printf("%%c\n");
	printf("%%c\n");
	ft_printf("%%%%%%\n");
	printf("%%%%%%\n");
	ft_printf("%%%c\n", 'x');
	printf("%%%c\n", 'x');

	// test with %s
	ft_printf("%s\n", "");
	printf("%s\n", "");
	ft_printf("%s\n", (char *)NULL);
	printf("%s\n", (char *)NULL);
	ft_printf("%s\n", "some string with %s hehe");
	printf("%s\n", "some string with %s hehe");
	ft_printf(" %s\n", "can it handle \t and \n?");
	printf(" %s\n", "can it handle \t and \n?");
	ft_printf("%sx\n", "{} al$#@@@^&$$^#^@@^$*((&");
	printf("%sx\n", "{} al$#@@@^&$$^#^@@^$*((&");
	ft_printf("%s%s%s\n", "And ", "some", "joined");
	printf("%s%s%s\n", "And ", "some", "joined");
	ft_printf("%ss%ss%ss\n", "And ", "some other", "joined");
	printf("%ss%ss%ss\n", "And ", "some other", "joined");

	// test with %p

	ft_printf("%s\n", "Ahora los punteros");
	ft_printf("%p\n", "");
	printf("%p\n", "");
	ft_printf("%p\n", NULL);
	printf("%p\n", NULL);
	ft_printf("%p\n", (void *)-14523);
	printf("%p\n", (void *)-14523);
	ft_printf("0x%p-\n", (void *)ULONG_MAX);
	printf("0x%p-\n", (void *)ULONG_MAX);
	ft_printf("%pp%p%p\n",
		(void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);
	printf("%pp%p%p\n", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);

	// test with %d and %i

	ft_printf("%d\n", 0);
	printf("%d\n", 0);
	ft_printf("%d\n", -10);
	printf("%d\n", -10);
	ft_printf("%d\n", -200000);
	printf("%d\n", -200000);
	ft_printf("%d\n", -6000023);
	printf("%d\n", -6000023);
	ft_printf("%d\n", 10);
	printf("%d\n", 10);
	ft_printf("%d\n", 10000);
	printf("%d\n", 10000);
	ft_printf("%d\n", 100023);
	printf("%d\n", 100023);
	ft_printf("%d\n", INT_MAX);
	printf("%d\n", INT_MAX);
	ft_printf("%d\n", INT_MIN);
	printf("%d\n", INT_MIN);
	ft_printf("dgs%dxx\n", 10);
	printf("dgs%dxx\n", 10);
	ft_printf("%d%dd%d\n", 1, 2, -3);
	printf("%d%dd%d\n", 1, 2, -3);

	// test with %u
	ft_printf("%s\n", "AHORA LOS UNSIGNED INTS");
	ft_printf("%u\n", 0);
	printf("%u\n", 0);
	ft_printf("%u\n", -10);
	printf("%u\n", -10);
	ft_printf("%u\n", -200000);
	printf("%u\n", -200000);
	ft_printf("%u\n", -6000023);
	printf("%u\n", -6000023);
	ft_printf("%u\n", 10);
	printf("%u\n", 10);
	ft_printf("%u\n", 10000);
	printf("%u\n", 10000);
	ft_printf("%u\n", 100023);
	printf("%u\n", 100023);
	ft_printf("%u\n", INT_MAX);
	printf("%u\n", INT_MAX);
	ft_printf("%u\n", INT_MIN);
	printf("%u\n", INT_MIN);
	ft_printf("%u\n", UINT_MAX);
	printf("%u\n", UINT_MAX);
	ft_printf("dgs%uxx\n", 10);
	printf("dgs%uxx\n", 10);
	ft_printf("%u%uu%u\n", 1, 2, -3);
	printf("%u%uu%u\n", 1, 2, -3);

	// test with %x and %X

	ft_printf("%s\n", "AHORA x");
	ft_printf("%x\n", 0);
	printf("%x\n", 0);
	ft_printf("%x\n", -10);
	printf("%x\n", -10);
	ft_printf("%x\n", -200000);
	printf("%x\n", -200000);
	ft_printf("%x\n", -6000023);
	printf("%x\n", -6000023);
	ft_printf("%x\n", 10);
	printf("%x\n", 10);
	ft_printf("%x\n", 10000);
	printf("%x\n", 10000);
	ft_printf("%x\n", 100023);
	printf("%x\n", 100023);
	ft_printf("%x\n", 0xabcdef);
	printf("%x\n", 0xabcdef);
	ft_printf("%x\n", 0x7fedcba1);
	printf("%x\n", 0x7fedcba1);
	ft_printf("%x\n", INT_MAX);
	printf("%x\n", INT_MAX);
	ft_printf("%x\n", INT_MIN);
	printf("%x\n", INT_MIN);
	ft_printf("%x\n", UINT_MAX);
	printf("%x\n", UINT_MAX);
	ft_printf("dgs%xxx\n", 10);
	printf("dgs%xxx\n", 10);
	ft_printf("%x%xx%x\n", 1, 2, -3);
	printf("%x%xx%x\n", 1, 2, -3);

	ft_printf("%s\n", "AHORA X");
	ft_printf("%X\n", 0);
	printf("%X\n", 0);
	ft_printf("%X\n", -10);
	printf("%X\n", -10);
	ft_printf("%X\n", -200000);
	printf("%X\n", -200000);
	ft_printf("%X\n", -6000023);
	printf("%X\n", -6000023);
	ft_printf("%X\n", 10);
	printf("%X\n", 10);
	ft_printf("%X\n", 10000);
	printf("%X\n", 10000);
	ft_printf("%X\n", 100023);
	printf("%X\n", 100023);
	ft_printf("%X\n", 0xabcdef);
	printf("%X\n", 0xabcdef);
	ft_printf("%X\n", 0x7fedcba1);
	printf("%X\n", 0x7fedcba1);
	ft_printf("%X\n", INT_MAX);
	printf("%X\n", INT_MAX);
	ft_printf("%X\n", INT_MIN);
	printf("%X\n", INT_MIN);
	ft_printf("%X\n", UINT_MAX);
	printf("%X\n", UINT_MAX);
	ft_printf("dgs%Xxx\n", 10);
	printf("dgs%Xxx\n", 10);
	ft_printf("%X%Xx%X\n", 1, 2, -3);
	printf("%X%Xx%X\n", 1, 2, -3);

}*/
