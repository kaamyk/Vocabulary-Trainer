/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:53:08 by anvincen          #+#    #+#             */
/*   Updated: 2022/11/14 10:04:07 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*buf;

	buf = (char *) s;
	while (*buf)
	{
		if (*buf == (char)c)
			return (buf);
		buf++;
	}
	if (c == 0)
		return (buf);
	return (NULL);
}
