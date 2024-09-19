/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:32:50 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:21:23 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}
/*
int	main(void)
{
	t_list	*node1;
	t_list	*node2;
	t_list	*temp;
	int		i = 1;

	node1 = ft_lstnew("hello");
	node2 = ft_lstnew("world");
	ft_lstadd_back(&node1, node2);

	while (node1 != NULL)
	{
		printf("Vuelta %d: %s\n", i, (char *)node1->content);
		temp = node1->next;
		free(node1);
		node1 = temp;
		i++;
	}
	return (0);
}*/
