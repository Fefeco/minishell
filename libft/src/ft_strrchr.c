/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:02:19 by davifer2          #+#    #+#             */
/*   Updated: 2024/01/21 13:59:46 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = 0;
	while (*s != '\0')
	{
		if (*s == (char)c)
			last = s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	else
		return ((char *)last);
}
/*
int main()
{
	char *str = "hola";
	char c = 'a';
	printf("%s\n", ft_strrchr(str, c));
	printf("%s\n", strrchr(str, c));
	return (0);
}
*/
