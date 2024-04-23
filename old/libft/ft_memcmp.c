/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:39:26 by anvincen          #+#    #+#             */
/*   Updated: 2022/11/23 14:08:24 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*tmp1;

	tmp = (unsigned char *) s1;
	tmp1 = (unsigned char *) s2;
	if (!n)
		return (0);
	while (n)
	{
		if (*tmp != *tmp1)
			return (*tmp - *tmp1);
		n--;
		tmp++;
		tmp1++;
	}
	return (0);
}
