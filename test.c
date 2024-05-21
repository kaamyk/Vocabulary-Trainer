#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <wchar.h>

int	getwline( wchar_t **s, size_t *n, FILE *stream)
{
	wchar_t	buf[256] = {0};
	wchar_t	*ptr = NULL;
	int		len = 0;

	if (s == NULL || n == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	else if (ferror (stream) || feof(stream))
		return (-1);
	else if (*s != NULL)
	{
		free(*s);
		*s = NULL;
	}

	while (fgetws(buf, 256, stream) != NULL)
	{
		ptr = wcschr(buf, L'\n');
		if (ptr != NULL)
		{
			if (*s)		
			{
				*n += ptr - buf;
				*s = wcsncat(s, buf, *n);
				wprintf(L"ptr != NULL && *s != NULL => new *s == [%ls]\n", *s);
				break ;
			}
			else
			{
				*n = ptr - buf;
				*s = malloc(*n + sizeof(wchar_t));

				wprintf(L"ptr != NULL && *s == NULL => new *s == [%ls]\n", *s);
				break ;
			}
		}
		else
		{
			if (*s)
			{
				*n += 256;
				*s = wcscat(s, buf);
				wprintf(L"No nl && *s!= NULL => *s == [%ls]", *s);
			}
			else
			{
				*n = 256;
				*s =
			}
		}
	}

	return (len);
}

int	main( void )
{
	char	*s = NULL;
	size_t	n = 0;
	FILE	*file = fopen("test.txt", "r");

	while (ft_getline(&s, &n, file))
	{
		printf("%s",s);
	}
	return (0);
}