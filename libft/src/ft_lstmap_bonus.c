/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:16:10 by davifer2          #+#    #+#             */
/*   Updated: 2024/05/29 20:22:49 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/libft.h"
/*
void *uppercase_content(void *content)
{
	size_t	i;
	char	*str;
	char *result;

	i = 0;
	if (content == NULL) {
		return NULL;
	}
	str = (char *)content;
	result = ft_strdup(str);
	while (result[i]) {
		result[i] = ft_toupper(result[i]);
		i++;
	}
	return result;
}

void free_content(void *content)
{
	free(content);
}*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	void	*aux;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		aux = f(lst->content);
		new_node = ft_lstnew(aux);
		if (!new_node)
		{
			del(aux);
			ft_lstclear(&new_lst, (*del));
			return (new_lst);
		}
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}
/*
int main(void)
{
	t_list	*lst;
	t_list *new_lst;

	lst = ft_lstnew("hello");
	ft_lstadd_back(&lst, ft_lstnew("world"));
	new_lst = ft_lstmap(lst, uppercase_content, free_content);
}*/
