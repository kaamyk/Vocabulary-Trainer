/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 08:59:49 by anvincen          #+#    #+#             */
/*   Updated: 2022/11/24 12:08:13 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_wdlen(const char *s, int c)
{
	int	len;

	len = 0;
	while (*(s + len) != c && *(s + len))
		len++;
	len++;
	return (len);
}

int	ft_wdcount(const char *s, int c)
{
	int	count;

	count = 1;
	if (!*s)
		return (count);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			count++;
			s += ft_wdlen(s, c) - 1;
		}
		if (!*s)
			return (count);
	}
	return (count);
}

void	ft_scat(char **dest, const char **src, int len)
{
	int	i;

	i = 1;
	while (i < len)
	{
		**dest = **src;
		(*dest)++;
		(*src)++;
		i++;
	}
	**dest = 0;
}

char	**ft_freetab(char ***s)
{
	int	i;

	i = 0;
	while (s[0][i])
	{
		free(s[0][i]);
		i++;
	}
	free (s[0]);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*tmp;
	int		j;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * ft_wdcount(s, c));
	if (!tab)
		return (NULL);
	j = 0;
	while (*s)
	{
		if (*s != c && ++j)
		{
			tab[j - 1] = malloc(sizeof(char) * ft_wdlen(s, c));
			if (!(*tab))
				return (ft_freetab(&tab));
			tmp = tab[j - 1];
			ft_scat(&tmp, &s, ft_wdlen(s, c));
		}
		else
			s++;
	}
	tab[j] = NULL;
	return (tab);
}
