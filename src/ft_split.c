#include "../inc/german.h"

	/* FT_SPLIT */
int	ft_wdlen(const wchar_t *s, int c)
{
	int	len;

	len = 0;
	while (*(s + len) != c && *(s + len))
		len++;
	len++;
	return (len);
}

int	ft_wdcount(const wchar_t *s, int c)
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

void	ft_scat(wchar_t **dest, const wchar_t **src, int len)
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

wchar_t	**ft_split(wchar_t const *s, wchar_t c)
{
	wchar_t	**tab;
	wchar_t	*tmp;
	int		j;

	if (!s)
		return (NULL);
	tab = (wchar_t **)malloc(sizeof(wchar_t *) * ft_wdcount(s, c));
	if (!tab)
		return (NULL);
	j = 0;
	while (*s)
	{
		if (*s != c && ++j)
		{
			tab[j - 1] = (wchar_t *)malloc(sizeof(wchar_t) * ft_wdlen(s, c));
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