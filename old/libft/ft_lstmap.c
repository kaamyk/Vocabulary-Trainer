/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:33:01 by anvincen          #+#    #+#             */
/*   Updated: 2022/11/17 11:53:08 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_list;
	t_list	*n_elm;

	if (!lst || !f)
		return (NULL);
	n_list = 0;
	while (lst)
	{
		if (!n_list)
			n_list = ft_lstnew(f(lst->content));
		else
		{	
			n_elm = ft_lstnew(f(lst->content));
			if (!n_elm)
			{
				ft_lstclear(&n_list, del);
				return (NULL);
			}
			ft_lstadd_back(&n_list, n_elm);
		}
		lst = lst->next;
	}
	return (n_list);
}
