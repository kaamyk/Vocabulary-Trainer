#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <wchar.h>
#include <stdint.h>

wchar_t	*wcsjoin(wchar_t const *s1, wchar_t const *s2)
{
	wchar_t	*result = NULL;
	int		t_len = 0;
	int		i = 0;

	if (!s1 || !s2)
		return (NULL);
	t_len = wcslen(s1) + wcslen(s2) + 1;
	result = calloc(t_len, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (*s1)
	{
		result[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		result[i] = *s2;
		s2++;
		i++;
	}
	result[i] = 0;
	return (result);
}

int	getwline( wchar_t **s, size_t *n, FILE *stream)
{
	//Vient d'etre ajoute revoir la suite pour ecrire dans res et plus dans *s
	wchar_t	*res = NULL;
	static wchar_t	rest[256] = {0};
	wchar_t	buf[256] = {0};
	wchar_t	*ptr = NULL;

	if (s == NULL || n == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	else if (ferror (stream) || feof(stream))
		return (-1);

	if (rest[0] != 0)
	{
		if (*s)
		{
			wcscpy(s, rest);
			for (unsigned int i = 0; i < 256; i++)
				rest[i] = 0;
			
		}
		else
		{
			*s = calloc(wcslen(rest) + 1, sizeof(wchar_t));
			if (*s == NULL)
			{
				perror(strerror(errno));
				return (-1);
			}
		}
	}

	while (fgetws(buf, 256, stream) != NULL)
	{
		// printf("la\n");
		ptr = wcschr(buf, L'\n');
		if (ptr != NULL)
		{
			if (*s)		
			{
				*n += ptr - buf;
				ptr = wcsjoin(*s, buf);
				wprintf(L"ptr != NULL && *s != NULL => new ptr == [%ls]\n", ptr);
				free(*s);
				*s = ptr;
			}
			else
			{
				*n = ptr - buf;
				*s = calloc(*n + 1, sizeof(wchar_t));
				if (*s == NULL)
				{
					perror(strerror(errno));
					return (-1);
				}
				wcsncpy(*s, buf, ptr - buf);
			}
			wprintf(L"ptr != NULL && *s == NULL => new *s == [%ls]\n", *s);
			wcscpy(rest, ptr);
			break ;
		}
		else
		{
			if (*s)
			{
				*n += 256;
				*s = wcscat(*s, buf);
				wprintf(L"No nl && *s!= NULL => *s == [%ls]", *s);
			}
			else
			{
				*n = 256;
				*s = calloc(sizeof(wchar_t), 256);
				if (*s == NULL)
				{
					perror(strerror(errno));
					return (-1);
				}
				wcscpy(*s, buf);
				wprintf(L"ptr != NULL && *s == NULL => new *s == [%ls]\n", *s);
			}
		}
	}

	return (*n);
}

int	main( void )
{
	wchar_t	*s = NULL;
	size_t	n = 0;
	FILE	*file = fopen("test.txt", "r");

	while (getwline(&s, &n, file) != -1)
	{
		printf("%ls",s);
		// printf("ici\n");
	}
	return (0);
}