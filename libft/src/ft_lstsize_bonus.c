/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:21:54 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:24:08 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
/*
int main(void)
{
	t_list	*node;

	node = ft_lstnew("hello");
	printf("%s\n", (char *)node->content);
	printf("La longitud del contenido de la lista es: %d\n", ft_lstsize(node));
	return (0);
}*/
