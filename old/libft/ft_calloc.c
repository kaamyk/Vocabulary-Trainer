/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:23:10 by anvincen          #+#    #+#             */
/*   Updated: 2022/11/15 12:05:57 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buf;

	buf = NULL;
	if (!size || !nmemb)
	{
		buf = malloc(sizeof(char));
		return (buf);
	}
	if (nmemb >= SIZE_MAX / size)
		return (buf);
	buf = malloc(nmemb * size);
	if (!buf)
		return (NULL);
	ft_bzero(buf, nmemb * size);
	return (buf);
}
