#include "../inc/german.h"

int	ft_nblen(int nb)
{
	int		len;
	long	n;

	len = 0;
	n = nb;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

wchar_t	*ft_itoa(int n)
{
	long	nb;
	int		len;
	wchar_t	*res;

	nb = n;
	len = ft_nblen(n);
	res = (wchar_t *)malloc(sizeof(wchar_t) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = 0;
	if (nb == 0)
		res[0] = '0';
	if (nb < 0)
	{
		res[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		len--;
		res[len] = nb % 10 + '0';
		nb /= 10;
	}
	return (res);
}
