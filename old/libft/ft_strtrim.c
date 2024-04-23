/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:14:49 by anvincen          #+#    #+#             */
/*   Updated: 2022/11/21 10:07:56 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_char_in_set(char const c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*n_str;
	const char	*buf;

	if (!s1 || !set)
		return (NULL);
	while (ft_char_in_set(*s1, set) && *s1)
		s1++;
	if (!*s1)
	{
		n_str = malloc(sizeof(char) * 1);
		if (!n_str)
			return (NULL);
		*n_str = 0;
		return (n_str);
	}
	buf = s1;
	while (*(buf + 1))
		buf++;
	while (ft_char_in_set(*buf, set) && buf >= s1)
		buf--;
	n_str = malloc(sizeof(char) * (buf - s1 + 2));
	if (!n_str)
		return (NULL);
	ft_strlcpy(n_str, s1, (buf - s1 + 2));
	return (n_str);
}
