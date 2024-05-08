#include "../inc/german.h"

int	ft_wctoi(const wchar_t *nptr)
{
	int	result;
	int	negative;

	result = 0;
	negative = 1;
	while (*nptr == ' ' || *nptr == '\v' || *nptr == '\t' || *nptr == '\f'
		|| *nptr == '\r' || *nptr == '\n')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			negative *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result * negative);
}