/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:22:44 by anvincen          #+#    #+#             */
/*   Updated: 2022/11/11 16:31:28 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d_buf;
	const char	*s_buf;

	if (!dest && !src)
		return (NULL);
	d_buf = (char *) dest;
	s_buf = (const char *) src;
	if (d_buf > s_buf)
	{
		while (n-- > 0)
			d_buf[n] = s_buf[n];
	}
	else
	{
		while (n)
		{
			*d_buf = *s_buf;
			d_buf++;
			s_buf++;
			n--;
		}
	}
	return (dest);
}
