/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:39:52 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:34:41 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!s1 || !set)
		return (0);
	j = ft_strlen(s1) - 1;
	while (i <= j && ft_strchr(set, s1[i]))
	{
		i++;
	}
	if (i > j)
		return (ft_strdup(""));
	while (j > i && ft_strchr(set, s1[j]))
	{
		j--;
	}
	str = ft_substr(s1, i, j - i + 1);
	if (!(str))
		return (0);
	return (str);
}
/*
int	main(void)
{
	char		str[] = "lorem ipsum dolor sit amet";
	const char	*set = "tel";
	char		*result = ft_strtrim(str, set);
	printf("%s", result);
	return (0);
}
*/
