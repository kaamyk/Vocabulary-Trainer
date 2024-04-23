/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:08:42 by anvincen          #+#    #+#             */
/*   Updated: 2022/11/15 17:05:58 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*buf;
	unsigned char	*i;

	buf = (unsigned char *)s;
	i = 0;
	while (i < (unsigned char *)n)
	{
		if (*buf == (unsigned char)c)
			return (buf);
		buf++;
		i++;
	}
	return (NULL);
}
