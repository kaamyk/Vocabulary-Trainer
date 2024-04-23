/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:59:01 by anvincen          #+#    #+#             */
/*   Updated: 2022/11/17 11:40:44 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*n_elm;

	n_elm = malloc (sizeof(t_list));
	if (!n_elm)
		return (NULL);
	n_elm->content = content;
	n_elm->next = NULL;
	return (n_elm);
}
