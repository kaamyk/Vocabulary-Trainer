#include "../inc/german.h"

	/*		PRINT		*/

void	print_tab( wchar_t **t )
{
	for (wchar_t **ptr = t; ptr != NULL && *ptr != NULL && **ptr != 0; ptr++)
	{
		write(1, *ptr, wcslen(*ptr));
		write(1, "\n", 1);
	}
}

void	print_int_tab( int *t )
{
	for (int *ptr = t; ptr != NULL && *ptr != -1  && *ptr != 0; ptr++)
	{
		printf("%d\n", *ptr);
	}
}

void	print_results( int nb_fails, int nb_correct )
{
	printf("\tEND OF SESSION !\n");
	printf(WHT "\n\tRight answers: " reset);
	printf(BGRN "%d" reset, nb_correct);
	printf(WHT "\tWrong answers: " reset);
	printf(BRED "%d\n" reset, nb_fails);
}

	/*		LENGTH		*/

int	l_tab( wchar_t **t )
{
	wchar_t	**tmp = t;

	while (*tmp != NULL)
		++tmp;
	return (tmp - t);
}

	/*	MODIFY VALUES	*/

void	del_nl( wchar_t *s )
{
	if (s == NULL)
		return ;
	wchar_t	*tmp = wcschr(s, '\n');
	// printf("tmp == %ls\n", tmp);
	if (tmp != NULL)
		*tmp = 0;
}

wchar_t	**init_answers( void )
{
	wchar_t	**res = calloc(LEN_ANSWERS + 1, sizeof(wchar_t *));
	if (res == NULL)
		return (NULL);
	res[LEN_ANSWERS] = NULL;
	for (int i = 0; i < LEN_ANSWERS && res != NULL; i++)
	{
		res[i] = calloc(MAX_LEN_INPUT + 1, sizeof(wchar_t));
		if (res[i] == NULL)
		{
			res = ft_freetab(&res);
			return (NULL);
		}
	}
	return (res);
}

	/*	OTHER */

bool	get_input( wchar_t *user_input )
{
	if (fgetws(user_input, MAX_LEN_INPUT, stdin) == NULL)
	{
		printf("The word you typed is too long. (Max wchar_tacters: 45)\n");
		return (1) ;
	}
	del_nl(user_input);
	// printf("\tuser_input: [%ls]\n", user_input);
	return (wcslen(user_input) < 1 ? 1 : 0);
}

wchar_t	*find_first_not_of( wchar_t *to_find, wchar_t *str )
{
	if (to_find == NULL || str == NULL)
		return (NULL);
	while(*str)
	{
		if (ft_wcschr(to_find, *str) == -1)
			return (str);
		++str;
	}
	return (NULL);
}

bool	find_int_in_tab( int n, int *t )
{
	while (*t != -1)
	{
		if (*t == n)
			return (1);
		++t;
	}
	return (0);
}

bool	check_answer( wchar_t *user_input, wchar_t **answers )
{

	// printf("check_answers():\n");
	// int	tmp = 0;
	wchar_t	B = L'ß';

// 348
// 447
// 539

	
	for (uint8_t i = 0; answers[i] != NULL && answers[i][0] != 0; i++)
	{
		// tmp = ft_wcschr(answers[i], 'ß');
		if (ft_wcschr(answers[i], B) != -1 && ft_wcschr(user_input, B) == -1)
		{
			strcmp_spe_wchar_t(user_input, answers[i], L"ss", B);
		}
		if (wcscmp(user_input, answers[i]) == 0)
			return (1);
	}
	return (0);
}

int	ft_wcschr( wchar_t *s, wchar_t to_find )//die Fussgängerzone
{
	printf(">> ft_wcschr():\n");
	if (wprintf(L"\ts == %ls\n", s))
		perror(strerror(errno));
	if (wprintf(L"\tto_find == %c\n", to_find) < 0)
		perror(strerror(errno));
	int	i = 0;

	while (s[i])
	{
		wprintf(L"\ts[%d] == %lc\n",i, s[i]);
		wprintf(L"\tto_find == %lc\n", to_find);
		if (s[i] == to_find)
			return (i);
		i++;
	}
	printf("Return (-1)\n");
	return (-1);
}

int	strcmp_spe_wchar_t( wchar_t *s1, wchar_t *s2, wchar_t *rpl, wchar_t sp_c )
{
	printf(">> strcmp_spe_wchar_t()\n");
	wchar_t	*tmp = rpl;
	
	while (*s1 || *s2)
	{
		printf("*s1 == %c | *s2 == %c\n", *s1, *s2);
		if (*s1 != *s2)
		{
			if (*s1 != rpl[0] || *s2 != sp_c)
			{
				printf("Return (%d)\n", *s1 - *s2);
				return (*s1 - *s2);
			}
			else
			{
				printf("Skipping spe wchar_t: *s1 == %c\n", *s1);
				tmp = rpl;
				while (*s1 && *rpl)
				{
					++s1;
					++rpl;
				}
				rpl = tmp;
				++s2;
				continue ;
			}
		}
		++s1;
		++s2;
	}
	return (0);
}