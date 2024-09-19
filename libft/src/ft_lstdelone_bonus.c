/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:06:10 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:22:06 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"

/*
void	delete_node(void *content)
{
	free(content);
}
*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free (lst);
}
/*
int	main(void)
{
	t_list	*node1;

	node = ft_lstnew("hello");
	printf("Content %s\n", (char *)node->content);

	ft_lstdelone(node1, delete_node);
	printf("Content %s\n", (char *)node->content);

	return (0);
}*/
