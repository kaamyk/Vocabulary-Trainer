#include "../inc/german.h"

	/*		1T		*/

void	print_tab( wchar_t **t )
{
	for (wchar_t **ptr = t; ptr != NULL && *ptr != NULL && **ptr != 0; ptr++)
	{
		wprintf(L"%ls\n", *ptr);
	}
}

void	print_int_tab( int *t )
{
	for (int *ptr = t; ptr != NULL && *ptr != -1  && *ptr != 0; ptr++)
	{
		wprintf(L"%d\n", *ptr);
	}
}

void	print_results( int nb_fails, int nb_correct )
{
	wprintf(L"\tEND OF SESSION !\n");
	wprintf(WHT "\n\tRight answers: " reset);
	wprintf(BGRN "%d" reset, nb_correct);
	wprintf(WHT "\tWrong answers: " reset);
	wprintf(BRED "%d\n" reset, nb_fails);
}

	/*		LENGTH		*/

int	l_tab( wchar_t **t )
{
	wchar_t	**tmp = t;

	while (*tmp != NULL)
		++tmp;
	return (tmp - t);
}

int	len_file( const char *file_name )
{
	int	res = 0;
	// size_t	n = 0;
	wchar_t	buf[BUFFER_SIZE] = {0};
	FILE	*file = fopen(file_name, "r");
	if (file == NULL)
		return (-1);
		
	// while (fgetws(buf, BUFFER_SIZE * sizeof(wchar_t), file) != NULL)
	while (fgetws(buf, BUFFER_SIZE, file) != NULL)
	{
		// wprintf(L"line[%d] == %ls\n", res, buf);
		if (wcschr(buf, '\n') != NULL)
			++res;
	}
	perror(strerror(errno));
	fclose(file);
	return (res);
}

	/*	MODIFY VALUES	*/

void	del_nl( wchar_t *s )
{
	if (s == NULL)
		return ;
	wchar_t	*tmp = wcschr(s, '\n');
	// wprintf(L"tmp == %ls\n", tmp);
	if (tmp != NULL)
		*tmp = 0;
}

wchar_t	**init_answers( void )
{
	wchar_t	**res = (wchar_t **)calloc(LEN_ANSWERS + 1, sizeof(wchar_t *));
	if (res == NULL)
		return (NULL);
	res[LEN_ANSWERS] = NULL;
	for (int i = 0; i < LEN_ANSWERS && res != NULL; i++)
	{
		res[i] = (wchar_t *)calloc(MAX_LEN_INPUT + 1, sizeof(wchar_t));
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
		wprintf(L"The word you typed is too long. (Max wchar_tacters: 45)\n");
		return (1) ;
	}
	del_nl(user_input);
	// wprintf(L"\tuser_input: [%ls]\n", user_input);
	return (wcslen(user_input) < 1 ? 1 : 0);
}

wchar_t	*find_first_not_of( wchar_t *to_find, wchar_t *str )
{
	// wprintf(L"find_first_not_of(): *tofind == %ls | *str == %ls\n", to_find, str);
	if (to_find == NULL || str == NULL)
		return (NULL);
	while(*str)
	{
		if (wcschr(to_find, *str) == NULL)
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

int	wcscmp_spe_wchar( wchar_t *srpl, wchar_t *sspe, wchar_t *rpl, const wchar_t sp_c )
{
	// wprintf(L">> strcmp_spe_wchar_t()\n");
	wchar_t	*tmp = rpl;
	
	while (*srpl || *sspe)
	{
		// wprintf(L"*srpl == %lc | *sspe == %lc\n", *srpl, *sspe);
		if (*srpl != *sspe)
		{
			if (*srpl == *rpl && *sspe == sp_c)
			{
				// wprintf(L"Skipping spe wchar_t: *srpl == %c\n", *srpl);
				while (*srpl && *rpl)
				{
					++srpl;
					++rpl;
				}
				rpl = tmp;
				++sspe;
				continue ;
			}
			else
			{
				// wprintf(L"Return (%d)\n", *srpl - *sspe);
				return (*srpl - *sspe);
			}
		}
		++srpl;
		++sspe;
	}
	// wprintf(L"Return (0)");
	return (0);
}

bool	check_answer( wchar_t *user_input, wchar_t **answers )
{

	// wprintf(L"check_answers():\n");
	
	wprintf(L"user_input == [%ls]\n", user_input);
	for (uint8_t i = 0; answers[i] != NULL && answers[i][0] != 0; i++)
	{
		wprintf(L"*answers[%d] == [%ls]\n", i, answers[i]);
		if (wcschr(answers[i], L'ß') != NULL && wcschr(user_input, L'ß') == NULL)
		{
			wprintf(L">>> Dans if spechar() <<<\n");
			return (!wcscmp_spe_wchar(user_input, answers[i], L"ss", L'ß'));
		}
		else if (wcscmp(user_input, answers[i]) == 0)
			return (1);
	}
	return (0);
}