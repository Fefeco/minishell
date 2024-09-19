/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:56:24 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:21:40 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"
/*
void	delete_node(void *content)
{
	free(content);
}*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!lst || !del || !(*lst))
		return ;
	ft_lstclear(&(*lst)->next, del);
	(del)((*lst)->content);
	free(*lst);
	*lst = NULL;
}
/*
int	main(void)
{
	t_list	*node;

	node = ft_lstnew("hello");
	printf("Content %s\n", (char *)node->content);

	ft_lstdelone(node, delete_node);
	printf("Content %s\n", (char *)node->content);

	return (0);
}*/
